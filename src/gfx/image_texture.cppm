module;

#include <glad/glad.h>
#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

export module image_texture;

import raw_texture;
import types;

export namespace gfx {
    class ImageTexture : public RawTexture {
    public:
        explicit ImageTexture(const std::string_view path) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            data = stbi_load(path.data(), &width, &height, nullptr, 0);
            if (data){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cerr << "Failed to load texture" << std::endl;
            }
        }

    private:
        u8* data{};

    };
}
