#include "SDL_GPUContext.h"

#include <Logger.h>
#include <SDL3/SDL.h>

namespace seed {
SDL_GPUContext::SDL_GPUContext(SDL_Window* window_handle)
    : m_window_handle(window_handle)
{
}

SDL_GPUContext::~SDL_GPUContext()
{
}

auto SDL_GPUContext::Init() -> void
{
}

auto SDL_GPUContext::SwapBuffers() -> void
{
}
} // namespace seed