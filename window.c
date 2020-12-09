//
// Created by a00007 on 09.12.2020.
//

#include "window.h"

#include <GL/gl.h>

static HDC g_hdc;
static HGLRC g_hglrc;
static XD_BOOL g_running;

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT msg,
                         WPARAM wParam,
                         LPARAM lParam) {
    switch (msg) {
        case WM_SIZE:
            glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            g_running = FALSE;
            break;
        default:
            break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

XD_RESULT create_window(XD_UINT16 width,
                        XD_UINT16 height,
                        XD_STRING title,
                        PTR(XD_WINDOW) p_window) {
    CLEAR_MEMORY(p_window);
    p_window->_width = width;
    p_window->_height = height;
    p_window->_title = title;
    p_window->_hInstance = GetModuleHandle(NULL);
    p_window->_hWnd = NULL;

    WNDCLASSEX wndEx;
    CLEAR_MEMORY(&wndEx);
    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.style = CS_VREDRAW | CS_HREDRAW;
    wndEx.lpfnWndProc = WndProc;
    wndEx.hInstance = p_window->_hInstance;
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.hIcon = (HICON) LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED);
    wndEx.hCursor = (HCURSOR) LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
    wndEx.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wndEx.lpszMenuName = NULL;
    wndEx.lpszClassName = TEXT("XDApp");
    wndEx.hIconSm = NULL;

    if (!RegisterClassEx(&wndEx)) {
        return XD_FAILED;
    }

    p_window->_hWnd = CreateWindow(TEXT("XDApp"), "XD window", WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, p_window->_hInstance, NULL);
    if (p_window->_hWnd == NULL) {
        return XD_FAILED;
    }

    ShowWindow(p_window->_hWnd, SW_SHOWNORMAL);
    UpdateWindow(p_window->_hWnd);

    g_hdc = GetDC(p_window->_hWnd);
    if (g_hdc == NULL) {
        return XD_FAILED;
    }

    PIXELFORMATDESCRIPTOR pfd;
    CLEAR_MEMORY(&pfd);
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 32;
    pfd.cStencilBits = 8;

    int pixel_format = ChoosePixelFormat(g_hdc, &pfd);
    if (!SetPixelFormat(g_hdc, pixel_format, &pfd)) {
        return XD_FAILED;
    }

    g_hglrc = wglCreateContext(g_hdc);
    if (g_hglrc == NULL) {
        return XD_FAILED;
    }

    if (!wglMakeCurrent(g_hdc, g_hglrc)) {
        return XD_FAILED;
    }

    g_running = TRUE;

    return XD_SUCCESS;
}

XD_BOOL is_open(XD_WINDOW window) {
    MSG msg;
    while (PeekMessage(&msg, window._hWnd, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return g_running;
}

XD_BOOL is_key_pressed(XD_KEY key) {
    if (GetAsyncKeyState(key) & 0x8000) {
        return TRUE;
    }
    return FALSE;
}

XD_RESULT close_window(NO_ARGUMENTS) {
    g_running = FALSE;

    return XD_SUCCESS;
}

XD_RESULT destroy_window(XD_WINDOW window) {
    wglMakeCurrent(g_hdc, NULL);
    wglDeleteContext(g_hglrc);
    ReleaseDC(window._hWnd, g_hdc);

    CloseWindow(window._hWnd);
    DestroyWindow(window._hWnd);

    UnregisterClass(TEXT("XDApp"), window._hInstance);

    PostQuitMessage(0);

    return XD_SUCCESS;
}
