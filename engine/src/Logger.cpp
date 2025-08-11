#include <Logger.h>
#include <spdlog/spdlog.h>

namespace seed {
auto Logger::log_info(const char* msg) -> void
{
    spdlog::info("[SEED] {}", msg);
}

auto Logger::log_warn(const char* msg) -> void
{
    spdlog::warn("[SEED] {}", msg);
}

auto Logger::log_debug(const char* msg) -> void
{
    spdlog::debug("[SEED] {}", msg);
}

auto Logger::log_error(const char* msg) -> void
{
    spdlog::error("[SEED] {}", msg);
}

} // namespace seed
