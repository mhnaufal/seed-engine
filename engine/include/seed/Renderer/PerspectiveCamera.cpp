#include <PerspectiveCamera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace seed {
PerspectiveCamera::PerspectiveCamera()
    : m_projection_matrix(glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f)), m_view_matrix(1.0f)
{
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

auto PerspectiveCamera::RecalculateViewMatrix() -> void
{
    const glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
                                glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));

    m_view_matrix = glm::inverse(transform);
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}
}