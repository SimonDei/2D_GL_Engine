//
// Created by a00007 on 10.12.2020.
//

#ifndef UNTITLED_MATH_H
#define UNTITLED_MATH_H

#include "macros.h"
#include "types.h"
#include "results.h"

EXPORT XD_RESULT identity_matrix(
    _Out_ XD_MATRIX4 matrix);

EXPORT XD_RESULT ortho_matrix(
    _In_ XD_FLOAT top,
    _In_ XD_FLOAT bottom,
    _In_ XD_FLOAT left,
    _In_ XD_FLOAT right,
    _Out_ XD_MATRIX4 matrix);

EXPORT XD_RESULT scale_matrix_2d(
    _In_ XD_FLOAT x,
    _In_ XD_FLOAT y,
    _Out_ XD_MATRIX4 matrix);

EXPORT XD_RESULT scale_matrix_3d(
    _In_ XD_FLOAT x,
    _In_ XD_FLOAT y,
    _In_ XD_FLOAT z,
    _Out_ XD_MATRIX4 matrix);

EXPORT XD_RESULT  translate_matrix_2d(
    _In_ XD_FLOAT x,
    _In_ XD_FLOAT y,
    _Out_ XD_MATRIX4 matrix);

EXPORT XD_RESULT translate_matrix_3d(
    _In_ XD_FLOAT x,
    _In_ XD_FLOAT y,
    _In_ XD_FLOAT z,
    _Out_ XD_MATRIX4 matrix);

EXPORT XD_RESULT rotate_matrix_z(
    _In_ XD_FLOAT rotation,
    _Out_ XD_MATRIX4 matrix);

EXPORT XD_RESULT rotate_around_center_z(
    _In_ XD_FLOAT rotation,
    _Out_ XD_MATRIX4 matrix);

EXPORT XD_RESULT multiply_matrix(
    _In_ XD_MATRIX4 first,
    _In_ XD_MATRIX4 second,
    _Out_ XD_MATRIX4 output);

EXPORT XD_RESULT invert_matrix(
    _In_ XD_MATRIX4 matrix,
    _Out_ XD_MATRIX4 output);

#endif //UNTITLED_MATH_H
