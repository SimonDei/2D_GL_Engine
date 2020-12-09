#include <window.h>
#include <renderer.h>
#include <shader.h>

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
    create_shader("vertex.glsl", "fragment.glsl", &shader);

    while (is_open(window)) {
        if (is_key_pressed(KEY_ESCAPE)) {
            close_window();
        }
        clear(0, 0, 0);

        set_texture(texture);
        draw_rect(50, 50, 100, 100);

        present(renderer);
    }

    destroy_renderer(renderer);
    destroy_window(window);

    return 0;
}
