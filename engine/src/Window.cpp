#include <Window.h>

namespace seed {

Window::Window(const int width, const int height, const int fps, const std::string& title)
    : m_screen_width(width)
    , m_screen_height(height)
    , m_fps(fps)
    , m_title(title)
{
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fps);
}

auto Window::SeedGetWindowInstance() -> Window&
{
    static Window instance;
    return instance;
}

auto Window::SeedInitWindow(const int width, const int height, const int fps, const std::string& title) -> bool
{
    Window(width, height, fps, title);
    return true;
}

auto Window::SeedIsWindowShown() -> bool
{
    m_is_window_shown = WindowShouldClose();
    return m_is_window_shown;
}

auto Window::SeedDestroyWindow() -> void
{
    CloseWindow();
}

} // namespace seed
