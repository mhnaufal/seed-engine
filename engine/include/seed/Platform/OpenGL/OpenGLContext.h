#pragma once

#include <Renderer/GraphicsContext.h>

struct SDL_Window;

namespace seed {
class OpenGLContext final : public GraphicsContext {
public:
    explicit OpenGLContext(SDL_Window* window_handle);

    auto Init() -> void override;
    auto SwapBuffers() -> void override;

private:
    SDL_Window* m_window_handle{};
};
} // seed