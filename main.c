#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_POSTITS 100
#define MAX_TITLE 50
#define MAX_CONTENT 200
#define FILENAME "postits.txt"

#define IDC_LIST 101
#define IDC_TITLE 102
#define IDC_CONTENT 103
#define IDC_ADD 104
#define IDC_EDIT 105
#define IDC_DELETE 106
#define IDC_SAVE 107

typedef struct {
    int id;
    char title[MAX_TITLE];
    char content[MAX_CONTENT];
    char date[20];
} PostIt;

PostIt postits[MAX_POSTITS];
int postit_count = 0;

HWND hList, hTitle, hContent;

void load_postits() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) return;
    char line[300];
    while (fgets(line, sizeof(line), file) && postit_count < MAX_POSTITS) {
        sscanf(line, "%d|%[^|]|%[^|]|%[^\n]", &postits[postit_count].id, postits[postit_count].title, postits[postit_count].content, postits[postit_count].date);
        postit_count++;
    }
    fclose(file);
}

void save_postits() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        MessageBox(NULL, "Errore nel salvare i post-it.", "Errore", MB_OK | MB_ICONERROR);
        return;
    }
    for (int i = 0; i < postit_count; i++) {
        fprintf(file, "%d|%s|%s|%s\n", postits[i].id, postits[i].title, postits[i].content, postits[i].date);
    }
    fclose(file);
}

void update_list() {
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    for (int i = 0; i < postit_count; i++) {
        char buffer[100];
        sprintf(buffer, "%d: %s (%s)", postits[i].id, postits[i].title, postits[i].date);
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);
    }
}

void add_postit() {
    if (postit_count >= MAX_POSTITS) {
        MessageBox(NULL, "Limite di post-it raggiunto.", "Errore", MB_OK | MB_ICONERROR);
        return;
    }
    char title[MAX_TITLE], content[MAX_CONTENT];
    GetWindowText(hTitle, title, MAX_TITLE);
    GetWindowText(hContent, content, MAX_CONTENT);
    if (strlen(title) == 0 || strlen(content) == 0) {
        MessageBox(NULL, "Titolo e contenuto richiesti.", "Errore", MB_OK | MB_ICONERROR);
        return;
    }
    PostIt p;
    p.id = postit_count + 1;
    strcpy(p.title, title);
    strcpy(p.content, content);
    time_t t = time(NULL);
    strftime(p.date, sizeof(p.date), "%Y-%m-%d %H:%M:%S", localtime(&t));
    postits[postit_count++] = p;
    update_list();
    SetWindowText(hTitle, "");
    SetWindowText(hContent, "");
}

void edit_postit() {
    int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
    if (index == LB_ERR) {
        MessageBox(NULL, "Seleziona un post-it da modificare.", "Errore", MB_OK | MB_ICONERROR);
        return;
    }
    char title[MAX_TITLE], content[MAX_CONTENT];
    GetWindowText(hTitle, title, MAX_TITLE);
    GetWindowText(hContent, content, MAX_CONTENT);
    if (strlen(title) == 0 || strlen(content) == 0) {
        MessageBox(NULL, "Titolo e contenuto richiesti.", "Errore", MB_OK | MB_ICONERROR);
        return;
    }
    strcpy(postits[index].title, title);
    strcpy(postits[index].content, content);
    time_t t = time(NULL);
    strftime(postits[index].date, sizeof(postits[index].date), "%Y-%m-%d %H:%M:%S", localtime(&t));
    update_list();
    SetWindowText(hTitle, "");
    SetWindowText(hContent, "");
}

void delete_postit() {
    int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
    if (index == LB_ERR) {
        MessageBox(NULL, "Seleziona un post-it da eliminare.", "Errore", MB_OK | MB_ICONERROR);
        return;
    }
    for (int i = index; i < postit_count - 1; i++) {
        postits[i] = postits[i + 1];
    }
    postit_count--;
    update_list();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            hList = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY, 10, 10, 380, 200, hwnd, (HMENU)IDC_LIST, NULL, NULL);
            CreateWindow("STATIC", "Titolo:", WS_CHILD | WS_VISIBLE, 10, 220, 50, 20, hwnd, NULL, NULL, NULL);
            hTitle = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 220, 320, 20, hwnd, (HMENU)IDC_TITLE, NULL, NULL);
            CreateWindow("STATIC", "Contenuto:", WS_CHILD | WS_VISIBLE, 10, 250, 70, 20, hwnd, NULL, NULL, NULL);
            hContent = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 70, 250, 320, 60, hwnd, (HMENU)IDC_CONTENT, NULL, NULL);
            CreateWindow("BUTTON", "Aggiungi", WS_CHILD | WS_VISIBLE, 10, 320, 80, 30, hwnd, (HMENU)IDC_ADD, NULL, NULL);
            CreateWindow("BUTTON", "Modifica", WS_CHILD | WS_VISIBLE, 100, 320, 80, 30, hwnd, (HMENU)IDC_EDIT, NULL, NULL);
            CreateWindow("BUTTON", "Elimina", WS_CHILD | WS_VISIBLE, 190, 320, 80, 30, hwnd, (HMENU)IDC_DELETE, NULL, NULL);
            CreateWindow("BUTTON", "Salva ed Esci", WS_CHILD | WS_VISIBLE, 280, 320, 110, 30, hwnd, (HMENU)IDC_SAVE, NULL, NULL);
            update_list();
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_ADD:
                    add_postit();
                    break;
                case IDC_EDIT:
                    edit_postit();
                    break;
                case IDC_DELETE:
                    delete_postit();
                    break;
                case IDC_SAVE:
                    save_postits();
                    PostQuitMessage(0);
                    break;
                case IDC_LIST:
                    if (HIWORD(wParam) == LBN_SELCHANGE) {
                        int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
                        if (index != LB_ERR) {
                            SetWindowText(hTitle, postits[index].title);
                            SetWindowText(hContent, postits[index].content);
                        }
                    }
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    load_postits();
    WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), NULL, "PostItManager", NULL};
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindow("PostItManager", "Gestore Post-It", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 420, 400, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}