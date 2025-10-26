#pragma once

#include <Renderer/GraphicsContext.h>
#include <SDL3/SDL_video.h>

namespace seed {
class SDL_GPUContext final : public GraphicsContext {
public:
    explicit SDL_GPUContext(SDL_Window* window_handle);
    ~SDL_GPUContext() override;

    auto Init() -> void override;
    auto SwapBuffers() -> void override;

private:
    SDL_Window* m_window_handle{};
    SDL_GLContext m_context_handle{};
};
} // namespace seed