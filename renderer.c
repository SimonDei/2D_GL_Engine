//
// Created by a00007 on 09.12.2020.
//

#include "renderer.h"

#include "tga_loader.h"

#include <GL/glew.h>

XD_RESULT create_renderer(PTR(XD_RENDERER) p_renderer) {
    CLEAR_MEMORY(p_renderer);
    p_renderer->_hDc = wglGetCurrentDC();
    if (p_renderer->_hDc == NULL) {
        return XD_FAILED;
    }

    p_renderer->_hGlrc = wglGetCurrentContext();
    if (p_renderer->_hGlrc == NULL) {
        return XD_FAILED;
    }

    glewExperimental = TRUE;
    if (glewInit() != GLEW_OK) {
        return XD_FAILED;
    }

    RECT rect;
    GetClientRect(GetActiveWindow(), &rect);

    glViewport(0, 0, rect.right, rect.bottom);

    //glEnable(GL_DEPTH_TEST);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, rect.right, rect.bottom, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    */

    return XD_SUCCESS;
}

XD_RESULT clear(XD_UINT8 red,
                XD_UINT8 green,
                XD_UINT8 blue) {
    glClearColor((XD_FLOAT) red / 255.0f, (XD_FLOAT) green / 255.0f, (XD_FLOAT) blue / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return XD_SUCCESS;
}

XD_RESULT present(XD_RENDERER renderer) {
    SwapBuffers(renderer._hDc);

    return XD_SUCCESS;
}

XD_RESULT draw_rect(XD_FLOAT x,
                    XD_FLOAT y,
                    XD_FLOAT width,
                    XD_FLOAT height) {
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        glVertex2f(x, y);
        glTexCoord2f(0, 0);
        glVertex2f(x, y + height);
        glTexCoord2f(1, 0);
        glVertex2f(x + width, y + height);
        glTexCoord2f(1, 1);
        glVertex2f(x + width, y);
    glEnd();

    return XD_SUCCESS;
}

XD_RESULT load_texture(XD_STRING file_path,
                       PTR(XD_TEXTURE) p_texture,
                       PTR(XD_RENDERER) p_renderer) {
    XD_TGAFILE file;
    load_tga_file(file_path, &file);

    glEnable(GL_TEXTURE_2D);

    glGenTextures(1, p_texture);
    glBindTexture(GL_TEXTURE_2D, *p_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, file._image_width, file._image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, file._image_data);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    p_renderer->_textures[p_renderer->_texture_index++] = *p_texture;

    return XD_SUCCESS;
}

XD_RESULT set_texture(XD_TEXTURE texture) {
    glBindTexture(GL_TEXTURE_2D, texture);

    return XD_SUCCESS;
}

XD_RESULT destroy_renderer(XD_RENDERER renderer) {
    for (UINT16 i = 0; i < renderer._texture_index; i++) {
        glDeleteTextures(1, &renderer._textures[i]);
    }

    return XD_SUCCESS;
}
