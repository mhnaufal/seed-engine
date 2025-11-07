#pragma once

#include "../Core/Definitions.h"

#include <vector>

namespace seed {
class VertexBuffer;
class IndexBuffer;

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;

    virtual auto AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffers) -> void = 0;
    virtual auto SetIndexBuffer(const Ref<IndexBuffer>& index_buffers) -> void = 0;

    [[nodiscard]] virtual auto GetVertexBuffer() const -> std::vector<Ref<VertexBuffer>> = 0;
    [[nodiscard]] virtual auto GetIndexBuffer() const -> Ref<IndexBuffer> = 0;

    static auto Create() -> VertexArray*;
};
}