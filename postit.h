#ifndef POSTIT_H
#define POSTIT_H

#include <windows.h>

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

extern PostIt postits[MAX_POSTITS];
extern int postit_count;

void load_postits();
void save_postits();
void add_postit(HWND hTitle, HWND hContent);
void edit_postit(HWND hList, HWND hTitle, HWND hContent);
void delete_postit(HWND hList);
void update_list(HWND hList);

#endif