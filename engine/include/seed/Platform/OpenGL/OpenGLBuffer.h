#pragma once

#include "imgui_impl_opengl3_loader.h"

#include "Core/Definitions.h"
#include <Renderer/Buffer.h>

namespace seed {
// TODO: change to reflection
inline auto ShaderDataTypeToOpenGLDataType(const ShaderDataType type) -> GLenum
{
    switch (type) {
    case ShaderDataType::FLOAT:
    case ShaderDataType::FLOAT2:
    case ShaderDataType::FLOAT3:
    case ShaderDataType::FLOAT4:
        return GL_FLOAT;
    case ShaderDataType::MATRIX2:
        return GL_FLOAT_MAT2;
    case ShaderDataType::MATRIX3:
        return GL_FLOAT_MAT3;
    case ShaderDataType::MATRIX4:
        return GL_FLOAT_MAT4;
    case ShaderDataType::INT:
    case ShaderDataType::INT2:
    case ShaderDataType::INT3:
    case ShaderDataType::INT4:
        return GL_INT;
    case ShaderDataType::BOOL:
        return GL_BOOL;
    default:
        return GL_ZERO;
    }
}

class OpenGLVertexBuffer final : public VertexBuffer {
public:
    OpenGLVertexBuffer(const float* vertices, uint32_t size);
    ~OpenGLVertexBuffer() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;

    [[nodiscard]] auto GetLayout() const -> BufferLayout override;
    auto SetLayout(const BufferLayout& layout) -> void override;

private:
    uint32_t m_renderer_id{};
    BufferLayout m_layout{};
};

class OpenGLIndexBuffer final : public IndexBuffer {
public:
    OpenGLIndexBuffer(const uint32_t* indices, uint32_t size);
    ~OpenGLIndexBuffer() override;

    auto Bind() const -> void override;
    auto Unbind() const -> void override;
    [[nodiscard]] auto GetCount() const -> uint32_t override;

private:
    uint32_t m_renderer_id{};
    uint32_t m_count{};
};
} // namespace seed