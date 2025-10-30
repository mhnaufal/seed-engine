#include "Buffer.h"
#include "Core/Definitions.h"
#include "OpenGLRendererAPI.h"
#include "VertexArray.h"
#include "imgui_impl_opengl3_loader.h"

namespace seed {
auto OpenGLRendererAPI::SetClearColor(const Eigen::Vector4f& color) -> void
{
    glClearColor(color(0), color(1), color(2), color(3));
}

auto OpenGLRendererAPI::Clear() -> void
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) -> void
{
    glDrawElements(GL_TRIANGLES, vertex_array.get()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
} // namespace seed