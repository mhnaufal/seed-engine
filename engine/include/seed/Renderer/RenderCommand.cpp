#include <Definitions.h>
#include <RenderCommand.h>
#include <OpenGLRendererAPI.h>
#include <Logger.h>

namespace seed {
Ref<RendererAPI> RenderCommand::m_renderer_api = std::make_shared<OpenGLRendererAPI>();

auto RenderCommand::Init() -> void
{
    SEED_LOG_VERBOSE("Initializing RenderCommand...");
    m_renderer_api->Init();
}

auto RenderCommand::SetClearColor(const glm::vec4& color) -> void
{
    SEED_LOG_VERBOSE("Setting clear color");
    m_renderer_api->SetClearColor(color);
}

auto RenderCommand::Clear() -> void
{
    SEED_LOG_VERBOSE("Clearing renderer");
    m_renderer_api->Clear();
}

auto RenderCommand::DrawIndexed(const Ref<VertexArray>& vertex_array) -> void
{
    m_renderer_api->DrawIndexed(vertex_array);
}

auto RenderCommand::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) -> void
{
    SEED_LOG_VERBOSE("Resetting viewport");
    m_renderer_api->SetViewport(x, y, width, height);
}
}