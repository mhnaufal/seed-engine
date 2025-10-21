#pragma once

#include "Event/Event.h"

namespace seed {
class Layer {
public:
    explicit Layer(std::string  name = "Layer");
    virtual ~Layer() = default;

    virtual auto OnAttach() -> void {}
    virtual auto OnDetach() -> void {}
    virtual auto OnUpdate() -> void {}
    virtual auto OnEvent([[maybe_unused]] Event& event) -> void {}
    virtual auto OnImGuiRender() -> void {}

    [[nodiscard]] inline auto GetName() const -> const std::string& { return m_debug_name; }

protected:
    std::string m_debug_name{};
};
} // namespace seed