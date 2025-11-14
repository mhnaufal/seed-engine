#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#include <Application.h>
#include <ImGuiLayer.h>
#include <Logger.h>
#include <Window.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3_loader.h>

#include <SDL3/SDL.h>

namespace seed {
ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
{
}

auto ImGuiLayer::OnAttach() -> void
{
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
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    const auto& app = Application::Get();
    const auto gl_ctx = SDL_GL_GetCurrentContext();
    // const auto gl_ctx = ImGui::GetCurrentContext();

    ImGui_ImplSDL3_InitForOpenGL(static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow()), gl_ctx);
    ImGui_ImplOpenGL3_Init("#version 460");
}

auto ImGuiLayer::OnDetach() -> void
{
    SEED_LOG_INFO("Detaching ImGui Layer...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

auto ImGuiLayer::Begin() -> void
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

auto ImGuiLayer::End() -> void
{
    ImGuiIO& io = ImGui::GetIO();
    const auto& app = Application::Get();
    io.DisplaySize = ImVec2(
        static_cast<float>(app.GetWindow().GetWidth()),
        static_cast<float>(app.GetWindow().GetHeight()));

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        auto* backup_current_window = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());
        // auto* backup_current_window = SDL_GL_GetCurrentWindow();
        const SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
}

auto ImGuiLayer::OnImGuiRender(const float fps) -> void
{
    // bool on = true;
    // ImGui::ShowDemoWindow(&on);
    ImGui::Begin("FPS");
    ImGui::Text("FPS: %.1f", fps);
    ImGui::End();
}
} // namespace seed