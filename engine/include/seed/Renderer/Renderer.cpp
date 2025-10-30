#include "Renderer.h"
#include "RenderCommand.h"
#include "VertexArray.h"

namespace seed {
auto Renderer::BeginScene() -> void
{
}

auto Renderer::EndScene() -> void
{
}

auto Renderer::Submit(const std::shared_ptr<VertexArray>& vertex_array) -> void
{
    vertex_array->Bind();
    RenderCommand::DrawIndexed(vertex_array);
}
}