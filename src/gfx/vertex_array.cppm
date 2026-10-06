module;

#include "glad/glad.h"

export module vertex_array;

import types;
import bindable;

export namespace gfx {
    class VertexArray : public IBindable {
    public:
        VertexArray() {
            glGenVertexArrays(1, &id);
            glBindVertexArray(id);
        }

        void bind() override {
            glBindVertexArray(id);
        }

        void unbind() override {
            glBindVertexArray(0);
        }

    private:
        u32 id{};
    };
}
