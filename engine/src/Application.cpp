#include <Application.h>
#include <Logger.h>
#include <Window.h>

namespace seed {
Application::Application()
{
    seed::Logger::log_info("Starting application...");

    m_window = &Window::SeedGetWindowInstance();
    m_is_app_running = m_window->SeedInitWindow(1280, 800, 60, "C++ JRPG");

    if (!m_is_app_running) {
        seed::Logger::log_error("Failed to initialize window");
    }

    seed::Logger::log_info("Application started");
}

Application::~Application()
{
    seed::Logger::log_info("Stopping application...");
    m_window->SeedDestroyWindow();
    delete m_window;
    m_is_app_running = false;
    seed::Logger::log_info("Application stopped");
}

auto Application::run() const -> void
{
    while (m_is_app_running) {
        seed::Logger::log_info("Application running...");
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("HALOO", 50, 100, 20, Color{100, 10, 100, 100});
        EndDrawing();
    }
}

} // namespace seed
