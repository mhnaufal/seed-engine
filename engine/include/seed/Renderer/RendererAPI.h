#pragma once

#include <Eigen/Dense>
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

    virtual auto SetClearColor(const Eigen::Vector4f& color) -> void = 0;
    virtual auto Clear() -> void = 0;

    virtual auto DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) -> void = 0;

    inline static auto GetAPI() -> API { return m_api; }
    inline static auto SetAPI(const API api) -> void { m_api = api; }

private:
    static API m_api;
};
}