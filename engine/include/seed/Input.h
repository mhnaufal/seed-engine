#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

namespace seed {
class Input {
public:
    inline static auto IsKeyPressed(const KeyCode key) -> bool { return s_instance->IsKeyPressedImpl(key); }

    inline static auto IsMouseButtonPressed(const MouseCode button) -> bool
    {
        return s_instance->IsMouseButtonPressedImpl(button);
    }

    inline static auto GetMouseX() -> float { return s_instance->GetMouseXImpl(); }
    inline static auto GetMouseY() -> float { return s_instance->GetMouseYImpl(); }
    virtual ~Input() = default;

protected:
    virtual auto IsKeyPressedImpl(KeyCode key) -> bool = 0;
    virtual auto IsMouseButtonPressedImpl(MouseCode button) -> bool = 0;
    virtual auto GetMouseXImpl() -> float = 0;
    virtual auto GetMouseYImpl() -> float = 0;

private:
    static Input* s_instance;
};
} // namespace seed