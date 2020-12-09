//
// Created by a00007 on 09.12.2020.
//

#ifndef UNTITLED_SHADER_H
#define UNTITLED_SHADER_H

#include "macros.h"
#include "types.h"
#include "results.h"

typedef struct _SHADER {
    XD_UINT32 _program_id;
    XD_UINT32 _vertex_shader_id;
    XD_UINT32 _fragment_shader_id;
    XD_UINT16 _buffer_index;
    XD_UINT32 _buffers[1024];
} XD_SHADER;

EXPORT XD_RESULT create_shader(
    _In_ XD_STRING vertex_shader_path,
    _In_ XD_STRING fragment_shader_path,
    _Out_ PTR(XD_SHADER) p_shader);

EXPORT XD_RESULT destroy_shader(
    _In_ PTR(XD_SHADER) p_shader);

#endif //UNTITLED_SHADER_H
