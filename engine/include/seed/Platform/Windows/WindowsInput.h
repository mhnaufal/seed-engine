#pragma once

#include <Input.h>

namespace seed {
class WindowsInput final : public Input {
protected:
    auto IsKeyPressedImpl(KeyCode key) -> bool override;
    auto IsMouseButtonPressedImpl(MouseCode button) -> bool override;
    auto GetMouseXImpl() -> float override;
    auto GetMouseYImpl() -> float override;
};
} // namespace seed