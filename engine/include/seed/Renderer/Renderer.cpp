#include <Renderer.h>
#include <OpenGLShader.h>
#include <OrthographicCamera.h>
#include <RenderCommand.h>
#include <VertexArray.h>

namespace seed {
Renderer::SceneData* Renderer::m_scene_data = new Renderer::SceneData();

auto Renderer::BeginScene(const OrthographicCamera& camera) -> void
{
    m_scene_data->m_view_projection_matrix = camera.GetViewProjectionMatrix();
}

auto Renderer::EndScene() -> void
{
}

auto Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform) -> void
{
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("uniform_view_projection", m_scene_data->m_view_projection_matrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("uniform_transform", transform);

    vertex_array->Bind();
    RenderCommand::DrawIndexed(vertex_array);
}
}