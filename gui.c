#include "postit.h"

HWND hList, hTitle, hContent;
HFONT hFont;
HICON hIconAdd, hIconEdit, hIconDelete, hIconSave;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI");
            
            // Load icons
            hIconAdd = LoadIcon(NULL, IDI_ASTERISK);
            hIconEdit = LoadIcon(NULL, IDI_EXCLAMATION);
            hIconDelete = LoadIcon(NULL, IDI_HAND);
            hIconSave = LoadIcon(NULL, IDI_WINLOGO);
            
            hList = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY, 20, 20, 360, 180, hwnd, (HMENU)IDC_LIST, NULL, NULL);
            SendMessage(hList, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            CreateWindow("STATIC", "Titolo:", WS_CHILD | WS_VISIBLE, 20, 210, 60, 25, hwnd, NULL, NULL, NULL);
            hTitle = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 90, 210, 290, 25, hwnd, (HMENU)IDC_TITLE, NULL, NULL);
            SendMessage(hTitle, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            CreateWindow("STATIC", "Contenuto:", WS_CHILD | WS_VISIBLE, 20, 245, 70, 25, hwnd, NULL, NULL, NULL);
            hContent = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL, 90, 245, 290, 60, hwnd, (HMENU)IDC_CONTENT, NULL, NULL);
            SendMessage(hContent, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            HWND hBtnAdd = CreateWindow("BUTTON", "Aggiungi", WS_CHILD | WS_VISIBLE | BS_ICON, 20, 320, 80, 30, hwnd, (HMENU)IDC_ADD, NULL, NULL);
            SendMessage(hBtnAdd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconAdd);
            
            HWND hBtnEdit = CreateWindow("BUTTON", "Modifica", WS_CHILD | WS_VISIBLE | BS_ICON, 110, 320, 80, 30, hwnd, (HMENU)IDC_EDIT, NULL, NULL);
            SendMessage(hBtnEdit, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconEdit);
            
            HWND hBtnDelete = CreateWindow("BUTTON", "Elimina", WS_CHILD | WS_VISIBLE | BS_ICON, 200, 320, 80, 30, hwnd, (HMENU)IDC_DELETE, NULL, NULL);
            SendMessage(hBtnDelete, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconDelete);
            
            HWND hBtnSave = CreateWindow("BUTTON", "Salva ed Esci", WS_CHILD | WS_VISIBLE | BS_ICON, 290, 320, 100, 30, hwnd, (HMENU)IDC_SAVE, NULL, NULL);
            SendMessage(hBtnSave, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconSave);
            
            // Set fonts for buttons and statics
            EnumChildWindows(hwnd, (WNDENUMPROC)SetFontProc, (LPARAM)hFont);
            
            update_list(hList);
            break;
        }
        case WM_CTLCOLORSTATIC: {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, RGB(255, 255, 224)); // Light yellow background
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 224));
        }
        case WM_CTLCOLOREDIT: {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, RGB(255, 255, 255)); // White for edits
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 255));
        }
        case WM_CTLCOLORLISTBOX: {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, RGB(255, 255, 255));
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 255));
        }
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
            DeleteObject(hFont);
            DestroyIcon(hIconAdd);
            DestroyIcon(hIconEdit);
            DestroyIcon(hIconDelete);
            DestroyIcon(hIconSave);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

BOOL CALLBACK SetFontProc(HWND hwnd, LPARAM lParam) {
    SendMessage(hwnd, WM_SETFONT, lParam, TRUE);
    return TRUE;
}