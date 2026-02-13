#include "postit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

PostIt postits[MAX_POSTITS];
int postit_count = 0;

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

void update_list(HWND hList) {
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    for (int i = 0; i < postit_count; i++) {
        char buffer[100];
        sprintf(buffer, "%d: %s (%s)", postits[i].id, postits[i].title, postits[i].date);
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);
    }
}

void add_postit(HWND hTitle, HWND hContent) {
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
    SetWindowText(hTitle, "");
    SetWindowText(hContent, "");
}

void edit_postit(HWND hList, HWND hTitle, HWND hContent) {
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
    SetWindowText(hTitle, "");
    SetWindowText(hContent, "");
}

void delete_postit(HWND hList) {
    int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
    if (index == LB_ERR) {
        MessageBox(NULL, "Seleziona un post-it da eliminare.", "Errore", MB_OK | MB_ICONERROR);
        return;
    }
    for (int i = index; i < postit_count - 1; i++) {
        postits[i] = postits[i + 1];
    }
    postit_count--;
}