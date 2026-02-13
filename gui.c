#include "postit.h"

HWND hList, hTitle, hContent;

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
            update_list(hList);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_ADD:
                    add_postit(hTitle, hContent);
                    update_list(hList);
                    break;
                case IDC_EDIT:
                    edit_postit(hList, hTitle, hContent);
                    update_list(hList);
                    break;
                case IDC_DELETE:
                    delete_postit(hList);
                    update_list(hList);
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