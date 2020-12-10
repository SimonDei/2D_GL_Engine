//
// Created by a00007 on 10.12.2020.
//

#include "math.h"

#include <memory.h>
#include <math.h>

XD_RESULT identity_matrix(XD_MATRIX4 matrix) {
    memset(matrix, 0, sizeof(XD_MATRIX4));

    matrix[0][0] = 1.0f;
    matrix[1][1] = 1.0f;
    matrix[2][2] = 1.0f;
    matrix[3][3] = 1.0f;

    return XD_SUCCESS;
}

XD_RESULT ortho_matrix(XD_FLOAT top,
                       XD_FLOAT bottom,
                       XD_FLOAT left,
                       XD_FLOAT right,
                       XD_MATRIX4 matrix) {
    float rl, tb, fn;

    memset(matrix, 0, sizeof(XD_MATRIX4));

    rl =  1.0f / (right - left);
    tb =  1.0f / (top   - bottom);
    fn = -1.0f / (1.0f  - 0.0f);

    matrix[0][0] =   2.0f * rl;
    matrix[1][1] =   2.0f * tb;
    matrix[2][2] =   2.0f * fn;
    matrix[3][0] = -(right + left)   * rl;
    matrix[3][1] = -(top   + bottom) * tb;
    matrix[3][2] =  (1.0f  + 0.0f)   * fn;
    matrix[3][3] =   1.0f;

    return XD_SUCCESS;
}

XD_RESULT scale_matrix_2d(XD_FLOAT x,
                          XD_FLOAT y,
                          XD_MATRIX4 matrix){
    matrix[0][0] = matrix[0][0] * x;
    matrix[0][1] = matrix[0][1] * x;
    matrix[0][2] = matrix[0][2] * x;
    matrix[0][3] = matrix[0][3] * x;

    matrix[1][0] = matrix[1][0] * y;
    matrix[1][1] = matrix[1][1] * y;
    matrix[1][2] = matrix[1][2] * y;
    matrix[1][3] = matrix[1][3] * y;

    matrix[2][0] = matrix[2][0];
    matrix[2][1] = matrix[2][1];
    matrix[2][2] = matrix[2][2];
    matrix[2][3] = matrix[2][3];

    matrix[3][0] = matrix[3][0];
    matrix[3][1] = matrix[3][1];
    matrix[3][2] = matrix[3][2];
    matrix[3][3] = matrix[3][3];

    return XD_SUCCESS;
}

XD_RESULT scale_matrix_3d(XD_FLOAT x,
                          XD_FLOAT y,
                          XD_FLOAT z,
                          XD_MATRIX4 matrix) {
    matrix[0][0] = matrix[0][0] * x;
    matrix[0][1] = matrix[0][1] * x;
    matrix[0][2] = matrix[0][2] * x;
    matrix[0][3] = matrix[0][3] * x;

    matrix[1][0] = matrix[1][0] * y;
    matrix[1][1] = matrix[1][1] * y;
    matrix[1][2] = matrix[1][2] * y;
    matrix[1][3] = matrix[1][3] * y;

    matrix[2][0] = matrix[2][0] * z;
    matrix[2][1] = matrix[2][1] * z;
    matrix[2][2] = matrix[2][2] * z;
    matrix[2][3] = matrix[2][3] * z;

    matrix[3][0] = matrix[3][0];
    matrix[3][1] = matrix[3][1];
    matrix[3][2] = matrix[3][2];
    matrix[3][3] = matrix[3][3];

    return XD_SUCCESS;
}

XD_RESULT translate_matrix_2d(XD_FLOAT x,
                              XD_FLOAT y,
                              XD_MATRIX4 matrix) {
    XD_FLOAT vec1[4], vec2[4];
    memset(vec1, 0, sizeof(XD_FLOAT[4]));
    memset(vec2, 0, sizeof(XD_FLOAT[4]));

    vec1[0] = matrix[0][0] * x;
    vec1[1] = matrix[0][1] * x;
    vec1[2] = matrix[0][2] * x;
    vec1[3] = matrix[0][3] * x;

    vec2[0] = matrix[1][0] * y;
    vec2[1] = matrix[1][1] * y;
    vec2[2] = matrix[1][2] * y;
    vec2[3] = matrix[1][3] * y;

    matrix[3][0] = vec1[0] + matrix[3][0];
    matrix[3][1] = vec1[1] + matrix[3][1];
    matrix[3][2] = vec1[2] + matrix[3][2];
    matrix[3][3] = vec1[3] + matrix[3][3];

    matrix[3][0] = vec2[0] + matrix[3][0];
    matrix[3][1] = vec2[1] + matrix[3][1];
    matrix[3][2] = vec2[2] + matrix[3][2];
    matrix[3][3] = vec2[3] + matrix[3][3];

    return XD_SUCCESS;
}

