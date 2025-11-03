#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include "Buffer.h"
#include "Core/Definitions.h"
#include "OpenGLRendererAPI.h"
#include "VertexArray.h"

#include "glad.h"
#include "imgui_impl_opengl3_loader.h"

namespace seed {
auto OpenGLRendererAPI::Init() -> void
{
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

auto OpenGLRendererAPI::SetViewport(
    const uint32_t x,
    const uint32_t y,
    const uint32_t width,
    const uint32_t height) -> void
{
    glViewport(x, y, width, height);
}

auto OpenGLRendererAPI::SetClearColor(const glm::vec4& color) -> void
{
    glClearColor(color.r, color.g, color.b, color.a);
}

auto OpenGLRendererAPI::Clear() -> void
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) -> void
{
    glDrawElements(GL_TRIANGLES, vertex_array.get()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

auto OpenGLRendererAPI::DrawLines(const std::shared_ptr<VertexArray>& vertex_array) -> void
{
    vertex_array->Bind();
    glDrawArrays(GL_LINES, 0, vertex_array->GetIndexBuffer()->GetCount());
}

auto OpenGLRendererAPI::SetLineWidth(const float width) -> void
{
    glLineWidth(width);
}
} // namespace seed