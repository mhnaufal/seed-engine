#include "Input.h"

#include <Application.h>
#include <Event/ApplicationEvent.h>
#include <Event/Event.h>
#include <Event/KeyboardEvent.h>
#include <Event/MouseEvent.h>
#include <Layer.h>
#include <Logger.h>
#include <SDL3/SDL.h>
#include <Window.h>

namespace seed {
// TODO: need static?
seed::Application* Application::s_instance = nullptr;

Application::Application()
{
    seed::Logger::log_info("Starting application...");
    m_is_app_running = true;
    seed::Logger::set_log_level(seed::SPD_LOG_LEVEL::DEBUG);

    s_instance = this;

    m_window = std::unique_ptr<seed::Window>(Window::Create());
    m_window->SetEventCallback([this](auto&& PH1) { OnEvent(std::forward<decltype(PH1)>(PH1)); });

    seed::Logger::log_info("Application started");
}

Application::~Application()
{
    seed::Logger::log_info("Stopping application...");
    SDL_Quit();
    m_is_app_running = false;
    seed::Logger::log_info("Application stopped");
}

auto Application::run() const -> void
{
    while (m_is_app_running) {
        // auto app_update_event = AppUpdateEvent();
        // seed::Logger::log_debug(app_update_event.ToString().c_str());

        for (const auto& layer : m_layer_stack) { layer->OnUpdate(); }

        // auto x_mouse_input = Input::GetMouseX();
        // auto y_mouse_input = Input::GetMouseY();
        // auto tab_key_pressed = Input::IsKeyPressed(Key::Tab);
        // auto mouse_press = Input::IsMouseButtonPressed(Mouse::ButtonLeft);
        // if () {
        //     SEED_LOG_ERROR("ASU {}-{}", x_mouse_input, y_mouse_input);
        //     SEED_LOG_INFO("\tEEK {}\n", tab_key_pressed);
        //     SEED_LOG_WARN("\tEEK {}\n", mouse_press);
        // }

        m_window->OnUpdate();
    }
}

auto Application::OnEvent(seed::Event& e) -> void
{
    // NOTE: ON or OFF
    // SEED_LOG_DEBUG("{}", e.ToString());

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(
        [this](auto&& PH1) { return OnWindowClose(std::forward<decltype(PH1)>(PH1)); });

    for (auto it = m_layer_stack.end(); it != m_layer_stack.begin();) {
        (*--it)->OnEvent(e);
        if (e.GetHandled()) {
            break;
        }
    }
}

auto Application::OnWindowClose([[maybe_unused]] WindowCloseEvent& e) -> bool
{
    m_is_app_running = false;
    return true;
}

auto Application::PushLayer(seed::Layer* layer) -> void
{
    m_layer_stack.PushLayer(layer);
    layer->OnAttach();
}

auto Application::PushOverlay(seed::Layer* layer) -> void
{
    m_layer_stack.PushOverlay(layer);
    layer->OnAttach();
}
} // namespace seed