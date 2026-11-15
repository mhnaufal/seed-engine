#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <Application.h>
#include <ImGuiLayer.h>
#include <Logger.h>
#include <RendererAPI.h>
#include <SDL_GPUContext.h>
#include <Window.h>

#include <imgui.h>
// #include <imgui_impl_opengl3.h>
// #include <imgui_impl_opengl3_loader.h>
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

            // ImGui_ImplSDL3_InitForOpenGL(static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow()), gl_ctx);
            // ImGui_ImplOpenGL3_Init("#version 460");
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
        {
            const auto handle_window = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());
            const auto handle_gpu_device = std::dynamic_pointer_cast<SDL_GPUContext>(
                    app.GetWindow().GetGraphicContext())->
                GetDevice();
            ImGui_ImplSDL3_InitForSDLGPU(handle_window);

            ImGui_ImplSDLGPU3_InitInfo init_info{};
            init_info.Device = handle_gpu_device;
            init_info.ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(handle_gpu_device, handle_window);
            init_info.MSAASamples = SDL_GPU_SAMPLECOUNT_1;
            init_info.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;
            init_info.PresentMode = SDL_GPU_PRESENTMODE_VSYNC;
            ImGui_ImplSDLGPU3_Init(&init_info);
        }
    }

    auto ImGuiLayer::OnDetach() -> void
    {
        SEED_PROFILE_FUNCTION();

        SEED_LOG_INFO("Detaching ImGui Layer...");

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            // ImGui_ImplOpenGL3_Shutdown();
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
            // ImGui_ImplOpenGL3_NewFrame();
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

        SDL_GPUCommandBuffer* handle_command_buffer = nullptr;

        if (RendererAPI::GetAPI() == RendererAPI::API::OPENGL)
        {
            // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        if (RendererAPI::GetAPI() == RendererAPI::API::SDL_GPU)
        {
            const auto draw_data = ImGui::GetDrawData();
            const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);

            const auto handle_window = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());
            const auto handle_gpu_device = std::dynamic_pointer_cast<SDL_GPUContext>(
                    app.GetWindow().GetGraphicContext())->
                GetDevice();
            // handle_command_buffer = std::dynamic_pointer_cast<SDL_GPUContext>(
            //         app.GetWindow().GetGraphicContext())->
            //     GetCommandBuffer();
            auto handle_swapchain_texture = std::dynamic_pointer_cast<SDL_GPUContext>(
                    app.GetWindow().GetGraphicContext())->
                GetSwapchainTexture();
            // SDL_GPUTexture* handle_swapchain_texture{};

            handle_command_buffer = SDL_AcquireGPUCommandBuffer(handle_gpu_device);
            SDL_WaitAndAcquireGPUSwapchainTexture(handle_command_buffer, handle_window, &handle_swapchain_texture,
                                                  nullptr, nullptr);
            if (handle_swapchain_texture != nullptr && !is_minimized)
            {
                ImGui_ImplSDLGPU3_PrepareDrawData(draw_data, handle_command_buffer);

                SDL_GPUColorTargetInfo target_info = {};
                target_info.texture = handle_swapchain_texture;
                target_info.clear_color = SDL_FColor{1.0f, 1.0f, 1.0f, 0.0f}; // WHITE
                target_info.load_op = SDL_GPU_LOADOP_CLEAR;
                target_info.store_op = SDL_GPU_STOREOP_STORE;

                SDL_GPURenderPass* render_pass =
                    SDL_BeginGPURenderPass(handle_command_buffer, &target_info, 1, nullptr);
                // SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(handle_command_buffer, nullptr, 1, nullptr);
                ImGui_ImplSDLGPU3_RenderDrawData(draw_data, handle_command_buffer, render_pass);
                SDL_EndGPURenderPass(render_pass);
            }
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
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
            }
        }

        SDL_SubmitGPUCommandBuffer(handle_command_buffer);
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
