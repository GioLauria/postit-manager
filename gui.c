#include "postit.h"

HWND hList, hTitle, hContent;
HFONT hFont;
HICON hIconAdd, hIconEdit, hIconDelete, hIconSave;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI");
            
            // Load icons
            hIconAdd = LoadIcon(NULL, IDI_ASTERISK);
            hIconEdit = LoadIcon(NULL, IDI_EXCLAMATION);
            hIconDelete = LoadIcon(NULL, IDI_HAND);
            hIconSave = LoadIcon(NULL, IDI_WINLOGO);
            
            hList = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | WS_BORDER, 20, 20, 360, 180, hwnd, (HMENU)IDC_LIST, NULL, NULL);
            SendMessage(hList, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            CreateWindow("STATIC", "Titolo:", WS_CHILD | WS_VISIBLE, 20, 210, 80, 30, hwnd, NULL, NULL, NULL);
            hTitle = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 100, 210, 280, 30, hwnd, (HMENU)IDC_TITLE, NULL, NULL);
            SendMessage(hTitle, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            CreateWindow("STATIC", "Contenuto:", WS_CHILD | WS_VISIBLE, 20, 250, 80, 30, hwnd, NULL, NULL, NULL);
            hContent = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL, 100, 250, 280, 70, hwnd, (HMENU)IDC_CONTENT, NULL, NULL);
            SendMessage(hContent, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Modern flat buttons
            CreateWindow("BUTTON", "➕ Aggiungi", WS_CHILD | WS_VISIBLE | BS_FLAT, 20, 330, 100, 35, hwnd, (HMENU)IDC_ADD, NULL, NULL);
            CreateWindow("BUTTON", "✏️ Modifica", WS_CHILD | WS_VISIBLE | BS_FLAT, 130, 330, 100, 35, hwnd, (HMENU)IDC_EDIT, NULL, NULL);
            CreateWindow("BUTTON", "🗑️ Elimina", WS_CHILD | WS_VISIBLE | BS_FLAT, 240, 330, 100, 35, hwnd, (HMENU)IDC_DELETE, NULL, NULL);
            CreateWindow("BUTTON", "💾 Salva & Esci", WS_CHILD | WS_VISIBLE | BS_FLAT, 350, 330, 120, 35, hwnd, (HMENU)IDC_SAVE, NULL, NULL);
            
            // Set fonts for buttons and statics
            EnumChildWindows(hwnd, (WNDENUMPROC)SetFontProc, (LPARAM)hFont);
            
            update_list(hList);
            break;
        }
        case WM_CTLCOLORSTATIC: {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, RGB(45, 45, 48)); // Dark background
            SetTextColor(hdc, RGB(255, 255, 255)); // White text
            return (LRESULT)CreateSolidBrush(RGB(45, 45, 48));
        }
        case WM_CTLCOLOREDIT: {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, RGB(30, 30, 30)); // Darker edit background
            SetTextColor(hdc, RGB(255, 255, 255));
            return (LRESULT)CreateSolidBrush(RGB(30, 30, 30));
        }
        case WM_CTLCOLORLISTBOX: {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, RGB(30, 30, 30));
            SetTextColor(hdc, RGB(255, 255, 255));
            return (LRESULT)CreateSolidBrush(RGB(30, 30, 30));
        }
        case WM_CTLCOLORBTN: {
            HDC hdc = (HDC)wParam;
            SetBkColor(hdc, RGB(63, 63, 70)); // Button background
            SetTextColor(hdc, RGB(255, 255, 255));
            return (LRESULT)CreateSolidBrush(RGB(63, 63, 70));
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