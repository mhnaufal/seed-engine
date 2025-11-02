#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include <glm/glm.hpp>
#include <memory>

namespace seed {
class VertexArray;

class RendererAPI {
public:
    virtual ~RendererAPI() = default;

    enum class API {
        NONE = 0,
        OPENGL = 1,
        SDL_GPU = 2,
        NVRHI = 3,
    };

    virtual auto Init() -> void = 0;
    virtual auto SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) -> void = 0;
    virtual auto SetClearColor(const glm::vec4& color) -> void = 0;
    virtual auto Clear() -> void = 0;

    virtual auto DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) -> void = 0;
    virtual auto DrawLines(const std::shared_ptr<VertexArray>& vertex_array) -> void = 0;

    virtual auto SetLineWidth(float width) -> void = 0;

    inline static auto GetAPI() -> API { return m_api; }
    inline static auto SetAPI(const API api) -> void { m_api = api; }

private:
    static API m_api;
};
}