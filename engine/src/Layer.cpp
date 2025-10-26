#include <Layer.h>

namespace seed {
Layer::Layer(std::string name)
    : m_debug_name(std::move(name))
{
}

} // namespace seed
