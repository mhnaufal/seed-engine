#include <Core/Definitions.h>

#include "OpenGLBuffer.h"

#include "imgui_impl_opengl3_loader.h"

namespace seed {
// ===================================
// Vertex Buffer ====================
// ===================================

OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, const uint32_t size)
{
    glGenBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_renderer_id);
}

auto OpenGLVertexBuffer::Bind() const -> void
{
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}

auto OpenGLVertexBuffer::Unbind() const -> void
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ===================================
// Index Buffer ======================
// ===================================

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, const uint32_t size)
    : m_count(size)
{
    glGenBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_renderer_id);
}

auto OpenGLIndexBuffer::Bind() const -> void
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

auto OpenGLIndexBuffer::Unbind() const -> void
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto OpenGLIndexBuffer::GetCount() const -> uint32_t
{
    return m_count;
}
} // namespace seed