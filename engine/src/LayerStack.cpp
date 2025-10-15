#include <LayerStack.h>
#include <algorithm>

namespace seed {
LayerStack::LayerStack()
{
    m_layer_insert = m_layers.begin();
}

LayerStack::~LayerStack()
{
    for (Layer* layer : m_layers) { delete layer; }
}

auto LayerStack::PushLayer(seed::Layer* layer) -> void
{
    m_layer_insert = m_layers.emplace(m_layer_insert, layer);
    m_layer_insert += 1;
}

auto LayerStack::PushOverlay(seed::Layer* layer) -> void
{
    m_layers.emplace_back(layer);
}

auto LayerStack::PopLayer(seed::Layer* layer) -> void
{
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if (it != m_layers.end()) {
        m_layers.erase(it);
        m_layer_insert -= 1;
    }
}

auto LayerStack::PopOverlay(seed::Layer* layer) -> void
{
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if (it != m_layers.end()) {
        m_layers.erase(it);
    }
}
} // namespace seed
