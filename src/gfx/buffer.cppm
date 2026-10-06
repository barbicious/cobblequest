module;

#include <array>

#include "glad/glad.h"

export module buffer;

import types;

export namespace gfx {
    class Buffer {
    public:
        template <typename T, usize N>
        Buffer(const u32 type, const u32 usage, std::array<T, N> data) : type{type}, usage{usage} {
            glGenBuffers(1, &id);
            glBindBuffer(type, id);
            glBufferData(type, N * sizeof(T), data.data(), usage);
        }

        virtual ~Buffer() = default;

        virtual void enableAttrib(u32 index, i32 size, i32 stride, u32 offset) = 0;

    private:
        u32 id{}, type, usage;

    };
}
