#include "imgui_impl_sdl3.h"

#include <WindowsWindow.h>
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
    const auto* data = static_cast<WindowsWindow::WindowData*>(userdata);

    switch (e->type) {
    case SDL_EVENT_WINDOW_RESIZED: {
        const int w = e->window.data1;
        const int h = e->window.data2;
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
        KeyboardPressedEvent event_keydown(static_cast<KeyCode>(e->key.scancode), 0);
        if (data->EventCallback) {
            data->EventCallback(event_keydown);
        }
        break;
    }

    case SDL_EVENT_KEY_UP: {
        KeyboardReleaseEvent event_keyup(static_cast<KeyCode>(e->key.key));
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

    case SDL_EVENT_MOUSE_BUTTON_UP: {
        MouseButtonReleasedEvent event_mouseclick(e->button.button);
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
        int is_success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD);
        if (!is_success) {
            SEED_LOG_ERROR("Failed to Initialize SDL");
            return;
        }
        else {
            is_SDL_Initialized = true;
        }
    }

    m_window = SDL_CreateWindow(
        m_data.Title.c_str(),
        m_data.Width,
        m_data.Height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY);

    if (auto error = SDL_GetError(); strcmp(error, "") != 0) {
        SEED_LOG_ERROR("Failed to create SDL Window: {}", error);
        return;
    }

    const auto gl_ctx = SDL_GL_CreateContext(m_window);
    if (auto error = SDL_GetError(); strcmp(error, "") != 0) {
        SEED_LOG_ERROR("Failed to create SDL Context: {}", error);
        return;
    }
    SDL_GL_MakeCurrent(m_window, gl_ctx);

    SetVSync(true);
    SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(m_window);

    // Event when a window resizing
    SDL_AddEventWatch(SDLEventCallback, &m_data);
}

void WindowsWindow::OnUpdate()
{
    while (SDL_PollEvent(&m_event)) { ImGui_ImplSDL3_ProcessEvent(&m_event); }

    SDL_GL_SwapWindow(m_window);
}

void WindowsWindow::Shutdown()
{
    const auto gl_ctx = SDL_GL_GetCurrentContext();
    SDL_RemoveEventWatch(SDLEventCallback, &m_data);
    SDL_GL_DestroyContext(gl_ctx);
    SDL_DestroyWindow(m_window);
}

void WindowsWindow::SetVSync(const bool enabled)
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