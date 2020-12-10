#include <window.h>
#include <renderer.h>
#include <shader.h>
#include <math.h>

int main() {
    XD_WINDOW window;
    if (XD_FAILED(create_window(1024, 768, "XD window", &window))) {
        return -1;
    }

    XD_RENDERER renderer;
    if (XD_FAILED(create_renderer(&renderer))) {
        return -1;
    }

    XD_TEXTURE texture;
    load_texture("direct_x.tga", &texture, &renderer);

    XD_SHADER shader;
    if (XD_FAILED(create_shader("vertex.glsl", "fragment.glsl", &shader))) {
        return -1;
    }

    XD_FLOAT vertices[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    XD_FLOAT texCoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    XD_UINT32 indicies[] = {
        0, 1, 2,
        0, 2, 3
    };

    set_vertex_attrib(&shader, 0, 2, vertices, sizeof(vertices));
    set_vertex_attrib(&shader, 1, 2, texCoords, sizeof(texCoords));

    set_indicies(&shader, 3, indicies, sizeof(indicies));

    XD_MATRIX4 model, view, projection;
    ortho_matrix(0.0f, 768.0f, 0.0f, 1024.0f, projection);

    identity_matrix(model);
    translate_matrix_2d(200.0f, 200.0f, model);
    rotate_around_center_z(45.0f, model);
    scale_matrix_2d(100.0f, 100.0f, model);

    identity_matrix(view);

    set_uniform(shader, "model", model);
    set_uniform(shader, "view", view);
    set_uniform(shader, "projection", projection);

    while (is_open(window)) {
        if (is_key_pressed(KEY_ESCAPE)) {
            close_window();
        }
        clear(0, 0, 0);

        set_texture(texture);
        execute_shader(shader);

        present(renderer);
    }

    destroy_shader(shader);
    destroy_renderer(renderer);
    destroy_window(window);

    return 0;
}
