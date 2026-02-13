#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_POSTITS 100
#define MAX_TITLE 50
#define MAX_CONTENT 200
#define FILENAME "postits.txt"

typedef struct {
    int id;
    char title[MAX_TITLE];
    char content[MAX_CONTENT];
    char date[20];
} PostIt;

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
        printf("Errore nel salvare i post-it.\n");
        return;
    }
    for (int i = 0; i < postit_count; i++) {
        fprintf(file, "%d|%s|%s|%s\n", postits[i].id, postits[i].title, postits[i].content, postits[i].date);
    }
    fclose(file);
}

void add_postit() {
    if (postit_count >= MAX_POSTITS) {
        printf("Limite di post-it raggiunto.\n");
        return;
    }
    PostIt p;
    p.id = postit_count + 1;
    printf("Titolo: ");
    fgets(p.title, MAX_TITLE, stdin);
    p.title[strcspn(p.title, "\n")] = 0; // remove newline
    printf("Contenuto: ");
    fgets(p.content, MAX_CONTENT, stdin);
    p.content[strcspn(p.content, "\n")] = 0;
    time_t t = time(NULL);
    strftime(p.date, sizeof(p.date), "%Y-%m-%d %H:%M:%S", localtime(&t));
    postits[postit_count++] = p;
    printf("Post-it aggiunto!\n");
}

void list_postits() {
    if (postit_count == 0) {
        printf("Nessun post-it presente.\n");
        return;
    }
    for (int i = 0; i < postit_count; i++) {
        printf("ID: %d\nTitolo: %s\nContenuto: %s\nData: %s\n\n", postits[i].id, postits[i].title, postits[i].content, postits[i].date);
    }
}

void edit_postit() {
    int id;
    printf("ID del post-it da modificare: ");
    scanf("%d", &id);
    getchar(); // consume newline
    for (int i = 0; i < postit_count; i++) {
        if (postits[i].id == id) {
            printf("Nuovo titolo (attuale: %s): ", postits[i].title);
            fgets(postits[i].title, MAX_TITLE, stdin);
            postits[i].title[strcspn(postits[i].title, "\n")] = 0;
            printf("Nuovo contenuto (attuale: %s): ", postits[i].content);
            fgets(postits[i].content, MAX_CONTENT, stdin);
            postits[i].content[strcspn(postits[i].content, "\n")] = 0;
            time_t t = time(NULL);
            strftime(postits[i].date, sizeof(postits[i].date), "%Y-%m-%d %H:%M:%S", localtime(&t));
            printf("Post-it modificato!\n");
            return;
        }
    }
    printf("Post-it non trovato.\n");
}

void delete_postit() {
    int id;
    printf("ID del post-it da eliminare: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < postit_count; i++) {
        if (postits[i].id == id) {
            for (int j = i; j < postit_count - 1; j++) {
                postits[j] = postits[j + 1];
            }
            postit_count--;
            printf("Post-it eliminato!\n");
            return;
        }
    }
    printf("Post-it non trovato.\n");
}

int main() {
    load_postits();
    int choice;
    while (1) {
        printf("\nGestore Post-It\n");
        printf("1. Aggiungi post-it\n");
        printf("2. Lista post-it\n");
        printf("3. Modifica post-it\n");
        printf("4. Elimina post-it\n");
        printf("5. Salva ed esci\n");
        printf("Scelta: ");
        scanf("%d", &choice);
        getchar(); // consume newline
        switch (choice) {
            case 1: add_postit(); break;
            case 2: list_postits(); break;
            case 3: edit_postit(); break;
            case 4: delete_postit(); break;
            case 5: save_postits(); printf("Arrivederci!\n"); return 0;
            default: printf("Scelta non valida.\n");
        }
    }
    return 0;
}