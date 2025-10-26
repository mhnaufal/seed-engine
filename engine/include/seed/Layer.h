#pragma once

#include <string>

namespace seed {
class Event;
class Timestep;

class Layer {
public:
    explicit Layer(std::string name = "Layer");
    virtual ~Layer() = default;

    virtual auto OnAttach() -> void {}
    virtual auto OnDetach() -> void {}
    virtual auto OnUpdate([[maybe_unused]] Timestep& time_step) -> void {}
    virtual auto OnEvent([[maybe_unused]] Event& event) -> void {}
    virtual auto OnImGuiRender([[maybe_unused]] const float fps) -> void {}

    [[nodiscard]] inline auto GetName() const -> const std::string& { return m_debug_name; }

protected:
    std::string m_debug_name{};
};
} // namespace seed