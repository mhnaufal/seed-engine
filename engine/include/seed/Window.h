#pragma once

// #include <raylib.h>
#include "Event/Event.h"

#include <string>

namespace seed {

struct WindowProps {
    std::string Title{};
    unsigned int Width{};
    unsigned int Height{};

    WindowProps(const std::string& title = "Seed Engine", unsigned int width = 1280, unsigned int height = 720)
        : Title(title)
        , Width(width)
        , Height(height)
    {
    }
};

class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    static Window* Create(const WindowProps& props = WindowProps());
};

/* OLD v0.1
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
*/
} // namespace seed
