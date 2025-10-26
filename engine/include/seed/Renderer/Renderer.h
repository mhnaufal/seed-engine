#pragma once

namespace seed {
enum class RendererAPI {
    NONE = 0,
    OPENGL = 1,
    SDL_GPU = 2,
    NVRHI = 3,
};

class Renderer {
public:
    inline static auto GetRendererAPI() -> RendererAPI { return m_renderer_api; }
    inline static auto SetRendererAPI(const RendererAPI renderer_api) { m_renderer_api = renderer_api; }

private:
    static RendererAPI m_renderer_api;
};
}