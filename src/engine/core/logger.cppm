module;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

export module core:logger;
import :math;

export void initialize_logger() {
    auto console = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(console);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
}

export void log_info(const std::string& message) {
    spdlog::info(message);
}

export void log_error(const std::string& message) {
    spdlog::error(message);
}