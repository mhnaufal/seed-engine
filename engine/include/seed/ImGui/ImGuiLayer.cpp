#include "ImGuiLayer.h"

#include "Window.h"

#include <Application.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <Logger.h>

#include "imgui_impl_opengl3_loader.h"

namespace seed {
ImGuiLayer::ImGuiLayer()
    : seed::Layer("ImGuiLayer")
{
}

ImGuiLayer::~ImGuiLayer()
= default;

auto ImGuiLayer::OnAttach() -> void
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.BackendFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.BackendFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.BackendFlags |= ImGuiConfigFlags_DockingEnable;
    io.BackendFlags |= ImGuiConfigFlags_ViewportsEnable;

    // TODO: handle key
    // io.AddKeyEvent(ImGuiKey_Tab, key == SDLK_TAB);

    const auto& app = Application::Get();
    const auto gl_ctx = SDL_GL_GetCurrentContext();

    ImGui_ImplSDL3_InitForOpenGL(app.GetWindow().GetNativeWindow(), gl_ctx);
    ImGui_ImplOpenGL3_Init("#version 460");
}

auto ImGuiLayer::OnDetach() -> void
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

auto ImGuiLayer::OnUpdate() -> void
{
    ImGuiIO& io = ImGui::GetIO();
    const auto& app = Application::Get();
    io.DisplaySize = ImVec2(
        static_cast<float>(app.GetWindow().GetWidth()),
        static_cast<float>(app.GetWindow().GetHeight()));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

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

auto ImGuiLayer::OnEvent(Event& event) -> void
{
}
} // namespace seed