#include "OpenGLContext.h"
#include <Logger.h>
#include <SDL3/SDL.h>

namespace seed {
OpenGLContext::OpenGLContext(SDL_Window* window_handle)
    : m_window_handle(window_handle)
{
}

auto OpenGLContext::Init() -> void
{
    const auto gl_ctx = SDL_GL_CreateContext(m_window_handle);
    if (auto error = SDL_GetError(); strcmp(error, "") != 0) {
        SEED_LOG_ERROR("Failed to create SDL Context: {}", error);
        return;
    }
    SDL_GL_MakeCurrent(m_window_handle, gl_ctx);
}

auto OpenGLContext::SwapBuffers() -> void
{
    SDL_GL_SwapWindow(m_window_handle);
}
} // seed