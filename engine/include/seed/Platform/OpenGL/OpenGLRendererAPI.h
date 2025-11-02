#pragma once

#include "RendererAPI.h"

namespace seed {
class OpenGLRendererAPI final : public RendererAPI {
    auto Init() -> void override;
    auto SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) -> void override;
    auto SetClearColor(const glm::vec4& color) -> void override;
    auto Clear() -> void override;

    auto DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) -> void override;
    auto DrawLines(const std::shared_ptr<VertexArray>& vertex_array) -> void override;

    auto SetLineWidth(float width) -> void override;
};
} // namespace seed