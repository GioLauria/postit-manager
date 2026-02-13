#include "postit.h"
#include <dwmapi.h>  // For Windows 11 Mica effect

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    load_postits();
    WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH), NULL, "PostItManager", NULL};
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindowEx(WS_EX_TOPMOST, "PostItManager", "Gestore Post-It", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 420, NULL, NULL, hInstance, NULL);
    
    // Enable Mica effect for Windows 11 (commented out if not available)
    // enum DWM_SYSTEMBACKDROP_TYPE backdrop = DWMSBT_MAINWINDOW;
    // DwmSetWindowAttribute(hwnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdrop, sizeof(backdrop));
    
    // Center the window
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int x = (screenWidth - width) / 2;
    int y = (screenHeight - height) / 2;
    SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}