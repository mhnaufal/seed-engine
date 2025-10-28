#pragma once

#include <vector>
#include <Core/Definitions.h>
#include <Renderer/VertexArray.h>

namespace seed {
class OpenGLVertexArray final : public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;

    auto AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffers) -> void override;
    auto SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffers) -> void override;

    [[nodiscard]] auto GetVertexBuffer() const -> std::vector<std::shared_ptr<VertexBuffer>> override
    {
        return m_vertex_buffers;
    };
    [[nodiscard]] auto GetIndexBuffer() const -> std::shared_ptr<IndexBuffer> override { return m_index_buffers; };

private:
    uint32_t m_renderer_id{};
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers{};
    std::shared_ptr<IndexBuffer> m_index_buffers{};
};
} // namespace seed