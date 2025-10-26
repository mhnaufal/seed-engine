#include "OpenGLContext.h"

#include <Logger.h>
#include <SDL3/SDL.h>

namespace seed {
OpenGLContext::OpenGLContext(SDL_Window* window_handle)
    : m_window_handle(window_handle)
{
}

OpenGLContext::~OpenGLContext()
{
    SEED_LOG_INFO("Destroying OpenGL context...");
    SDL_GL_DestroyContext(m_context_handle);
}

auto OpenGLContext::Init() -> void
{
    SEED_LOG_INFO("Initializing OpenGL context...");
    m_context_handle = SDL_GL_CreateContext(m_window_handle);
    if (auto error = SDL_GetError(); strcmp(error, "") != 0) {
        SEED_LOG_ERROR("Failed to create SDL Context: {}", error);
        return;
    }
    SDL_GL_MakeCurrent(m_window_handle, m_context_handle);
}

auto OpenGLContext::SwapBuffers() -> void
{
    SDL_GL_SwapWindow(m_window_handle);
}
} // namespace seed