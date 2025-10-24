#include "ImGuiLayer.h"

#include "Window.h"

#include <Application.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <Logger.h>
#include <SDL3/SDL.h>

#include "imgui_impl_opengl3_loader.h"

namespace seed {
ImGuiLayer::ImGuiLayer()
    : seed::Layer("ImGuiLayer")
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
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
}

auto ImGuiLayer::OnImGuiRender() -> void
{
    bool on = true;
    ImGui::ShowDemoWindow(&on);
}

// ---------------------------

/* NOTE: version 1
auto ImGuiLayer::OnUpdate() -> void
{
    ImGuiIO& io = ImGui::GetIO();
    const auto& app = Application::Get();
    io.DisplaySize = ImVec2(
        static_cast<float>(app.GetWindow().GetWidth()),
        static_cast<float>(app.GetWindow().GetHeight()));


    ImGui::ShowDemoWindow();

    ImGui::Render();

    constexpr auto clear_color = ImVec4((249.0f / 255.0f), (155.0f / 255.0f), (254.0f / 255.0f), 1.00f);
    glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
    glClearColor(
        clear_color.x * clear_color.w,
        clear_color.y * clear_color.w,
        clear_color.z * clear_color.w,
        clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // SDL_GL_SwapWindow(app.GetWindow().GetNativeWindow());
}
*/
} // namespace seed