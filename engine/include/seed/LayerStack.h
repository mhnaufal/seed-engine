#pragma once

#include "Event/Event.h"
#include "Layer.h"

#include <string>
#include <vector>

namespace seed {
class LayerStack {
public:
    LayerStack() = default;
    ~LayerStack();

    auto PushLayer(seed::Layer* layer) -> void;
    auto PushOverlay(seed::Layer* layer) -> void;
    auto PopLayer(seed::Layer* layer) -> void;
    auto PopOverlay(seed::Layer* layer) -> void;

    auto begin() -> std::vector<seed::Layer*>::iterator { return m_layers.begin(); }
    auto end() -> std::vector<seed::Layer*>::iterator { return m_layers.end(); }

    [[nodiscard]] auto begin() const -> std::vector<seed::Layer*>::const_iterator { return m_layers.begin(); }
    [[nodiscard]] auto end() const -> std::vector<seed::Layer*>::const_iterator { return m_layers.end(); }

private:
    std::vector<seed::Layer*> m_layers{};
    // std::vector<seed::Layer*>::iterator m_layer_insert{};
    unsigned int m_layer_index{};
};
} // namespace seed