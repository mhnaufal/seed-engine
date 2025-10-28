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

    auto OnEvent(seed::Event& e) -> void;

    auto PushLayer(seed::Layer* layer) -> void;
    auto PushOverlay(seed::Layer* layer) -> void;
    auto PopLayer(seed::Layer* layer) -> void;
    auto PopOverlay(seed::Layer* layer) -> void;

    inline static auto Get() -> Application& { return *s_instance; }
    [[nodiscard]] inline auto GetWindow() const -> Window& { return *m_window; }

private:
    auto OnWindowClose(WindowCloseEvent& e) -> bool;

    static Application* s_instance;
    bool m_is_app_running = false;

    std::unique_ptr<Window> m_window = nullptr;
    std::unique_ptr<ImGuiLayer> m_imgui_layer = nullptr;
    LayerStack m_layer_stack{};

    std::shared_ptr<Shader> m_triangle_shader = nullptr;
    std::shared_ptr<VertexArray> m_triangle_vertex_array = nullptr;
    std::shared_ptr<VertexBuffer> m_triangle_vertex_buffer = nullptr;
    std::shared_ptr<IndexBuffer> m_triangle_index_buffer = nullptr;

    Timestep m_delta_timestep{};
    float m_last_frame_time = 0.0f;
    float m_fps = 0.0f;
    float m_time_to_wait = 0.0f;
};
} // namespace seed