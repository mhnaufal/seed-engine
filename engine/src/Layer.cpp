#include <Layer.h>
#include <Logger.h>

namespace seed {
Layer::Layer(std::string name)
    : m_debug_name(std::move(name))
{
    SEED_LOG_VERBOSE("Initializing debug layer: {}", m_debug_name);
}
} // namespace seed