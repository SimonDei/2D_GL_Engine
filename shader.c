//
// Created by a00007 on 09.12.2020.
//

#include "shader.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include <GL/glew.h>

XD_RESULT create_shader(XD_STRING vertex_shader_path,
                        XD_STRING fragment_shader_path,
                        PTR(XD_SHADER) p_shader) {
    CLEAR_MEMORY(p_shader);
    p_shader->_program_id = glCreateProgram();
    p_shader->_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    p_shader->_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    glGenVertexArrays(1, &p_shader->_vertex_array_id);

    FILE* file = NULL;
    XD_LONG byte_length;

    file = fopen(vertex_shader_path, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        byte_length = ftell(file);
        fseek(file, 0, SEEK_SET);

        XD_CHAR buffer[2048];
        memset(buffer, 0, 2048 * sizeof(XD_CHAR));
        fread(buffer, sizeof(XD_CHAR), byte_length, file);

        fclose(file);
        file = NULL;

        XD_LPCHAR vertex_source = buffer;

        glShaderSource(p_shader->_vertex_shader_id, 1, (XD_STRING*) &vertex_source, NULL);
        glCompileShader(p_shader->_vertex_shader_id);

        XD_INT32 max_length;
        glGetShaderiv(p_shader->_vertex_shader_id, GL_INFO_LOG_LENGTH, &max_length);
        if (max_length > 1) {
            XD_LPCHAR shader_log = (XD_LPCHAR) malloc(max_length * sizeof(XD_CHAR));
            glGetShaderInfoLog(p_shader->_vertex_shader_id, max_length, &max_length, shader_log);

            fprintf(stderr, "%s\n", shader_log);

            free(shader_log);
            shader_log = NULL;

            glDeleteShader(p_shader->_vertex_shader_id);
            return XD_FAILED;
        }

        glAttachShader(p_shader->_program_id, p_shader->_vertex_shader_id);
    }

    byte_length = 0;

    file = fopen(fragment_shader_path, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        byte_length = ftell(file);
        fseek(file, 0, SEEK_SET);

        XD_CHAR buffer[2048];
        memset(buffer, 0, 2048 * sizeof(XD_CHAR));
        fread(buffer, sizeof(XD_CHAR), byte_length, file);

        fclose(file);
        file = NULL;

        XD_LPCHAR fragment_source = buffer;

        glShaderSource(p_shader->_fragment_shader_id, 1, (XD_STRING*) &fragment_source, NULL);
        glCompileShader(p_shader->_fragment_shader_id);

        XD_INT32 max_length;
        glGetShaderiv(p_shader->_fragment_shader_id, GL_INFO_LOG_LENGTH, &max_length);
        if (max_length > 1) {
            XD_LPCHAR shader_log = (XD_LPCHAR) malloc(max_length * sizeof(XD_CHAR));
            glGetShaderInfoLog(p_shader->_fragment_shader_id, max_length, &max_length, shader_log);

            fprintf(stderr, "%s\n", shader_log);

            free(shader_log);
            shader_log = NULL;

            glDeleteShader(p_shader->_fragment_shader_id);
            return XD_FAILED;
        }

        glAttachShader(p_shader->_program_id, p_shader->_fragment_shader_id);
    }

    glLinkProgram(p_shader->_program_id);

    return XD_SUCCESS;
}

XD_RESULT set_vertex_attrib(PTR(XD_SHADER) p_shader,
                            XD_UINT8 position,
                            XD_UINT8 vertex_size,
                            PTR(XD_FLOAT) p_data,
                            XD_UINT32 data_size) {
    XD_UINT32 buffer_id;
    glGenBuffers(1, &buffer_id);

    glBindVertexArray(p_shader->_vertex_array_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

    glBufferData(GL_ARRAY_BUFFER, data_size, p_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, vertex_size, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    p_shader->_buffers[p_shader->_buffer_index++] = buffer_id;

    return XD_SUCCESS;
}

XD_RESULT set_indicies(PTR(XD_SHADER) p_shader,
                       XD_UINT8 vertex_size,
                       PTR(XD_UINT32) p_data,
                       XD_UINT32 data_size) {
    XD_UINT32 buffer_id;
    glGenBuffers(1, &buffer_id);

    glBindVertexArray(p_shader->_vertex_array_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, p_data, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    p_shader->_indicies_count = data_size / sizeof(XD_UINT32);
    p_shader->_buffers[p_shader->_buffer_index++] = buffer_id;

    return XD_SUCCESS;
}

XD_RESULT set_uniform(XD_SHADER shader,
                      XD_STRING name,
                      XD_MATRIX4 matrix) {
    glUseProgram(shader._program_id);

    XD_UINT32 location = glGetUniformLocation(shader._program_id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, (XD_LPFLOAT) matrix);

    glUseProgram(0);

    return XD_SUCCESS;
}

XD_RESULT execute_shader(XD_SHADER shader) {
    glUseProgram(shader._program_id);
    glBindVertexArray(shader._vertex_array_id);
    glDrawElements(GL_TRIANGLES, shader._indicies_count, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    glUseProgram(0);

    return XD_SUCCESS;
}

XD_RESULT destroy_shader(XD_SHADER shader) {
    for (XD_UINT16 i = 0; i < shader._buffer_index; i++) {
        glDeleteBuffers(1, &shader._buffers[i]);
    }

    glDeleteVertexArrays(1, &shader._vertex_array_id);

    glDetachShader(shader._program_id, shader._vertex_shader_id);
    glDetachShader(shader._program_id, shader._fragment_shader_id);

    glDeleteShader(shader._vertex_shader_id);
    glDeleteShader(shader._fragment_shader_id);

    glDeleteProgram(shader._program_id);

    return XD_SUCCESS;
}
