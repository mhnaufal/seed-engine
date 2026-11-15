#include <Buffer.h>
#include <Core/Definitions.h>
#include <SDL_GPURendererAPI.h>
#include <VertexArray.h>

// #include <glad.h>

namespace seed
{
    auto SDL_GPURendererAPI::Init() -> void
    {
        SEED_PROFILE_FUNCTION();

    }

    auto SDL_GPURendererAPI::SetViewport(
        const uint32_t x,
        const uint32_t y,
        const uint32_t width,
        const uint32_t height) -> void
    {
    }

    auto SDL_GPURendererAPI::SetClearColor(const glm::vec4& color) -> void
    {
    }

    auto SDL_GPURendererAPI::Clear() -> void
    {
    }

    auto SDL_GPURendererAPI::DrawIndexed(const Ref<VertexArray>& vertex_array) -> void
    {
    }

    auto SDL_GPURendererAPI::DrawLines(const Ref<VertexArray>& vertex_array) -> void
    {
    }

    auto SDL_GPURendererAPI::SetLineWidth(const float width) -> void
    {
    }
} // namespace seed
