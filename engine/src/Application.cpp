#include <Application.h>
#include <Core/Definitions.h>
#include <Core/Timestep.h>
#include <Event/ApplicationEvent.h>
#include <Event/Event.h>
#include <imgui.h>
#include <ImGui/ImGuiLayer.h>
#include <Layer.h>
#include <Logger.h>
#include <Renderer/Buffer.h>
#include <Renderer/Renderer.h>
#include <Renderer/Shader.h>
#include <SDL3/SDL.h>
#include <Window.h>

#include "imgui_impl_opengl3_loader.h"
#include "OpenGLBuffer.h"

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

    // /* 🐤 TODO: change to SDL
    Renderer::SetRendererAPI(RendererAPI::OPENGL);

    // [#] Initialize vertex array
    glGenVertexArrays(1, &m_vertex_array);
    // [#] Bind the vertex array
    glBindVertexArray(m_vertex_array);

    constexpr float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.6f, 0.4f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.5f, 0.6f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.8f, 0.4f, 0.6f, 1.0f
    };
    m_vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    const BufferLayout layout(
    {
        {ShaderDataType::FLOAT3, std::string("attribute_position")},
        {ShaderDataType::FLOAT4, std::string("attribute_color")}
    });
    m_vertex_buffer->SetLayout(layout);

    uint32_t index = 0;
    const auto& i_layout = m_vertex_buffer->GetLayout();
    for (const auto& element : i_layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            static_cast<int>(element.GetComponentCount()),
            ShaderDataTypeToOpenGLDataType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            static_cast<int>(i_layout.GetStride()),
            reinterpret_cast<const void*>(element.offset));
        index++;
    }

    //* NOTE:
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)12);
    //* NOTE:

    constexpr uint32_t indices[3] = {0, 1, 2};
    m_index_buffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

    std::string vertex_code = R"(
        #version 460 core

        layout(location = 0) in vec3 attribute_position;
        layout(location = 1) in vec4 attribute_color;

        out vec3 output_position;
        out vec4 output_color;

        void main()
        {
            output_position = attribute_position;
            output_color = attribute_color;
            gl_Position = vec4(attribute_position, 1.0);
        }
    )";

    std::string fragment_code = R"(
        #version 460 core

        layout(location = 0) out vec4 color;

        in vec3 output_position;
        in vec4 output_color;

        void main()
        {
            // Clamp (-1, +1) into (0, +1)
            // color = vec4((output_position + 1) / 2, 1.0);
            color = output_color;
        }
    )";

    m_shader = std::make_unique<Shader>(vertex_code, fragment_code);
    // 🐤 TODO: change to SDL */

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
        const auto current_time = static_cast<float>(SDL_GetTicks());

        for (const auto& layer : m_layer_stack) {
            layer->OnUpdate(m_delta_timestep);
        }

        //* 🐤 TODO: change to SDL
        constexpr auto clear_color = ImVec4((249.0f / 255.0f), (155.0f / 255.0f), (254.0f / 255.0f), 1.00f);
        glViewport(0, 0, static_cast<int>(GetWindow().GetWidth()), static_cast<int>(GetWindow().GetHeight()));
        glClearColor(
            clear_color.x * clear_color.w,
            clear_color.y * clear_color.w,
            clear_color.z * clear_color.w,
            clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // [#] Bind the created shader
        m_shader->Bind();
        // [#] Bind the vertex array
        glBindVertexArray(m_vertex_array);
        // [#] Draw the data inside GPU & OpenGL
        glDrawElements(GL_TRIANGLES, static_cast<int>(m_index_buffer->GetCount()), GL_UNSIGNED_INT, nullptr);
        //* 🐤 TODO: change to SDL

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
            m_fps = 1000.0f / static_cast<float>(m_delta_timestep);
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

auto Application::PopLayer(seed::Layer* layer) -> void
{
    m_layer_stack.PopLayer(layer);
}

auto Application::PopOverlay(seed::Layer* layer) -> void
{
    m_layer_stack.PopOverlay(layer);
}
} // namespace seed