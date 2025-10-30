#pragma once

#include "RendererAPI.h"

namespace seed {
class Renderer {
public:
    static auto BeginScene() -> void;
    static auto EndScene() -> void;

    static auto Submit(const std::shared_ptr<VertexArray>& vertex_array) -> void;

    inline static auto GetRendererAPI() -> RendererAPI::API { return RendererAPI::GetAPI(); }
    inline static auto SetRendererAPI(const RendererAPI::API renderer_api) { RendererAPI::SetAPI(renderer_api); }
};
}