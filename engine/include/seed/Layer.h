#pragma once

#include "Event/Event.h"

namespace seed {
class Layer {
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual auto OnAttach() -> void {}
    virtual auto OnDetach() -> void {}
    virtual auto OnUpdate() -> void {}
    virtual auto OnEvent([[maybe_unused]] Event& event) -> void {}

    inline auto GetName() const -> const std::string& { return m_debug_name; }

protected:
    std::string m_debug_name{};
};
} // namespace seed