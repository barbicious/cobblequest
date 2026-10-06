#include <array>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

import types;
import shader;
import vertex_array;
import buffer;
import vertex_buffer;

i32 main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window{glfwCreateWindow(1280, 720, "cobblequest", nullptr, nullptr)};
    if (window == nullptr) {
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        return EXIT_FAILURE;
    }

    std::array<f32, 6> vertices{
        -0.5, -0.5,
        0.5, -0.5,
        0.0, 0.5
    };

    gfx::VertexArray vertexArray{};

    gfx::VertexBuffer vertexBuffer{GL_STATIC_DRAW, vertices};
    vertexBuffer.enableAttrib(0, 2, 2, 0);
    gfx::Shader shader{"res/shaders/sprite.vert", "res/shaders/sprite.frag"};
    shader.bind();

    glClearColor(0.75, 0.65, 0.1, 1.0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
