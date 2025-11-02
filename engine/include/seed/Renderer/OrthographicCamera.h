#pragma once

#include <glm/glm.hpp>

namespace seed {
class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    auto GetPosition() const -> const glm::vec3& { return m_position; }

    auto SetPosition(const glm::vec3 position) -> void
    {
        m_position = position;
        RecalculateViewMatrix();
    }

    auto GetRotation() const -> float { return m_rotation; }

    auto SetRotation(const float rotation) -> void
    {
        m_rotation = rotation;
        RecalculateViewMatrix();
    }

    auto GetProjectionMatrix() const -> const glm::mat4& { return m_projection_matrix; }
    auto GetViewMatrix() const -> const glm::mat4& { return m_view_matrix; }
    auto GetViewProjectionMatrix() const -> const glm::mat4& { return m_view_projection_matrix; }

private:
    auto RecalculateViewMatrix() -> void;

    glm::mat4 m_projection_matrix{};
    glm::mat4 m_view_matrix{};
    glm::mat4 m_view_projection_matrix{};

    glm::vec3 m_position{0.0f, 0.0f, 0.0f};
    float m_rotation{0.0f};

};
}