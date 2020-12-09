//
// Created by a00007 on 09.12.2020.
//

#include "shader.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

#include <GL/glew.h>

XD_RESULT create_shader(XD_STRING vertex_shader_path,
                        XD_STRING fragment_shader_path,
                        PTR(XD_SHADER) p_shader) {
    CLEAR_MEMORY(p_shader);
    p_shader->_program_id = glCreateProgram();
    p_shader->_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    p_shader->_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    FILE* file = NULL;
    long byte_length;

    file = fopen(vertex_shader_path, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        byte_length = ftell(file);
        fseek(file, 0, SEEK_SET);

        char buffer[2048];
        fread(buffer, sizeof(char), byte_length, file);

        fclose(file);
        file = NULL;

        char* vertex_source = buffer;

        glShaderSource(p_shader->_vertex_shader_id, 1, (const char**) &vertex_source, NULL);
        glCompileShader(p_shader->_vertex_shader_id);
        glAttachShader(p_shader->_program_id, p_shader->_vertex_shader_id);
    }

    byte_length = 0;

    file = fopen(fragment_shader_path, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        byte_length = ftell(file);
        fseek(file, 0, SEEK_SET);

        char buffer[2048];
        fread(buffer, sizeof(char), byte_length, file);

        fclose(file);
        file = NULL;

        char* fragment_source = buffer;

        glShaderSource(p_shader->_fragment_shader_id, 1, (const char**) &fragment_source, NULL);
        glCompileShader(p_shader->_fragment_shader_id);
        glAttachShader(p_shader->_program_id, p_shader->_fragment_shader_id);
    }

    glLinkProgram(p_shader->_program_id);

    return XD_SUCCESS;
}
