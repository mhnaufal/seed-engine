#include "OpenGLVertexArray.h"

#include "OpenGLBuffer.h"
#include "imgui_impl_opengl3_loader.h"

namespace seed {
OpenGLVertexArray::OpenGLVertexArray()
{
    // [#] Initialize a vertex array: state containing entity, "reference" to the Vertex Buffer Data
    glGenVertexArrays(1, &m_renderer_id);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_renderer_id);
}

auto OpenGLVertexArray::Bind() const -> void
{
    // [#] Bind the vertex array
    glBindVertexArray(m_renderer_id);
}

auto OpenGLVertexArray::Unbind() const -> void
{
    glBindVertexArray(0);
}

auto OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffers) -> void
{
    glBindVertexArray(m_renderer_id);

    uint32_t index = 0;
    const auto& i_layout = vertex_buffers->GetLayout();
    for (const auto& element : i_layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            static_cast<int>(element.GetComponentCount()),
            ShaderDataTypeToOpenGLDataType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            static_cast<int>(i_layout.GetStride()),
            reinterpret_cast<const void*>(static_cast<uintptr_t>(element.offset)));
        index++;
    }
    m_vertex_buffers.push_back(vertex_buffers);
}

auto OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffers) -> void
{
    glBindVertexArray(m_renderer_id);
    index_buffers->Bind();
    m_index_buffers = index_buffers;
}
} // namespace seed