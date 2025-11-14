#include <Layer.h>
#include <LayerStack.h>
#include <Logger.h>

namespace seed {
LayerStack::~LayerStack()
{
    for (Layer* layer : m_layers) {
        layer->OnDetach();
    }
}

auto LayerStack::PushLayer(Layer* layer) -> void
{
    SEED_LOG_VERBOSE("Pushing new layer: {}", layer->GetName());

    m_layers.emplace(m_layers.begin() + m_layer_index, layer);
    m_layer_index += 1;
}

auto LayerStack::PushOverlay(Layer* layer) -> void
{
    SEED_LOG_VERBOSE("Pushing new overlayer: {}", layer->GetName());

    m_layers.emplace_back(layer);
}

auto LayerStack::PopLayer(Layer* layer) -> void
{
    SEED_LOG_VERBOSE("Poping new layer: {}", layer->GetName());

    auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_index, layer);
    if (it != m_layers.begin() + m_layer_index) {
        layer->OnDetach();
        m_layers.erase(it);
        m_layer_index -= 1;
    }
}

auto LayerStack::PopOverlay(Layer* layer) -> void
{
    SEED_LOG_VERBOSE("Poping overlayer: {}", layer->GetName());

    auto it = std::find(m_layers.begin(), m_layers.begin() + m_layer_index, layer);
    if (it != m_layers.end()) {
        layer->OnDetach();
        m_layers.erase(it);
    }
}
} // namespace seed