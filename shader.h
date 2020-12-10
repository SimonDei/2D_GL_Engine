//
// Created by a00007 on 09.12.2020.
//

#ifndef UNTITLED_SHADER_H
#define UNTITLED_SHADER_H

#include "macros.h"
#include "types.h"
#include "results.h"
#include "math.h"

typedef struct _SHADER {
    XD_UINT32 _program_id;
    XD_UINT32 _vertex_array_id;
    XD_UINT32 _vertex_shader_id;
    XD_UINT32 _fragment_shader_id;
    XD_UINT32 _indicies_count;
    XD_UINT16 _buffer_index;
    XD_UINT32 _buffers[1024];
} XD_SHADER;

EXPORT XD_RESULT create_shader(
    _In_ XD_STRING vertex_shader_path,
    _In_ XD_STRING fragment_shader_path,
    _Out_ PTR(XD_SHADER) p_shader);

EXPORT XD_RESULT set_vertex_attrib(
    _In_ PTR(XD_SHADER) p_shader,
    _In_ XD_UINT8 position,
    _In_ XD_UINT8 vertex_size,
    _In_ PTR(XD_FLOAT) p_data,
    _In_ XD_UINT32 data_size);

EXPORT XD_RESULT set_indicies(
    _In_ PTR(XD_SHADER) p_shader,
    _In_ XD_UINT8 vertex_size,
    _In_ PTR(XD_UINT32) p_data,
    _In_ XD_UINT32 data_size);

EXPORT XD_RESULT set_uniform(
    _In_ XD_SHADER shader,
    _In_ XD_STRING name,
    _In_ XD_MATRIX4 matrix);

EXPORT XD_RESULT execute_shader(
    _In_ XD_SHADER shader);

EXPORT XD_RESULT destroy_shader(
    _In_ XD_SHADER shader);

#endif //UNTITLED_SHADER_H
