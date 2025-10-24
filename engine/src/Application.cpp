#include <Application.h>
#include <Event/ApplicationEvent.h>
#include <Event/Event.h>
#include <Layer.h>
#include <Logger.h>
#include <SDL3/SDL.h>
#include <Window.h>
#include <imgui.h>
#include <ImGui/ImGuiLayer.h>

#include "imgui_impl_opengl3_loader.h"

namespace seed {
// TODO: need static?
seed::Application* Application::s_instance = nullptr;

Application::Application()
{
    seed::Logger::log_info("Starting application...");
    seed::Logger::set_log_level(seed::SPD_LOG_LEVEL::DEBUG);

    s_instance = this;

    m_window = std::unique_ptr<seed::Window>(Window::Create());
    m_window->SetEventCallback([this](auto&& PH1) { OnEvent(std::forward<decltype(PH1)>(PH1)); });

    m_imgui_layer = std::make_unique<ImGuiLayer>();
    PushOverlay(m_imgui_layer.get());

    //* TODO: change to SDL
    /* [#] Initialize */
    glGenVertexArrays(1, &m_vertex_array);
    /* [#] Filling the data */
    glBindVertexArray(m_vertex_array);
    /* [#] Initialize */
    glGenBuffers(1, &m_vertex_buffer);
    /* [#] Filling the data */
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
    constexpr float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };
    /* [#] Send data to GPU */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0x88E4);
    /* [#] Register Vertex Array */
    glEnableVertexAttribArray(0);
    /* [#] Defined Registered Vertex Array */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    /* [#] Initialize Index Buffer */
    glGenBuffers(1, &m_index_buffer);
    /* [#] Filling Index Buffer Data */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
    constexpr unsigned int indices[3] = {0, 1, 2};
    /* [#] Send Index Buffer Data to GPU */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 0x88E4);
    //* TODO: change to SDL

    m_is_app_running = true;
    seed::Logger::log_info("Application started");
}

Application::~Application()
{
    seed::Logger::log_info("Stopping application...");

    PopOverlay(m_imgui_layer.get());
    m_imgui_layer.reset();

    m_window.reset();

    SDL_Quit();

    m_is_app_running = false;
    seed::Logger::log_info("Application stopped");
}

auto Application::run() const -> void
{
    while (m_is_app_running) {
        for (const auto& layer : m_layer_stack) { layer->OnUpdate(); }

        //* NOTE:
        // auto x_mouse_input = Input::GetMouseX();
        // auto y_mouse_input = Input::GetMouseY();
        // auto tab_key_pressed = Input::IsKeyPressed(Key::Tab);
        // auto mouse_press = Input::IsMouseButtonPressed(Mouse::ButtonLeft);
        // if () {
        //     SEED_LOG_ERROR("ASU {}-{}", x_mouse_input, y_mouse_input);
        //     SEED_LOG_INFO("\tEEK {}\n", tab_key_pressed);
        //     SEED_LOG_WARN("\tEEK {}\n", mouse_press);
        // }

        //* TODO: change to SDL
        constexpr auto clear_color = ImVec4((249.0f / 255.0f), (155.0f / 255.0f), (254.0f / 255.0f), 1.00f);
        glViewport(0, 0, static_cast<int>(GetWindow().GetWidth()), static_cast<int>(GetWindow().GetHeight()));
        glClearColor(
            clear_color.x * clear_color.w,
            clear_color.y * clear_color.w,
            clear_color.z * clear_color.w,
            clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(m_vertex_array);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        //* TODO: change to SDL

        ImGuiLayer::Begin();
        for (Layer* layer : m_layer_stack) {
            layer->OnImGuiRender();
        }
        ImGuiLayer::End();

        m_window->OnUpdate();
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