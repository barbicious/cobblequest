module;

#include <iostream>
#include <string_view>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

export module window;

import types;

export namespace wnd {
    class Window {
    public:
        Window(const std::string_view title, const i32 width, const i32 height) {
            glfwInit();

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

            rawWindow = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
            if (rawWindow == nullptr) {
                std::cerr << "Failed to create window" << std::endl;
            }

            glfwMakeContextCurrent(rawWindow);

            if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
                std::cerr << "Failed to load glad functions" << std::endl;
            }
        }

        ~Window() {
            glfwDestroyWindow(rawWindow);
            glfwTerminate();
        }

        [[nodiscard]] bool isGood() const {
            glfwPollEvents();

            return !glfwWindowShouldClose(rawWindow);
        }

        void splat() const {
            glfwSwapBuffers(rawWindow);
        }

    private:
        GLFWwindow* rawWindow{};
    };
}