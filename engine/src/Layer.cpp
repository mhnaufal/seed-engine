#include <Layer.h>
#include <utility>

namespace seed {
Layer::Layer(std::string debug_name)
    : m_debug_name(std::move(debug_name))
{
}

} // namespace seed
