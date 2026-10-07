module;

#include "glad/glad.h"

export module raw_texture;

import types;
import bindable;

export namespace gfx {
    class RawTexture : public IBindable {
    public:
        RawTexture() {
            glGenTextures(1, &id);
            RawTexture::bind();
        }

        ~RawTexture() override {
            glDeleteTextures(1, &id);
        }

        void bind() override {
            glBindTexture(GL_TEXTURE_2D, id);
        }

        void unbind() override {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        [[nodiscard]] i32 getWidth() const noexcept {
            return width;
        }

        [[nodiscard]] i32 getHeight() const noexcept {
            return height;
        }

    protected:
        i32 width{}, height{};

    private:
        u32 id{};

    };
}