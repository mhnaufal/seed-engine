#include <Application.h>
#include <Logger.h>
#include <Window.h>

#include <Event/Event.h>
#include <Event/KeyboardEvent.h>
#include <Event/ApplicationEvent.h>
#include <Event/MouseEvent.h>

namespace seed {
Application::Application()
{
    seed::Logger::log_info("Starting application...");
    m_is_app_running = true;
    seed::Logger::set_log_level(seed::SPD_LOG_LEVEL::DEBUG);
    seed::Logger::log_info("Application started");
}

Application::~Application()
{
    seed::Logger::log_info("Stopping application...");
    delete m_window;
    m_is_app_running = false;
    seed::Logger::log_info("Application stopped");
}

auto Application::run() const -> void
{
    WindowResizeEvent window_resize_event(100, 200);
    seed::Logger::log_debug(window_resize_event.ToString().c_str());

    // while (m_is_app_running) {
    //     seed::Logger::log_info("Application running...");
    //     auto app_update_event = AppUpdateEvent();
    // }
}

} // namespace seed
