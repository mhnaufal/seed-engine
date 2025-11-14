#pragma once

#include "Core/Timestep.h"
#include "Event/ApplicationEvent.h"
#include "Event/Event.h"
#include "LayerStack.h"

#include <memory>

namespace seed {
class Logger;
class Window;
class ImGuiLayer;
class Shader;
class VertexBuffer;
class IndexBuffer;
class Layer;
class VertexArray;

class Application {
public:
    Application();

    ~Application();

    auto run() -> void;

    auto OnEvent(Event& e) -> void;

    auto PushLayer(Layer* layer) -> void;
    auto PushOverlay(Layer* layer) -> void;
    auto PopLayer(Layer* layer) -> void;
    auto PopOverlay(Layer* layer) -> void;

    inline static auto Get() -> Application& { return *s_instance; }
    [[nodiscard]] inline auto GetWindow() const -> Window& { return *m_window; }

private:
    auto OnWindowClose(WindowCloseEvent& e) -> bool;
    auto OnWindowResize(WindowResizeEvent& e) -> bool;

    static Application* s_instance;
    bool m_is_app_running = false;
    bool m_is_minimized = false;

    std::unique_ptr<Window> m_window = nullptr;
    std::unique_ptr<ImGuiLayer> m_imgui_layer = nullptr;
    LayerStack m_layer_stack{};

    Timestep m_delta_timestep{};
    float m_last_frame_time = 0.0f;
    float m_fps = 0.0f;
    float m_time_to_wait = 0.0f;
};
} // namespace seed