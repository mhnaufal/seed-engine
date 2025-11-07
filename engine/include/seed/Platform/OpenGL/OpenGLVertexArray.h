#pragma once

#include "../Core/Definitions.h"
#include <Renderer/VertexArray.h>

#include <vector>

namespace seed {
class OpenGLVertexArray final : public VertexArray {
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;

    auto AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffers) -> void override;
    auto SetIndexBuffer(const Ref<IndexBuffer>& index_buffers) -> void override;

    [[nodiscard]] auto GetVertexBuffer() const -> std::vector<Ref<VertexBuffer>> override
    {
        return m_vertex_buffers;
    };
    [[nodiscard]] auto GetIndexBuffer() const -> Ref<IndexBuffer> override { return m_index_buffers; };

private:
    uint32_t m_renderer_id{};
    std::vector<Ref<VertexBuffer>> m_vertex_buffers{};
    Ref<IndexBuffer> m_index_buffers{};
};
} // namespace seed