#pragma once

#include <glm/glm.hpp>

namespace seed {
class Timestep;
class Event;
class WindowResizeEvent;
class MouseScrolledEvent;

class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);
    auto SetProjection(float left, float right, float bottom, float top) -> void;

    [[nodiscard]] auto GetPosition() const -> const glm::vec3& { return m_position; }

    auto SetPosition(const glm::vec3 position) -> void
    {
        m_position = position;
        RecalculateViewMatrix();
    }

    [[nodiscard]] auto GetRotation() const -> float { return m_rotation; }

    auto SetRotation(const float rotation) -> void
    {
        m_rotation = rotation;
        RecalculateViewMatrix();
    }

    [[nodiscard]] auto GetProjectionMatrix() const -> const glm::mat4& { return m_projection_matrix; }
    [[nodiscard]] auto GetViewMatrix() const -> const glm::mat4& { return m_view_matrix; }
    [[nodiscard]] auto GetViewProjectionMatrix() const -> const glm::mat4& { return m_view_projection_matrix; }

private:
    auto RecalculateViewMatrix() -> void;

    glm::mat4 m_projection_matrix{};
    glm::mat4 m_view_matrix{};
    glm::mat4 m_view_projection_matrix{};

    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    float m_rotation{0.0f};
};

class OrthographicCameraController {
public:
    OrthographicCameraController(float aspect_ratio, bool is_rotation);

    auto OnUpdate(Timestep time_step) -> void;
    auto OnEvent(Event& event) -> void;

    auto GetCamera() -> OrthographicCamera&;

private:
    auto OnMouseScrolled(const MouseScrolledEvent& e) -> bool;
    auto OnWindowResized(const WindowResizeEvent& e) -> bool;

private:
    float m_aspect_ratio{};
    bool m_is_rotation = false;
    float m_zoom_level = 1.0f;

    glm::vec3 m_camera_position{0.0f, 0.0f, 0.0f};
    float m_camera_move_speed = 1.0f;
    float m_camera_rotation = 0.0f;
    float m_camera_rotation_speed = 45.0f;

    OrthographicCamera m_camera;
};
}