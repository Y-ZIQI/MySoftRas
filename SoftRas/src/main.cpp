#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>

#include "context.h"

struct WindowContext
{
    int m_width = 800, m_height = 800;
    HDC m_hdc_back_buffer;
    HBITMAP m_hbitmap;
    HBITMAP m_old_hbitmap;
};
WindowContext w_ctx;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t m_title[] = L"Soft Rasterizer";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = m_title;

    RegisterClass(&wc);

    RECT m_size = { 0, 0, w_ctx.m_width, w_ctx.m_height };
    HWND m_hwnd = CreateWindowEx(
        0, m_title, m_title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        m_size.right - m_size.left, m_size.bottom - m_size.top,
        nullptr, nullptr, hInstance, nullptr
    );
    if (!m_hwnd)
    {
        return 0;
    }

    ShowWindow(m_hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (uMsg)
    {
    case WM_CREATE:
    {
        SoftRas::g_ctx.init();
        BITMAPINFOHEADER bmpinfo{};
        bmpinfo.biSize = sizeof(BITMAPINFOHEADER);
        bmpinfo.biWidth = w_ctx.m_width;
        bmpinfo.biHeight = -w_ctx.m_height;
        bmpinfo.biPlanes = 1;
        bmpinfo.biBitCount = 32;
        bmpinfo.biSizeImage = w_ctx.m_width * w_ctx.m_height * 4;

        w_ctx.m_hdc_back_buffer = CreateCompatibleDC(nullptr);
        hdc = GetDC(hwnd);
        w_ctx.m_hbitmap = CreateDIBSection(
            nullptr, (BITMAPINFO*)&bmpinfo, DIB_RGB_COLORS,
            reinterpret_cast<void**>(&SoftRas::g_ctx.getDefaultFramebuffer()),
            nullptr, 0
        );
        if (!w_ctx.m_hbitmap) {
            return 0;
        }
        w_ctx.m_old_hbitmap = (HBITMAP)SelectObject(w_ctx.m_hdc_back_buffer, w_ctx.m_hbitmap);
        ReleaseDC(hwnd, hdc);
        break;
    }
    case WM_DESTROY:
        SelectObject(w_ctx.m_hdc_back_buffer, w_ctx.m_old_hbitmap);
        DeleteDC(w_ctx.m_hdc_back_buffer);
        DeleteObject(w_ctx.m_old_hbitmap);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        SoftRas::g_ctx.testPaint();
        BitBlt(ps.hdc, 0, 0, w_ctx.m_width, w_ctx.m_height, w_ctx.m_hdc_back_buffer, 0, 0, SRCCOPY);

        EndPaint(hwnd, &ps);
        return 0;
    }

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}