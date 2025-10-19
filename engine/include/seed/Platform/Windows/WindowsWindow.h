#pragma once

#include "../../Window.h"

#include <SDL3/SDL.h>

namespace seed {
class WindowsWindow final : public Window {
public:
    explicit WindowsWindow(const WindowProps& props);
    ~WindowsWindow() override;

    void OnUpdate() override;

    [[nodiscard]] inline auto GetWidth() const -> unsigned int override { return m_data.Width; }
    [[nodiscard]] inline auto GetHeight() const -> unsigned int override { return m_data.Height; }
    [[nodiscard]] inline auto GetNativeWindow() const -> SDL_Window* override { return m_window; }

    inline auto SetEventCallback(const EventCallbackFn& callback) -> void override { m_data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    [[nodiscard]] bool IsVSync() const override;

    struct WindowData {
        std::string Title{};
        unsigned int Width{}, Height{};
        bool VSync{};

        EventCallbackFn EventCallback{};
    };

private:
    virtual auto Init(const WindowProps& props) -> void;
    virtual auto Shutdown() -> void;

private:
    SDL_Window* m_window{};
    SDL_Event m_event{};

    WindowData m_data{};
};
} // namespace seed