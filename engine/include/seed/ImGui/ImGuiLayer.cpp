#include "ImGuiLayer.h"

#include "Window.h"

#include <Application.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <SDL3/SDL_keycode.h>
#include <Logger.h>

namespace seed {
ImGuiLayer::ImGuiLayer()
    : seed::Layer("ImGuiLayer")
{
    SEED_LOG_DEBUG("ASU 3");
}

ImGuiLayer::~ImGuiLayer()
= default;

auto ImGuiLayer::OnAttach() -> void
{
    SEED_LOG_DEBUG("ASU 1");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // TODO: handle key
    // io.AddKeyEvent(ImGuiKey_Tab, key == SDLK_TAB);

    ImGui_ImplOpenGL3_Init("#version 460");
    SEED_LOG_DEBUG("ASU 2");
}

auto ImGuiLayer::OnDetach() -> void
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

auto ImGuiLayer::OnUpdate() -> void
{
    ImGuiIO& io = ImGui::GetIO();
    auto& app = Application::Get();
    io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

auto ImGuiLayer::OnEvent(Event& event) -> void
{
}

} // namespace seed