#pragma once

#include <raylib.h>
#include <string>

namespace seed {
class Window {
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window() = default;

    static auto SeedGetWindowInstance() -> Window&;
    static auto SeedInitWindow(int width = 256, int height = 256, int fps = 60, const std::string& title = "Seed Game")
        -> bool;
    auto SeedIsWindowShown() -> bool;
    static auto SeedDestroyWindow() -> void;

private:
    Window() = default;
    Window(int width, int height, int fps, const std::string& title);

    int m_screen_width{};
    int m_screen_height{};
    int m_fps{};
    std::string m_title{};
    bool m_is_window_shown{false};
};
} // namespace seed