XD_RESULT translate_matrix_3d(XD_FLOAT x,
                              XD_FLOAT y,
                              XD_FLOAT z,
                              XD_MATRIX4 matrix) {
    XD_FLOAT vec1[4], vec2[4], vec3[4];
    memset(vec1, 0, sizeof(XD_FLOAT[4]));
    memset(vec2, 0, sizeof(XD_FLOAT[4]));
    memset(vec3, 0, sizeof(XD_FLOAT[4]));

    vec1[0] = matrix[0][0] * x;
    vec1[1] = matrix[0][1] * x;
    vec1[2] = matrix[0][2] * x;
    vec1[3] = matrix[0][3] * x;

    vec2[0] = matrix[1][0] * y;
    vec2[1] = matrix[1][1] * y;
    vec2[2] = matrix[1][2] * y;
    vec2[3] = matrix[1][3] * y;

    vec3[0] = matrix[2][0] * z;
    vec3[1] = matrix[2][1] * z;
    vec3[2] = matrix[2][2] * z;
    vec3[3] = matrix[2][3] * z;

    matrix[3][0] = vec1[0] + matrix[3][0];
    matrix[3][1] = vec1[1] + matrix[3][1];
    matrix[3][2] = vec1[2] + matrix[3][2];
    matrix[3][3] = vec1[3] + matrix[3][3];

    matrix[3][0] = vec2[0] + matrix[3][0];
    matrix[3][1] = vec2[1] + matrix[3][1];
    matrix[3][2] = vec2[2] + matrix[3][2];
    matrix[3][3] = vec2[3] + matrix[3][3];

    matrix[3][0] = vec3[0] + matrix[3][0];
    matrix[3][1] = vec3[1] + matrix[3][1];
    matrix[3][2] = vec3[2] + matrix[3][2];
    matrix[3][3] = vec3[3] + matrix[3][3];

    return XD_SUCCESS;
}

