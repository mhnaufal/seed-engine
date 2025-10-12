#pragma once

#include "../../Window.h"

#include <SDL3/SDL.h>

namespace seed {
class WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void OnUpdate() override;

    inline unsigned int GetWidth() const override { return m_data.Width; }
    inline unsigned int GetHeight() const override { return m_data.Height; }

    inline void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    struct WindowData {
        std::string Title{};
        unsigned int Width{}, Height{};
        bool VSync{};

        EventCallbackFn EventCallback{};
    };

private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

private:
    SDL_Window* m_window{};
    SDL_Event m_event{};

    WindowData m_data{};
};
} // namespace seed