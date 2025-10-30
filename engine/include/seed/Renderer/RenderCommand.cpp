#include "RenderCommand.h"

#include "OpenGLRendererAPI.h"

namespace seed {
RendererAPI* RenderCommand::m_renderer_api = new OpenGLRendererAPI;

auto RenderCommand::SetClearColor(const Eigen::Vector4f& color) -> void
{
    m_renderer_api->SetClearColor(color);
}

auto RenderCommand::Clear() -> void
{
    m_renderer_api->Clear();
}

auto RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) -> void
{
    m_renderer_api->DrawIndexed(vertex_array);
}
}