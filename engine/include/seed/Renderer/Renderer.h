#pragma once

#include "RendererAPI.h"
#include "../Core/Definitions.h"

namespace seed {
class OrthographicCamera;
class Shader;

class Renderer {
public:
    static auto BeginScene(const OrthographicCamera& camera) -> void;
    static auto EndScene() -> void;

    static auto Submit(
        const Ref<Shader>& shader,
        const Ref<VertexArray>& vertex_array,
        const glm::mat4& transform = glm::mat4(1.0f)) -> void;

    inline static auto GetRendererAPI() -> RendererAPI::API { return RendererAPI::GetAPI(); }
    inline static auto SetRendererAPI(const RendererAPI::API renderer_api) { RendererAPI::SetAPI(renderer_api); }

private:
    struct SceneData {
        glm::mat4 m_view_projection_matrix{};
    };

    static SceneData* m_scene_data;
};
}