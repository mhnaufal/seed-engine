#include "WindowsInput.h"

#include "Application.h"
#include "Window.h"

#include <SDL3/SDL.h>

namespace seed {
Input* Input::s_instance = new WindowsInput();

auto WindowsInput::IsKeyPressedImpl(const KeyCode key) -> bool
{
    [[maybe_unused]] auto window = static_cast<SDL_Window*>(Application::Get().GetWindow().GetNativeWindow());
    const auto state = SDL_GetKeyboardState(nullptr);
    const int scancode = static_cast<int>(key);

    return state[scancode] != 0;
}

auto WindowsInput::IsMouseButtonPressedImpl(const MouseCode button) -> bool
{
    const auto state = SDL_GetMouseState(nullptr, nullptr);
    const int scancode = static_cast<int>(button);

    return SDL_BUTTON_MASK(scancode) == state;
}

auto WindowsInput::GetMouseXImpl() -> float
{
    float x{};
    [[maybe_unused]] const auto state = SDL_GetMouseState(&x, nullptr);
    return x;
}

auto WindowsInput::GetMouseYImpl() -> float
{
    float y{};
    [[maybe_unused]] const auto state = SDL_GetMouseState(nullptr, &y);
    return y;
}
} // namespace seed