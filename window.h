//
// Created by a00007 on 09.12.2020.
//

#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H

#include "macros.h"
#include "types.h"
#include "results.h"
#include "keycodes.h"

#include <Windows.h>

typedef struct _WINDOW {
    XD_UINT16 _width;
    XD_UINT16 _height;
    XD_STRING _title;
    HWND      _hWnd;
    HINSTANCE _hInstance;
} XD_WINDOW;

EXPORT XD_RESULT create_window(
    _In_ XD_UINT16 width,
    _In_ XD_UINT16 height,
    _In_ XD_STRING title,
    _Out_ PTR(XD_WINDOW) p_window);

EXPORT XD_BOOL is_open(
    _In_ XD_WINDOW window);

EXPORT XD_BOOL is_key_pressed(
    _In_ XD_KEY key);

EXPORT XD_RESULT close_window(
    NO_ARGUMENTS);

EXPORT XD_RESULT destroy_window(
    _In_ XD_WINDOW window);

#endif //UNTITLED_WINDOW_H
