#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>
#include <windowsx.h>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "renderer.h"

struct WindowContext
{
    int m_width = 800, m_height = 800;
    HDC m_hdc_back_buffer;
    HBITMAP m_hbitmap;
    HBITMAP m_old_hbitmap;
};
WindowContext w_ctx;

SoftRas::Renderer rdr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowStatus(float fps);
void ClearConsole();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t m_title[] = L"Soft Rasterizer";

    AllocConsole();
    FILE* file = nullptr;
    freopen_s(&file, "CONIN$", "r", stdin);
    freopen_s(&file, "CONOUT$", "w", stdout);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = m_title;

    RegisterClass(&wc);

    RECT m_size = { 0, 0, w_ctx.m_width, w_ctx.m_height };
    HWND m_hwnd = CreateWindowEx(
        0, m_title, m_title, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        m_size.right - m_size.left + 15, m_size.bottom - m_size.top + 38,
        nullptr, nullptr, hInstance, nullptr
    );
    if (!m_hwnd)
    {
        return 0;
    }

    ShowWindow(m_hwnd, nCmdShow);

    MSG msg = {};
    ZeroMemory(&msg, sizeof(msg));

    // main loop
    const float update_duration = 1.0f;
    float accu = 0.0f, dura = 0.0f;
    int frame = 0;
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // show status and compute duration
            if (accu >= update_duration) {
                ClearConsole();
                ShowStatus((float)frame / accu);
                accu = 0.0f;
                frame = 0;
            }
            rdr.tick(dura);
            auto t1 = std::chrono::high_resolution_clock::now();
            rdr.draw();
            auto t2 = std::chrono::high_resolution_clock::now();
            dura = (float)(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) / 1000.0f;
            accu += dura;
            frame++;

            InvalidateRect(m_hwnd, nullptr, true);
            UpdateWindow(m_hwnd);
        }
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
        SoftRas::g_ctx.init(w_ctx.m_width, w_ctx.m_height);
        rdr.init();

        BITMAPINFOHEADER bmpinfo{};
        bmpinfo.biSize = sizeof(BITMAPINFOHEADER);
        bmpinfo.biWidth = w_ctx.m_width;
        bmpinfo.biHeight = -w_ctx.m_height;
        bmpinfo.biPlanes = 1;
        bmpinfo.biBitCount = 32;
        bmpinfo.biSizeImage = w_ctx.m_width * w_ctx.m_height * 4;

        w_ctx.m_hdc_back_buffer = CreateCompatibleDC(nullptr);
        hdc = GetDC(hwnd);
        void* temp;
        w_ctx.m_hbitmap = CreateDIBSection(
            nullptr, (BITMAPINFO*)&bmpinfo, DIB_RGB_COLORS,
            &temp,
            nullptr, 0
        );
        SoftRas::g_ctx.getFramebuffer()->applyExternalBuffer(0, (SoftRas::uint32*)temp);
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
        BitBlt(ps.hdc, 0, 0, w_ctx.m_width, w_ctx.m_height, w_ctx.m_hdc_back_buffer, 0, 0, SRCCOPY);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_KEYDOWN:
        rdr.keyDown(wParam);
        return 0;
    case WM_KEYUP:
        rdr.keyUp(wParam);
        return 0;
    case WM_LBUTTONDOWN:
        SetCapture(hwnd);
        rdr.mouseDown(0);
        return 0;
    case WM_LBUTTONUP:
        ReleaseCapture();
        rdr.mouseUp(0);
        return 0;
    case WM_RBUTTONDOWN:
        rdr.mouseDown(1);
        return 0;
    case WM_RBUTTONUP:
        rdr.mouseUp(1);
        return 0;
    case WM_MOUSEMOVE:
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        rdr.mouseMove(xPos, yPos);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void ShowStatus(float fps) {
    auto& cam = rdr.m_scene.m_camera;
    auto& trs = rdr.m_scene.m_trans;
    std::cout << std::fixed << std::setprecision(3)
        << "========== Status ==========" << std::endl
        << "FPS: " << std::setw(6) << fps << "\t"
        << "Frames: " << rdr.m_frames << std::endl
        << "Camera position: " << std::endl
        << "X " << std::setw(6) << cam.pos.x << " Y " << std::setw(6) << cam.pos.y << " Z " << std::setw(6) << cam.pos.z << std::endl
        << "Camera direction: " << std::endl
        << "X " << std::setw(6) << cam.front.x << " Y " << std::setw(6) << cam.front.y << " Z " << std::setw(6) << cam.front.z << std::endl;
    for (int i = 0; i < rdr.m_scene.m_insts.size(); i++) {
        auto& tr = rdr.m_scene.m_trans[rdr.m_scene.m_insts[i].trans_id].trans;
        std::cout << "-- " << i + 1 << ": " << rdr.m_scene.m_insts[i].name << std::endl
            << "X " << std::setw(6) << tr.x << " Y " << std::setw(6) << tr.y << " Z " << std::setw(6) << tr.z << std::endl;
    }
    if (rdr.m_control_obj == 0) {
        std::cout << "Controling camera" << "                    " << std::endl;
    }
    else {
        std::cout << "Controling object " << rdr.m_control_obj << ": " << rdr.m_scene.m_insts[rdr.m_control_obj - 1].name << "            " << std::endl;
    }
}

void ClearConsole()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces 
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;*/

    /* Fill the entire buffer with the current colors and attributes 
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;*/

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}