#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

Sandbox2D::Sandbox2D()
    : seed::Layer("Sandbox2D")
    , m_camera_controller(1280.0f / 720.0f, true)
{
}

auto Sandbox2D::OnAttach() -> void
{
    seed::Renderer::SetRendererAPI(seed::RendererAPI::API::OPENGL);
    seed::Renderer::Init();

    m_texture2D = seed::Texture2D::Create("assets/back.jpg");

    m_audio = std::make_shared<seed::Audio>(m_sound_path);
    m_audio->Play();
}

auto Sandbox2D::OnDetach() -> void
{
}

auto Sandbox2D::OnUpdate([[maybe_unused]] seed::Timestep& time_step) -> void
{
    m_camera_controller.OnUpdate(time_step);

    glm::vec4 clear_color((249.0f / 255.0f), (155.0f / 255.0f), (254.0f / 255.0f), 1.00f);
    seed::RenderCommand::SetClearColor(clear_color);
    seed::RenderCommand::Clear();

    seed::Renderer2D::BeginScene(m_camera_controller.GetCamera());
    seed::Renderer2D::DrawQuad({-1.3f, 0.9f}, {1.0f, 0.5f}, {0.8f, 0.2f, 0.3f, 1.0f});
    seed::Renderer2D::DrawQuad({1.0f, -0.7f, 0.0f}, {0.7f, 1.0f}, m_selected_color);
    seed::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {2.0f, 2.0f}, m_texture2D);
    seed::Renderer2D::EndScene();
}

auto Sandbox2D::OnEvent([[maybe_unused]] seed::Event& event) -> void
{
    m_camera_controller.OnEvent(event);
}

auto Sandbox2D::OnImGuiRender([[maybe_unused]] const float fps) -> void
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Color Picker", glm::value_ptr(m_selected_color));
    ImGui::End();
}
