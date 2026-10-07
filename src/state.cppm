module;

#include <array>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

export module state;

import window;
import shader;
import vertex_buffer;
import vertex_array;
import types;
import util;
import image_texture;

export class State {
public:
    State() {
        wnd::init();
    }

    ~State() {
        wnd::destroy();
    }

    void run() {
        std::array<f32, 12> vertices{
            -0.5, -0.5, 0.0, 1.0,
            0.5, -0.5, 1.0, 1.0,
            0.5, 0.5, 1.0, 0.0,
        };

        gfx::VertexArray vertexArray{};

        gfx::VertexBuffer vertexBuffer{GL_STATIC_DRAW, vertices};
        vertexBuffer.enableAttrib(0, 2, 4, 0);
        vertexBuffer.enableAttrib(1, 2, 4, 2);
        gfx::Shader shader{"res/shaders/sprite.vert", "res/shaders/sprite.frag"};
        shader.bind();

        gfx::ImageTexture image{"res/textures/player.png"};

        glClearColor(0.75, 0.65, 0.1, 1.0);

        while (window.isGood()) {
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            window.splat();
        }
    }

private:
    wnd::Window window{"cobblequest", 1280, 720};
};
