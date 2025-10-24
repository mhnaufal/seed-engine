#pragma once

#include "../Layer.h"

namespace seed {
class ImGuiLayer final : public Layer {
public:
    ImGuiLayer();

    auto OnAttach() -> void override;
    auto OnDetach() -> void override;
    auto OnImGuiRender() -> void override;

    static auto Begin() -> void;
    static auto End() -> void;

private:
};
} // namespace seed