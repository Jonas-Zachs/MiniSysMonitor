#include "pch.h"
#include "WindowProc.h"
#include "CpuUsage.h"
#include "MemoryUsage.h"
#include "Renderer.h"

// Window procedure for handling messages
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static SYSTEMTIME sysTime;
    static double cpuUsage = 0.0;
    static double ramUsedGB = 0.0;
    static double ramTotalGB = 0.0;

    switch (message) {
    case WM_CREATE: {
        // Set a timer to update system info every 1000 ms
        SetTimer(hWnd, 1, 1000, NULL);

        // Create and store a custom font
        HFONT hFont = CreateFont(
            16, 0, 0, 0,
            FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            DEFAULT_PITCH, L"Arial"
        );
        SetProp(hWnd, L"CustomFont", hFont);
        break;
    }

    case WM_TIMER: {
        if (wParam == 1) {
            // Update the local time, memory usage, and CPU usage
            GetLocalTime(&sysTime);
            GetMemoryUsage(ramUsedGB, ramTotalGB);
            cpuUsage = CalculateCpuUsage();
            InvalidateRect(hWnd, NULL, FALSE); // Do not clear background
        }
        break;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // Draw the overlay with the updated system information
        DrawOverlay(hdc, sysTime, cpuUsage, ramUsedGB, ramTotalGB);
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_DESTROY: {
        // Kill the timer and clean up resources
        KillTimer(hWnd, 1);

        // Delete the custom font
        HFONT hFont = (HFONT)GetProp(hWnd, L"CustomFont");
        if (hFont) DeleteObject(hFont);

        PostQuitMessage(0);
        break;
    }

    case WM_NCHITTEST: {
        return HTCAPTION; // Make the window draggable
    }

    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
    return 0;
}