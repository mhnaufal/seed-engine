#pragma once

#include <vector>

namespace seed {
class Layer;

class LayerStack {
public:
    LayerStack() = default;
    ~LayerStack();

    auto PushLayer(Layer* layer) -> void;
    auto PushOverlay(Layer* layer) -> void;
    auto PopLayer(Layer* layer) -> void;
    auto PopOverlay(Layer* layer) -> void;

    auto begin() -> std::vector<Layer*>::iterator { return m_layers.begin(); }
    auto end() -> std::vector<Layer*>::iterator { return m_layers.end(); }

    [[nodiscard]] auto begin() const -> std::vector<Layer*>::const_iterator { return m_layers.begin(); }
    [[nodiscard]] auto end() const -> std::vector<Layer*>::const_iterator { return m_layers.end(); }

private:
    std::vector<Layer*> m_layers{};
    unsigned int m_layer_index{};
};
} // namespace seed