#include <Window.h>

namespace seed {

/* OLD v0.1
Window::Window(const int width, const int height, const int fps, const std::string& title)
    : m_screen_width(width)
    , m_screen_height(height)
    , m_fps(fps)
    , m_title(title)
{
}

auto Window::SeedGetWindowInstance() -> Window&
{
    static Window instance;
    return instance;
}

auto Window::SeedInitWindow(const int width, const int height, const int fps, const std::string& title) -> bool
{
    return true;
}

auto Window::SeedIsWindowShown() -> bool
{
    return m_is_window_shown;
}

auto Window::SeedDestroyWindow() -> void
{
}
*/

} // namespace seed
