#include <Layer.h>
#include <LayerStack.h>

namespace seed {
LayerStack::~LayerStack()
{
    for (Layer* layer : m_layers) {
        layer->OnDetach();
    }
}

auto LayerStack::PushLayer(seed::Layer* layer) -> void
{
    // m_layer_insert = m_layers.emplace(m_layer_insert, layer);
    m_layers.emplace(m_layers.begin() + m_layer_index, layer);
    m_layer_index += 1;
}

auto LayerStack::PushOverlay(seed::Layer* layer) -> void
{
    m_layers.emplace_back(layer);
}

auto LayerStack::PopLayer(seed::Layer* layer) -> void
{
    auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_index, layer);
    if (it != m_layers.begin() + m_layer_index) {
        layer->OnDetach();
        m_layers.erase(it);
        m_layer_index -= 1;
    }
}

auto LayerStack::PopOverlay(seed::Layer* layer) -> void
{
    auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_index, layer);
    if (it != m_layers.end()) {
        layer->OnDetach();
        m_layers.erase(it);
    }
}
} // namespace seed