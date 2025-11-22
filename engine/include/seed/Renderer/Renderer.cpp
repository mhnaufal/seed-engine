#include <Renderer.h>
#include <Renderer2D.h>
#include <OpenGLShader.h>
#include <SDL_GPUShader.h>
#include <OrthographicCamera.h>
#include <RenderCommand.h>
#include <VertexArray.h>

namespace seed
{
    Renderer::SceneData* Renderer::m_scene_data = new SceneData();

    auto Renderer::Init() -> void
    {
        SEED_PROFILE_FUNCTION();

        RenderCommand::Init();
        Renderer2D::Init();
    }

    auto Renderer::OnWindowResize(const uint32_t width, const uint32_t height) -> void
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    auto Renderer::BeginScene(const OrthographicCamera& camera) -> void
    {
        m_scene_data->m_view_projection_matrix = camera.GetViewProjectionMatrix();
    }

    auto Renderer::EndScene() -> void
    {
        Renderer2D::Shutdown();
    }

    auto Renderer::Submit(
        const Ref<Shader>& shader,
        const Ref<VertexArray>& vertex_array,
        const glm::mat4& transform) -> void
    {
        shader->Bind();
        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
                "uniform_view_projection",
                m_scene_data->m_view_projection_matrix);

            std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("uniform_transform", transform);
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
        {
            std::dynamic_pointer_cast<SDL_GPUShader>(shader)->UploadUniformMat4(
                "uniform_view_projection",
                m_scene_data->m_view_projection_matrix);

            std::dynamic_pointer_cast<SDL_GPUShader>(shader)->UploadUniformMat4("uniform_transform", transform);
        }


        vertex_array->Bind();
        RenderCommand::DrawIndexed(vertex_array);
    }
}
