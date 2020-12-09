//
// Created by a00007 on 09.12.2020.
//

#ifndef UNTITLED_RENDERER_H
#define UNTITLED_RENDERER_H

#include "macros.h"
#include "types.h"
#include "results.h"

#include <Windows.h>

typedef struct _RENDERER {
    HDC        _hDc;
    HGLRC      _hGlrc;
    XD_UINT16  _texture_index;
    XD_TEXTURE _textures[1024];
} XD_RENDERER;

EXPORT XD_RESULT create_renderer(
    _Out_ PTR(XD_RENDERER) p_renderer);

EXPORT XD_RESULT clear(
    _In_ XD_UINT8 red,
    _In_ XD_UINT8 green,
    _In_ XD_UINT8 blue);

EXPORT XD_RESULT present(
    _In_ XD_RENDERER renderer);

EXPORT XD_RESULT draw_rect(
    _In_ XD_FLOAT x,
    _In_ XD_FLOAT y,
    _In_ XD_FLOAT width,
    _In_ XD_FLOAT height);

EXPORT XD_RESULT set_vertices(
    _In_ XD_FLOAT vertices[]);

EXPORT XD_RESULT load_texture(
    _In_ XD_STRING file_path,
    _Out_ PTR(XD_TEXTURE) p_texture,
    _In_ PTR(XD_RENDERER) p_renderer);

EXPORT XD_RESULT set_texture(
    _In_ XD_TEXTURE texture);

EXPORT XD_RESULT destroy_renderer(
    _In_ XD_RENDERER renderer);

#endif //UNTITLED_RENDERER_H
