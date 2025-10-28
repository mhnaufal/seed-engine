#pragma once

#include <memory>
#include <vector>

namespace seed {
class VertexBuffer;
class IndexBuffer;

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual auto Bind() const -> void = 0;
    virtual auto Unbind() const -> void = 0;

    virtual auto AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffers) -> void = 0;
    virtual auto SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffers) -> void = 0;

    [[nodiscard]] virtual auto GetVertexBuffer() const -> std::vector<std::shared_ptr<VertexBuffer>> = 0;
    [[nodiscard]] virtual auto GetIndexBuffer() const -> std::shared_ptr<IndexBuffer> = 0;

    static auto Create() -> VertexArray*;
};
}