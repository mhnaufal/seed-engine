#pragma once

#include "../Event/Event.h"
#include "../Layer.h"

namespace seed {
class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer() override;

    auto OnAttach() -> void override;
    auto OnDetach() -> void override;
    auto OnImGuiRender() -> void override;

    static auto Begin() -> void;
    static auto End() -> void;

private:
};
} // namespace seed