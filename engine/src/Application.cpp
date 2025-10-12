#include <Application.h>
#include <Event/ApplicationEvent.h>
#include <Event/Event.h>
#include <Event/KeyboardEvent.h>
#include <Event/MouseEvent.h>
#include <Logger.h>
#include <SDL3/SDL.h>
#include <Window.h>

namespace seed {
Application::Application()
{
    seed::Logger::log_info("Starting application...");
    m_is_app_running = true;
    seed::Logger::set_log_level(seed::SPD_LOG_LEVEL::DEBUG);

    m_window = std::unique_ptr<seed::Window>(Window::Create());
    m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

    seed::Logger::log_info("Application started");
}

Application::~Application()
{
    seed::Logger::log_info("Stopping application...");
    SDL_Quit();
    m_is_app_running = false;
    seed::Logger::log_info("Application stopped");
}

auto Application::run() const -> void
{
    while (m_is_app_running) {
        // auto app_update_event = AppUpdateEvent();
        // seed::Logger::log_debug(app_update_event.ToString().c_str());

        m_window->OnUpdate();
    }
}

auto Application::OnEvent(seed::Event& e) -> void
{
    SEED_LOG_DEBUG("{}", e.ToString());

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
}

auto Application::OnWindowClose([[maybe_unused]] WindowCloseEvent& e) -> bool
{
    m_is_app_running = false;
    return true;
}

} // namespace seed
