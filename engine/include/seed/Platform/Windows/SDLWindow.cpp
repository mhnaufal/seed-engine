#include <Application.h>
#include <RendererAPI.h>
#include <SDL_GPUContext.h>
#include <SDLWindow.h>
#include <Event/ApplicationEvent.h>
#include <Event/KeyboardEvent.h>
#include <Event/MouseEvent.h>
#include <Logger.h>

#include <imgui_impl_sdl3.h>
#include <SDL3/SDL.h>

namespace seed
{
    static bool is_sdl_initialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new SDLWindow(props);
    }

    SDLWindow::SDLWindow(const WindowProps& props)
    {
        Init(props);
    }

    SDLWindow::~SDLWindow()
    {
        Shutdown();
    }

    bool SDLCALL SDLEventCallback([[maybe_unused]] void* userdata, SDL_Event* e)
    {
        const auto* data = static_cast<SDLWindow::WindowData*>(userdata);

        switch (e->type)
        {
        case SDL_EVENT_WINDOW_RESIZED:
            {
                const int w = e->window.data1;
                const int h = e->window.data2;
                WindowResizeEvent event_resize(w, h);
                if (data->EventCallback)
                {
                    data->EventCallback(event_resize);
                }
                break;
            }

        case SDL_EVENT_QUIT:
            {
                WindowCloseEvent event_quit{};
                if (data->EventCallback)
                {
                    data->EventCallback(event_quit);
                }
                break;
            }

        case SDL_EVENT_KEY_DOWN:
            {
                KeyboardPressedEvent event_keydown(static_cast<KeyCode>(e->key.scancode), 0);
                if (data->EventCallback)
                {
                    data->EventCallback(event_keydown);
                }
                break;
            }

        case SDL_EVENT_KEY_UP:
            {
                KeyboardReleaseEvent event_keyup(static_cast<KeyCode>(e->key.key));
                if (data->EventCallback)
                {
                    data->EventCallback(event_keyup);
                }
                break;
            }

        case SDL_EVENT_MOUSE_MOTION:
            {
                MouseMovedEvent event_mousemove(e->motion.x, e->motion.y);
                if (data->EventCallback)
                {
                    data->EventCallback(event_mousemove);
                }
                break;
            }

        case SDL_EVENT_MOUSE_WHEEL:
            {
                MouseScrolledEvent event_mousewheel(e->wheel.x, e->wheel.y);
                if (data->EventCallback)
                {
                    data->EventCallback(event_mousewheel);
                }
                break;
            }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                MouseButtonPressedEvent event_mouseclick(e->button.button);
                if (data->EventCallback)
                {
                    data->EventCallback(event_mouseclick);
                }
                break;
            }

        case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                MouseButtonReleasedEvent event_mouseclick(e->button.button);
                if (data->EventCallback)
                {
                    data->EventCallback(event_mouseclick);
                }
                break;
            }

        default:
            break;
        }

        return true;
    }

    void SDLWindow::Init([[maybe_unused]] const WindowProps& props)
    {
        SEED_PROFILE_FUNCTION();

        m_data.Title = WINDOW_NAME;
        m_data.Width = WINDOW_WIDTH;
        m_data.Height = WINDOW_HEIGHT;

        SEED_LOG_INFO("Creating Window: {} {}x{}", m_data.Title, m_data.Width, m_data.Height);

        if (!is_sdl_initialized)
        {
            int is_success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD);
            if (!is_success)
            {
                SEED_LOG_FATAL_ERROR("Failed to Initialize SDL");
                return;
            }
            is_sdl_initialized = true;
        }

        float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
        SDL_WindowFlags sdl_window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            // sdl_window_flags |= SDL_WINDOW_OPENGL;
        }

        m_window = SDL_CreateWindow(
            m_data.Title.c_str(),
            static_cast<int>(m_data.Width * main_scale),
            static_cast<int>(m_data.Height * main_scale),
            sdl_window_flags);

        if (auto error = SDL_GetError(); strcmp(error, "") != 0)
        {
            SEED_LOG_ERROR("Failed to create SDL Window: {}", error);
            return;
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            // m_graphic_context = std::make_shared<OpenGLContext>(m_window);
            // m_graphic_context->Init();
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
        {
            m_graphic_context = std::make_shared<SDL_GPUContext>(m_window);
            m_graphic_context->Init();
        }

        SetVSync(true);
        SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_ShowWindow(m_window);

        SDL_AddEventWatch(SDLEventCallback, &m_data);
    }

    void SDLWindow::OnUpdate()
    {
        SEED_PROFILE_FUNCTION();

        while (SDL_PollEvent(&m_event))
        {
            ImGui_ImplSDL3_ProcessEvent(&m_event);
        }

        m_graphic_context->SwapBuffers();
    }

    void SDLWindow::Shutdown()
    {
        SEED_PROFILE_FUNCTION();

        m_graphic_context->Shutdown();

        SEED_LOG_INFO("Shutting down Window...");
        SDL_RemoveEventWatch(SDLEventCallback, &m_data);

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            // const auto gl_ctx = SDL_GL_GetCurrentContext();
            // SDL_GL_DestroyContext(gl_ctx);
        }

        SDL_DestroyWindow(m_window);
    }

    void SDLWindow::SetVSync(const bool enabled)
    {
        if (enabled)
        {
            if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
            {
                // SDL_GL_SetSwapInterval(1);
            }

            if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
            {
                // const auto& app = Application::Get();
                // const auto handle_gpu_device = std::dynamic_pointer_cast<SDL_GPUContext>(app.GetWindow().GetGraphicContext())->GetDevice();
                // SDL_SetGPUSwapchainParameters(handle_gpu_device, m_window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC);
            }

            SDL_SetWindowSurfaceVSync(m_window, true);
        }
        else
        {
            if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
            {
                // SDL_GL_SetSwapInterval(0);
            }

            SDL_SetWindowSurfaceVSync(m_window, false);
        }
        m_data.VSync = enabled;
    }

    bool SDLWindow::IsVSync() const
    {
        return m_data.VSync;
    }
} // namespace seed
