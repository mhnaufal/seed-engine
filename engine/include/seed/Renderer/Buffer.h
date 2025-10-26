#pragma once

#include <cstdint>

namespace seed {
class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;

    static auto Create(const float* vertices, uint32_t size) -> VertexBuffer*;
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;
    virtual auto GetCount() const -> uint32_t = 0;

    static auto Create(const uint32_t* indices, const uint32_t size) -> IndexBuffer*;
};
}