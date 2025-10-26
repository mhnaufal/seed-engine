#pragma once

#include <Renderer/Buffer.h>

namespace seed {
class OpenGLVertexBuffer final : public VertexBuffer {
public:
    OpenGLVertexBuffer(const float* vertices, uint32_t size);
    ~OpenGLVertexBuffer() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;

private:
    uint32_t m_renderer_id{};
};

class OpenGLIndexBuffer final : public IndexBuffer {
public:
    OpenGLIndexBuffer(const uint32_t* indices, const uint32_t size);
    ~OpenGLIndexBuffer() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;
    auto GetCount() const -> uint32_t override;

private:
    uint32_t m_renderer_id{};
    uint32_t m_count{};
};
} // namespace seed