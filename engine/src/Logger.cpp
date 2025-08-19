#include <Logger.h>
#include <spdlog/spdlog.h>

namespace seed {

auto Logger::set_log_level(seed::SPD_LOG_LEVEL level) -> void
{
    switch (level)
    {
    case SPD_LOG_LEVEL::DEBUG:
        spdlog::set_level(spdlog::level::debug);
        break;
    case SPD_LOG_LEVEL::INFO:
        spdlog::set_level(spdlog::level::info);
        break;
    case SPD_LOG_LEVEL::WARNING:
        spdlog::set_level(spdlog::level::warn);
        break;
    case SPD_LOG_LEVEL::ERROR:
        spdlog::set_level(spdlog::level::err);
        break;
    }
}

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
