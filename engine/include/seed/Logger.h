#pragma once

#include <spdlog/spdlog.h>
#include <string>

namespace seed {
enum class SPD_LOG_LEVEL {
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
};

class Logger {
public:
    static auto set_log_level(SPD_LOG_LEVEL level) -> void;

    template<typename... Args>
    static void log_info(fmt::format_string<Args...> fmt_str, Args&&... args)
    {
        std::string message = fmt::format(fmt_str, std::forward<Args>(args)...);
        spdlog::info("[SEED] {}", message);
    }

    template<typename... Args>
    static void log_debug(fmt::format_string<Args...> fmt_str, Args&&... args)
    {
        std::string message = fmt::format(fmt_str, std::forward<Args>(args)...);
        spdlog::debug("[SEED] {}", message);
    }

    template<typename... Args>
    static void log_warn(fmt::format_string<Args...> fmt_str, Args&&... args)
    {
        std::string message = fmt::format(fmt_str, std::forward<Args>(args)...);
        spdlog::warn("[SEED] {}", message);
    }

    template<typename... Args>
    static void log_error(fmt::format_string<Args...> fmt_str, Args&&... args)
    {
        std::string message = fmt::format(fmt_str, std::forward<Args>(args)...);
        spdlog::error("[SEED] {}", message);
    }
};
} // namespace seed

// TODO: if def Debug or Release
#define SEED_LOG_INFO(...) seed::Logger::log_info(__VA_ARGS__)
#define SEED_LOG_WARN(...) seed::Logger::log_warn(__VA_ARGS__)
#define SEED_LOG_DEBUG(...) seed::Logger::log_debug(__VA_ARGS__)
#define SEED_LOG_ERROR(...) seed::Logger::log_error(__VA_ARGS__)