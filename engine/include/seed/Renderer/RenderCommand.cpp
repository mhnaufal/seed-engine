#include <Definitions.h>
#include <RenderCommand.h>
#include <OpenGLRendererAPI.h>

namespace seed {
Ref<RendererAPI> RenderCommand::m_renderer_api = std::make_shared<OpenGLRendererAPI>();

auto RenderCommand::Init() -> void
{
    m_renderer_api->Init();
}


auto RenderCommand::SetClearColor(const glm::vec4& color) -> void
{
    m_renderer_api->SetClearColor(color);
}

auto RenderCommand::Clear() -> void
{
    m_renderer_api->Clear();
}

auto RenderCommand::DrawIndexed(const Ref<VertexArray>& vertex_array) -> void
{
    m_renderer_api->DrawIndexed(vertex_array);
}
}