#pragma once

#include "Event/Event.h"

#include <string>

namespace seed {

constexpr auto WINDOW_NAME = "Seed Engine";
constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;

struct WindowProps {
    explicit WindowProps(
        const std::string& title = WINDOW_NAME,
        const unsigned int width = WINDOW_WIDTH,
        const unsigned int height = WINDOW_HEIGHT)
        : m_title(title)
          , m_width(width)
          , m_height(height)
    {
    }

private:
    std::string m_title{};
    unsigned int m_width{};
    unsigned int m_height{};
};

class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    [[nodiscard]] virtual unsigned int GetWidth() const = 0;
    [[nodiscard]] virtual unsigned int GetHeight() const = 0;
    [[nodiscard]] virtual void* GetNativeWindow() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    [[nodiscard]] virtual bool IsVSync() const = 0;

    static Window* Create(const WindowProps& props = WindowProps());
};
} // namespace seed