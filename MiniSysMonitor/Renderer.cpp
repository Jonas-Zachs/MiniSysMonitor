#include "pch.h"
#include "Renderer.h"

// Draws the overlay with system information using double buffering
void DrawOverlay(HDC hdc, const SYSTEMTIME& time, double cpuUsage, double ramUsed, double ramTotal) {
    HWND hWnd = WindowFromDC(hdc);
    RECT rect;
    GetClientRect(hWnd, &rect);

    // Create a memory device context for double buffering
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hBmp = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
    SelectObject(memDC, hBmp);

    // Fill the background with black
    FillRect(memDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

    // Select the custom font
    HFONT hFont = (HFONT)GetProp(hWnd, L"CustomFont");
    SelectObject(memDC, hFont);
    SetTextColor(memDC, RGB(255, 255, 255));
    SetBkMode(memDC, TRANSPARENT);

    // Draw the system time
    wchar_t text[256];
    swprintf_s(text, L"Time: %02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
    TextOut(memDC, 10, 10, text, (int)wcslen(text));

    // Draw the CPU usage
    swprintf_s(text, L"CPU: %.1f%%", cpuUsage);
    TextOut(memDC, 10, 35, text, (int)wcslen(text));

    // Draw the memory usage
    swprintf_s(text, L"RAM: %.2f/%.2f GB", ramUsed, ramTotal);
    TextOut(memDC, 10, 60, text, (int)wcslen(text));

    // Copy the buffer to the screen
    BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

    // Clean up resources
    DeleteObject(hBmp);
    DeleteDC(memDC);
}