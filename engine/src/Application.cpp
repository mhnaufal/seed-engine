#include <Application.h>
#include <Core/Definitions.h>
#include <imgui.h>
#include <ImGui/ImGuiLayer.h>
#include <Layer.h>
#include <Logger.h>
#include <Renderer/Buffer.h>
#include <Renderer/Renderer.h>
#include <Renderer/Shader.h>
#include <SDL3/SDL.h>
#include <Window.h>

#include "RenderCommand.h"
#include "VertexArray.h"

// TODO: refactor
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

namespace seed {
// TODO: need static?
seed::Application* Application::s_instance = nullptr;

Application::Application()
{
    SEED_LOG_INFO("Starting Application...");
    seed::Logger::set_log_level(seed::SPD_LOG_LEVEL::DEBUG);

    s_instance = this;

    m_window = std::unique_ptr<seed::Window>(Window::Create());
    m_window->SetEventCallback([this](auto&& PH1) { OnEvent(std::forward<decltype(PH1)>(PH1)); });

    m_imgui_layer = std::make_unique<ImGuiLayer>();
    PushOverlay(m_imgui_layer.get());

    m_is_app_running = true;
    SEED_LOG_INFO("Application started");
}

Application::~Application()
{
    SEED_LOG_INFO("Stopping Application...");

    PopOverlay(m_imgui_layer.get());
    m_imgui_layer.reset();

    m_window.reset();

    SDL_Quit();

    m_is_app_running = false;
    SEED_LOG_INFO("Application stopped");
}

auto Application::run() -> void
{
    while (m_is_app_running) {
        //* Handle Delta time & FPS
        // TODO: add constant when doing movement multiplied with delta time
        const auto current_time = static_cast<float>(SDL_GetTicks() / 1000.0f);

        for (const auto& layer : m_layer_stack) {
            layer->OnUpdate(m_delta_timestep);
        }

        ImGuiLayer::Begin();
        for (Layer* layer : m_layer_stack) {
            layer->OnImGuiRender(m_fps);
        }
        ImGuiLayer::End();

        m_window->OnUpdate();

        //* Handle Delta time & FPS
        // TODO: add constant when doing movement multiplied with delta time
        m_delta_timestep = current_time - m_last_frame_time;
        m_last_frame_time = current_time;
        if (m_delta_timestep.GetMilliSeconds() > 0.0f) {
            m_fps = 1.0f / static_cast<float>(m_delta_timestep);
        }
        if (m_delta_timestep < TARGET_FRAME_TIME) {
            m_time_to_wait = TARGET_FRAME_TIME - m_delta_timestep;
        }
        if (m_time_to_wait > 0.0f) {
            SDL_DelayPrecise(static_cast<Uint64>(m_time_to_wait));
        }
    }
}

auto Application::OnEvent(seed::Event& e) -> void
{
    // NOTE: ON or OFF the events
    SEED_LOG_DEBUG("{}", e.ToString());

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

auto Application::PopLayer(seed::Layer* layer) -> void
{
    m_layer_stack.PopLayer(layer);
}

auto Application::PopOverlay(seed::Layer* layer) -> void
{
    m_layer_stack.PopOverlay(layer);
}
} // namespace seed