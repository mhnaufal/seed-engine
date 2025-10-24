#pragma once

#include "Event/ApplicationEvent.h"
#include "Event/Event.h"
#include "Layer.h"
#include "LayerStack.h"

#include <memory>

namespace seed {
class Logger;
class Window;
class ImGuiLayer;

class Application {
public:
    Application();

    ~Application();

    auto run() const -> void;

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

    std::unique_ptr<seed::Window> m_window = nullptr;
    std::unique_ptr<ImGuiLayer> m_imgui_layer = nullptr;
    seed::LayerStack m_layer_stack{};

    unsigned int m_vertex_array{}, m_vertex_buffer{}, m_index_buffer{};
};
} // namespace seed