#pragma once

#include <seed/seed.h>

class Sandbox2D : public seed::Layer {
public:
    Sandbox2D();
    ~Sandbox2D() = default;

    auto OnAttach() -> void override;
    auto OnDetach() -> void override;

    auto OnUpdate([[maybe_unused]] seed::Timestep& time_step) -> void override;
    auto OnEvent([[maybe_unused]] seed::Event& event) -> void override;
    auto OnImGuiRender([[maybe_unused]] const float fps) -> void override;

private:
    seed::OrthographicCameraController m_camera_controller;
    // seed::Ref<seed::VertexArray> m_square_vertex_array = nullptr;
    // seed::Ref<seed::Shader> m_square_shader = nullptr;
    glm::vec4 m_selected_color = { 0.2f, 0.3f, 0.8f, 1.0f };

    seed::Ref<seed::Texture2D> m_texture2D = nullptr;

    seed::Ref<seed::Audio> m_audio = nullptr;
    std::string m_sound_path = "assets/selow.mp3";
};
