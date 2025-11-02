#pragma once

#include "RendererAPI.h"

namespace seed {
class OrthographicCamera;
class Shader;

class Renderer {
public:
    static auto BeginScene(const OrthographicCamera& camera) -> void;
    static auto EndScene() -> void;

    static auto Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array) -> void;

    inline static auto GetRendererAPI() -> RendererAPI::API { return RendererAPI::GetAPI(); }
    inline static auto SetRendererAPI(const RendererAPI::API renderer_api) { RendererAPI::SetAPI(renderer_api); }

private:
    struct SceneData {
        glm::mat4 m_view_projection_matrix{};
    };

    static SceneData* m_scene_data;
};
}