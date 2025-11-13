#include "OrthographicCamera.h"
#include "Input.h"
#include "Logger.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"
#include "Timestep.h"

#include <glm/gtc/matrix_transform.hpp>

namespace seed {
OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top)
    : m_projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_view_matrix(1.0f)
{
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

auto OrthographicCamera::SetProjection(const float left, const float right, const float bottom, const float top) -> void
{
    m_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

auto OrthographicCamera::RecalculateViewMatrix() -> void
{
    const glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
                                glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

    m_view_matrix = glm::inverse(transform);
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

//* OrthographicCameraController *//
OrthographicCameraController::OrthographicCameraController(const float aspect_ratio, const bool is_rotation)
    : m_aspect_ratio(aspect_ratio), m_is_rotation(is_rotation),
      m_camera(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level)
{
}

auto OrthographicCameraController::OnUpdate(const Timestep time_step) -> void
{
    if (Input::IsKeyPressed(SDL_SCANCODE_A)) {
        m_camera_position.x = m_camera_position.x - (m_camera_move_speed * time_step);
    }
    else if (Input::IsKeyPressed(SDL_SCANCODE_D)) {
        m_camera_position.x = m_camera_position.x + (m_camera_move_speed * time_step);
    }

    if (Input::IsKeyPressed(SDL_SCANCODE_W)) {
        m_camera_position.y = m_camera_position.y + (m_camera_move_speed * time_step);
    }
    else if (Input::IsKeyPressed(SDL_SCANCODE_S)) {
        m_camera_position.y = m_camera_position.y - (m_camera_move_speed * time_step);
    }

    if (m_is_rotation == true) {
        if (Input::IsKeyPressed(SDL_SCANCODE_Q)) {
            m_camera_rotation = m_camera_rotation - (m_camera_rotation_speed * time_step);
        }
        else if (Input::IsKeyPressed(SDL_SCANCODE_E)) {
            m_camera_rotation = m_camera_rotation + (m_camera_rotation_speed * time_step);
        }

        m_camera.SetRotation(m_camera_rotation);
    }

    m_camera.SetPosition(m_camera_position);
    m_camera_move_speed = m_zoom_level;
}

auto OrthographicCameraController::OnEvent(Event& event) -> void
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseScrolledEvent>(
        [this](auto&& PHI) { return OrthographicCameraController::OnMouseScrolled(PHI); });
    dispatcher.Dispatch<WindowResizeEvent>(
        [this](auto&& PHI) { return OrthographicCameraController::OnWindowResized(PHI); });
}

auto OrthographicCameraController::GetCamera() -> OrthographicCamera&
{
    return m_camera;
}

auto OrthographicCameraController::OnMouseScrolled(const MouseScrolledEvent& e) -> bool
{
    m_zoom_level = m_zoom_level - e.GetYOffset() * 0.15f;
    m_zoom_level = std::max(m_zoom_level, 0.15f);
    m_camera.SetProjection(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level);

    return false;
}

auto OrthographicCameraController::OnWindowResized(const WindowResizeEvent& e) -> bool
{
    m_aspect_ratio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
    m_camera.SetProjection(-m_aspect_ratio * m_zoom_level, m_aspect_ratio * m_zoom_level, -m_zoom_level, m_zoom_level);

    return false;
}
}