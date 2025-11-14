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
    static auto SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) -> void;

private:
    static Ref<RendererAPI> m_renderer_api;
};
}