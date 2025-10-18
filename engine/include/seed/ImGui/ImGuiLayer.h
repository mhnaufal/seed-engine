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
    auto OnUpdate() -> void override;
    auto OnEvent(Event& event) -> void override;

private:
};
} // namespace seed