#pragma once

namespace seed {
class Logger {
public:
    static auto log_info(const char* msg) -> void;
    static auto log_warn(const char* msg) -> void;
    static auto log_debug(const char* msg) -> void;
    static auto log_error(const char* msg) -> void;
};
} // namespace seed

// TODO: if def Debug or Release
#define SEED_LOG_INFO(msg) seed::Logger::log_info(msg)
#define SEED_LOG_DEBUG(msg) seed::Logger::log_debug(msg)
#define SEED_LOG_WARN(msg) seed::Logger::log_warn(msg)
#define SEED_LOG_ERROR(msg) seed::Logger::log_error(msg)
