#pragma once

#include "RendererAPI.h"
#include <memory>

namespace seed {
class VertexArray;

class RenderCommand {
public:
    static auto SetClearColor(const Eigen::Vector4f& color) -> void;
    static auto Clear() -> void;
    static auto DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) -> void;

private:
    static RendererAPI* m_renderer_api;
};
}