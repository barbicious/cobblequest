module;

#include <expected>
#include <glad/glad.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

export module shader;

import types;
import bindable;

export namespace gfx {
    class Shader : public IBindable {
    public:
        Shader(const std::filesystem::path& vsPath, const std::filesystem::path& fsPath) {
            if (const std::expected vertexShader{compileShader(vsPath, GL_VERTEX_SHADER)}; vertexShader.has_value()) {
                glAttachShader(id, vertexShader.value());
                glDeleteShader(vertexShader.value());
            } else {
                std::cerr << vertexShader.error() << std::endl;
            }

            if (const std::expected fragmentShader{compileShader(fsPath, GL_FRAGMENT_SHADER)}; fragmentShader.has_value()) {
                glAttachShader(id, fragmentShader.value());
                glDeleteShader(fragmentShader.value());
            } else {
                std::cerr << fragmentShader.error() << std::endl;
            }

            glLinkProgram(id);

            i32 success;
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                std::array<char, 512> buffer{};
                glGetProgramInfoLog(id, buffer.size(), nullptr, buffer.data());
                std::cerr << buffer.data() << std::endl;
            }
        }

        ~Shader() override {
            glDeleteProgram(id);
        }

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        void bind() override {
            glUseProgram(id);
        }

        void unbind() override {
            glUseProgram(0);
        }

    private:
        u32 id{glCreateProgram()};

        static std::expected<u32, std::string> compileShader(const std::filesystem::path& path, const u32 type) {
            std::ifstream file{path};
            if (!file.is_open()) {
                return std::unexpected{"Failed to open file!"};
            }

            const std::string shaderSrc{
                std::istreambuf_iterator{file},
                std::istreambuf_iterator<char>{}
            };

            const char* shaderSrcC{shaderSrc.c_str()};

            u32 shader{glCreateShader(type)};
            glShaderSource(shader, 1, &shaderSrcC, nullptr);
            glCompileShader(shader);

            i32 success{};
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                std::array<char, 512> buffer{};
                glGetShaderInfoLog(shader, buffer.size(), nullptr, buffer.data());
                return std::unexpected{buffer.data()};
            }

            return shader;
        }
    };
}
