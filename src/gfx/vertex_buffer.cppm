module;

#include <array>

#include "glad/glad.h"

export module vertex_buffer;

import buffer;
import types;

export namespace gfx {
    class VertexBuffer : public Buffer {
    public:
        template <usize N>
        VertexBuffer(const u32 usage, std::array<f32, N> data) : Buffer{GL_ARRAY_BUFFER, usage, data} {
        }

        void enableAttrib(u32 index, i32 size, i32 stride, u32 offset) override {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size , GL_FLOAT, false, stride * static_cast<i32>(sizeof(f32)), reinterpret_cast<void*>(offset * sizeof(f32)));
        }
    };
}
