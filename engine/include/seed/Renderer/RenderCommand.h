#pragma once

#include "../Core/Definitions.h"
#include "RendererAPI.h"

namespace seed {
class VertexArray;

class RenderCommand {
public:
    static auto Init() -> void;
    static auto SetClearColor(const glm::vec4& color) -> void;
    static auto Clear() -> void;
    static auto DrawIndexed(const Ref<VertexArray>& vertex_array) -> void;

private:
    static Ref<RendererAPI> m_renderer_api;
};
}