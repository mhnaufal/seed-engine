#include "WindowsWindow.h"

#include <Event/ApplicationEvent.h>
#include <Event/KeyboardEvent.h>
#include <Event/MouseEvent.h>
#include <Logger.h>
#include <SDL3/SDL.h>

namespace seed {
static bool is_SDL_Initialized = false;

Window* Window::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    WindowsWindow::Init(props);
}

WindowsWindow::~WindowsWindow()
{
    WindowsWindow::Shutdown();
}

bool SDLCALL SDLEventCallback([[maybe_unused]] void* userdata, SDL_Event* e)
{
    auto* data = static_cast<WindowsWindow::WindowData*>(userdata);

    switch (e->type) {
    case SDL_EVENT_WINDOW_RESIZED: {
        int w = e->window.data1;
        int h = e->window.data2;
        WindowResizeEvent event_resize(w, h);
        if (data->EventCallback) {
            data->EventCallback(event_resize);
        }
        break;
    }

    case SDL_EVENT_QUIT: {
        WindowCloseEvent event_quit{};
        if (data->EventCallback) {
            data->EventCallback(event_quit);
        }
        break;
    }

    case SDL_EVENT_KEY_DOWN: {
        KeyboardPressedEvent event_keydown(e->key.scancode, 0);
        if (data->EventCallback) {
            data->EventCallback(event_keydown);
        }
        break;
    }

    case SDL_EVENT_KEY_UP: {
        KeyboardReleaseEvent event_keyup(e->key.key);
        if (data->EventCallback) {
            data->EventCallback(event_keyup);
        }
        break;
    }

    case SDL_EVENT_MOUSE_MOTION: {
        MouseMovedEvent event_mousemove(e->button.x, e->button.y);
        if (data->EventCallback) {
            data->EventCallback(event_mousemove);
        }
        break;
    }

    case SDL_EVENT_MOUSE_WHEEL: {
        MouseScrolledEvent event_mousewheel(e->button.x, e->button.y);
        if (data->EventCallback) {
            data->EventCallback(event_mousewheel);
        }
        break;
    }

    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        MouseButtonPressedEvent event_mouseclick(e->button.button);
        if (data->EventCallback) {
            data->EventCallback(event_mouseclick);
        }
        break;
    }

    default:
        break;
    }

    return true;
}

void WindowsWindow::Init(const WindowProps& props)
{
    m_data.Title = props.Title;
    m_data.Width = props.Width;
    m_data.Height = props.Height;

    SEED_LOG_INFO("Creating Window: {} {}x{}", m_data.Title, m_data.Width, m_data.Height);

    if (!is_SDL_Initialized) {
        int is_success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        if (!is_success) {
            SEED_LOG_ERROR("Failed to Initialize SDL");
            return;
        }
        else {
            is_SDL_Initialized = true;
        }
    }

    m_window =
        SDL_CreateWindow(m_data.Title.c_str(), m_data.Width, m_data.Height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    auto error = SDL_GetError();
    if (strcmp(error, "") != 0) {
        SEED_LOG_ERROR("Failed to create SDL Window: {}", error);
        return;
    }

    auto gl_ctx = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, gl_ctx);

    SetVSync(true);

    // Event when window resizing
    SDL_AddEventWatch(SDLEventCallback, &m_data);
}

void WindowsWindow::OnUpdate()
{
    while (SDL_PollEvent(&m_event)) {}

    SDL_GL_SwapWindow(m_window);
}

void WindowsWindow::Shutdown()
{
    SDL_RemoveEventWatch(SDLEventCallback, &m_data);
    SDL_DestroyWindow(m_window);
}

void WindowsWindow::SetVSync(bool enabled)
{
    if (enabled) {
        SDL_GL_SetSwapInterval(1);
    }
    else {
        SDL_GL_SetSwapInterval(0);
    }
    m_data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const
{
    return m_data.VSync;
}
} // namespace seed