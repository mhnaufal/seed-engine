#pragma once

#include <glm/glm.hpp>

namespace seed {
class OrthographicCamera;
class Texture2D;

class Renderer2D {
public:
    static auto Init() -> void;
    static auto Shutdown() -> void;

    static auto BeginScene(const OrthographicCamera& camera) -> void;
    static auto EndScene() -> void;

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
};
}