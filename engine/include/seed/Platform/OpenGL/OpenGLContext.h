#pragma once

#include <Renderer/GraphicsContext.h>
#include <SDL3/SDL_video.h>

struct SDL_Window;
// struct SDL_GLContext;

namespace seed {
class OpenGLContext final : public GraphicsContext {
public:
    explicit OpenGLContext(SDL_Window* window_handle);
    ~OpenGLContext() override;

    auto Init() -> void override;
    auto SwapBuffers() -> void override;

private:
    SDL_Window* m_window_handle{};
    SDL_GLContext m_context_handle{};
};
} // seed