XD_RESULT rotate_matrix_z(XD_FLOAT rotation,
                          XD_MATRIX4 matrix){
    XD_MATRIX4 rot;
    identity_matrix(rot);

    XD_FLOAT radian_rotation = rotation * (XD_FLOAT) M_PI / 180.0f;

    XD_FLOAT c = cosf(radian_rotation);
    XD_FLOAT s = sinf(radian_rotation);

    rot[0][0] = c;
    rot[0][1] = s;
    rot[1][0] = -s;
    rot[1][1] = c;

    XD_FLOAT a00 = matrix[0][0], a01 = matrix[0][1], a02 = matrix[0][2], a03 = matrix[0][3],
             a10 = matrix[1][0], a11 = matrix[1][1], a12 = matrix[1][2], a13 = matrix[1][3],
             a20 = matrix[2][0], a21 = matrix[2][1], a22 = matrix[2][2], a23 = matrix[2][3],
             a30 = matrix[3][0], a31 = matrix[3][1], a32 = matrix[3][2], a33 = matrix[3][3];

    XD_FLOAT b00 = rot[0][0], b01 = rot[0][1], b02 = rot[0][2],
             b10 = rot[1][0], b11 = rot[1][1], b12 = rot[1][2],
             b20 = rot[2][0], b21 = rot[2][1], b22 = rot[2][2];

    matrix[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
    matrix[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
    matrix[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
    matrix[0][3] = a03 * b00 + a13 * b01 + a23 * b02;

    matrix[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
    matrix[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
    matrix[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
    matrix[1][3] = a03 * b10 + a13 * b11 + a23 * b12;

    matrix[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
    matrix[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
    matrix[2][2] = a02 * b20 + a12 * b21 + a22 * b22;
    matrix[2][3] = a03 * b20 + a13 * b21 + a23 * b22;

    matrix[3][0] = a30;
    matrix[3][1] = a31;
    matrix[3][2] = a32;
    matrix[3][3] = a33;

    return XD_SUCCESS;
}

XD_RESULT rotate_around_center_z(XD_FLOAT rotation,
                                 XD_MATRIX4 matrix) {
    XD_MATRIX4 rot;
    identity_matrix(rot);
    translate_matrix_2d(0.5f, 0.5f, rot);
    rotate_matrix_z(rotation, rot);
    translate_matrix_2d(-0.5f, -0.5f, rot);

    multiply_matrix(matrix, rot, matrix);

    return XD_FAILED;
}

XD_RESULT multiply_matrix(XD_MATRIX4 first,
                          XD_MATRIX4 second,
                          XD_MATRIX4 output) {
    XD_FLOAT a00 = first[0][0], a01 = first[0][1], a02 = first[0][2], a03 = first[0][3],
             a10 = first[1][0], a11 = first[1][1], a12 = first[1][2], a13 = first[1][3],
             a20 = first[2][0], a21 = first[2][1], a22 = first[2][2], a23 = first[2][3],
             a30 = first[3][0], a31 = first[3][1], a32 = first[3][2], a33 = first[3][3];

    XD_FLOAT b00 = second[0][0], b01 = second[0][1], b02 = second[0][2], b03 = second[0][3],
             b10 = second[1][0], b11 = second[1][1], b12 = second[1][2], b13 = second[1][3],
             b20 = second[2][0], b21 = second[2][1], b22 = second[2][2], b23 = second[2][3],
             b30 = second[3][0], b31 = second[3][1], b32 = second[3][2], b33 = second[3][3];

    output[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
    output[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
    output[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
    output[0][3] = a03 * b00 + a13 * b01 + a23 * b02;

    output[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
    output[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
    output[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
    output[1][3] = a03 * b10 + a13 * b11 + a23 * b12;

    output[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
    output[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
    output[2][2] = a02 * b20 + a12 * b21 + a22 * b22;
    output[2][3] = a03 * b20 + a13 * b21 + a23 * b22;

    output[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
    output[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
    output[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
    output[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;

    return XD_SUCCESS;
}

XD_RESULT invert_matrix(XD_MATRIX4 matrix,
                        XD_MATRIX4 output) {
    XD_FLOAT t[6];
    XD_FLOAT det;
    XD_FLOAT a = matrix[0][0], b = matrix[0][1], c = matrix[0][2], d = matrix[0][3],
             e = matrix[1][0], f = matrix[1][1], g = matrix[1][2], h = matrix[1][3],
             i = matrix[2][0], j = matrix[2][1], k = matrix[2][2], l = matrix[2][3],
             m = matrix[3][0], n = matrix[3][1], o = matrix[3][2], p = matrix[3][3];

    t[0] = k * p - o * l; t[1] = j * p - n * l; t[2] = j * o - n * k;
    t[3] = i * p - m * l; t[4] = i * o - m * k; t[5] = i * n - m * j;

    output[0][0] =  f * t[0] - g * t[1] + h * t[2];
    output[1][0] =-(e * t[0] - g * t[3] + h * t[4]);
    output[2][0] =  e * t[1] - f * t[3] + h * t[5];
    output[3][0] =-(e * t[2] - f * t[4] + g * t[5]);

    output[0][1] =-(b * t[0] - c * t[1] + d * t[2]);
    output[1][1] =  a * t[0] - c * t[3] + d * t[4];
    output[2][1] =-(a * t[1] - b * t[3] + d * t[5]);
    output[3][1] =  a * t[2] - b * t[4] + c * t[5];

    t[0] = g * p - o * h; t[1] = f * p - n * h; t[2] = f * o - n * g;
    t[3] = e * p - m * h; t[4] = e * o - m * g; t[5] = e * n - m * f;

    output[0][2] =  b * t[0] - c * t[1] + d * t[2];
    output[1][2] =-(a * t[0] - c * t[3] + d * t[4]);
    output[2][2] =  a * t[1] - b * t[3] + d * t[5];
    output[3][2] =-(a * t[2] - b * t[4] + c * t[5]);

    t[0] = g * l - k * h; t[1] = f * l - j * h; t[2] = f * k - j * g;
    t[3] = e * l - i * h; t[4] = e * k - i * g; t[5] = e * j - i * f;

    output[0][3] =-(b * t[0] - c * t[1] + d * t[2]);
    output[1][3] =  a * t[0] - c * t[3] + d * t[4];
    output[2][3] =-(a * t[1] - b * t[3] + d * t[5]);
    output[3][3] =  a * t[2] - b * t[4] + c * t[5];

    det = 1.0f / (a * output[0][0] + b * output[1][0] + c * output[2][0] + d * output[3][0]);

    output[0][0] *= det; output[0][1] *= det; output[0][2] *= det; output[0][3] *= det;
    output[1][0] *= det; output[1][1] *= det; output[1][2] *= det; output[1][3] *= det;
    output[2][0] *= det; output[2][1] *= det; output[2][2] *= det; output[2][3] *= det;
    output[3][0] *= det; output[3][1] *= det; output[3][2] *= det; output[3][3] *= det;

    return XD_SUCCESS;
}
