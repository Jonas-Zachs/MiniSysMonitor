#include "pch.h"
#include "WindowProc.h"

constexpr int WINDOW_WIDTH = 250;
constexpr int WINDOW_HEIGHT = 100;

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
) {
    const wchar_t CLASS_NAME[] = L"SysMonWidgetClass";

    // Setup the window class attributes
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = CLASS_NAME;

    // Register the window class
    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, L"Window class registration failed!", L"Error", MB_ICONERROR);
        return -1;
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    // Create a topmost, layered popup window
    HWND hWnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED,
        CLASS_NAME,
        L"System Monitor",
        WS_POPUP,
        screenWidth - WINDOW_WIDTH - 10, 10, WINDOW_WIDTH, WINDOW_HEIGHT,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) {
        MessageBox(nullptr, L"Window creation failed!", L"Error", MB_ICONERROR);
        return -1;
    }

    // Set window transparency to 85% opacity
    SetLayeredWindowAttributes(hWnd, 0, 215, LWA_ALPHA);
    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    // Main message loop
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}