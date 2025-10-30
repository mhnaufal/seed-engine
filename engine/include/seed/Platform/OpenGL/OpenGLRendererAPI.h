#pragma once
#include "RendererAPI.h"

namespace seed {
class OpenGLRendererAPI final : public RendererAPI {
    auto SetClearColor(const Eigen::Vector4f& color) -> void override;
    auto Clear() -> void override;

    auto DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) -> void override;
};
} // namespace seed