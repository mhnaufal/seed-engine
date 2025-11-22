#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <Application.h>
#include <ImGuiLayer.h>
#include <Logger.h>
#include <RendererAPI.h>
#include <SDL_GPUContext.h>
#include <Window.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>
#include <imgui_impl_sdlgpu3.h>
#include <imgui_impl_sdl3.h>

#include <SDL3/SDL.h>

namespace seed
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }

    auto ImGuiLayer::OnAttach() -> void
    {
        SEED_PROFILE_FUNCTION();

        SEED_LOG_INFO("Attaching ImGui layer...");
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsLight();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        const auto& app = Application::Get();

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            const auto gl_ctx = ImGui::GetCurrentContext();

            ImGui_ImplSDL3_InitForOpenGL(static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow()), gl_ctx);
            ImGui_ImplOpenGL3_Init("#version 460");
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
        {
            ImGui_ImplSDL3_InitForSDLGPU(static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow()));

            ImGui_ImplSDLGPU3_InitInfo init_info{};
            init_info.Device = std::dynamic_pointer_cast<SDL_GPUContext>(app.GetWindow().GetGraphicContext())->
                GetDevice();
            ImGui_ImplSDLGPU3_Init(&init_info);
        }
    }

    auto ImGuiLayer::OnDetach() -> void
    {
        SEED_PROFILE_FUNCTION();

        SEED_LOG_INFO("Detaching ImGui Layer...");

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            ImGui_ImplOpenGL3_Shutdown();
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
        {
            ImGui_ImplSDLGPU3_Shutdown();
        }

        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    auto ImGuiLayer::Begin() -> void
    {
        SEED_PROFILE_FUNCTION();

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            ImGui_ImplOpenGL3_NewFrame();
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
        {
            ImGui_ImplSDLGPU3_NewFrame();
        }

        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    auto ImGuiLayer::End() -> void
    {
        SEED_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        const auto& app = Application::Get();
        io.DisplaySize = ImVec2(
            static_cast<float>(app.GetWindow().GetWidth()),
            static_cast<float>(app.GetWindow().GetHeight()));

        ImGui::Render();

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
        {
            SDL_GPUCommandBuffer* command_buffer{};
            SDL_GPURenderPass* render_pass{};
            SDL_GPUGraphicsPipeline* pipeline{};
            // ImGui_ImplSDLGPU3_RenderDrawData(ImGui::GetDrawData(), command_buffer, render_pass, pipeline);
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
            {
                auto* backup_current_window = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());
                SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
            }

            if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
            {
            }
        }
    }

    auto ImGuiLayer::OnImGuiRender(const float fps) -> void
    {
        SEED_PROFILE_FUNCTION();

        // bool on = true;
        // ImGui::ShowDemoWindow(&on);

        ImGui::Begin("FPS");
        ImGui::Text("FPS: %.1f", fps);
        ImGui::End();
    }
} // namespace seed
