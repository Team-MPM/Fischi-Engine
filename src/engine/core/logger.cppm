module;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

export module core:logger;

import :service;

export class Logger final : public IService {
public:
    Logger() {
        const auto pattern = "[%Y-%m-%d %H:%M:%S.%e] [%l] %v";
        m_Console = spdlog::stdout_color_mt("console");
        m_Console->set_pattern(pattern);
        m_LatestLogFile = spdlog::basic_logger_mt("latest_log", "latest.log");
        m_Console->set_pattern(pattern);
    }

    template<typename... Args>
    void log(fmt::format_string<Args...> msg, const spdlog::level::level_enum level, Args&&... args) {
        m_Console->log(level, fmt::format(msg, std::forward<Args>(args)...));
    }

    template<typename... Args>
    void trace(const fmt::format_string<Args...> msg, Args&&... args) {
        log(msg, spdlog::level::trace, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(const fmt::format_string<Args...> msg, Args&&... args) {
        log(msg, spdlog::level::debug, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(const fmt::format_string<Args...> msg, Args&&... args) {
        log(msg, spdlog::level::info, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(const fmt::format_string<Args...> msg, Args&&... args) {
        log(msg, spdlog::level::warn, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(const fmt::format_string<Args...> msg, Args&&... args) {
        log(msg, spdlog::level::err, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void fatal(const fmt::format_string<Args...> msg, Args&&... args) {
        log(msg, spdlog::level::critical, std::forward<Args>(args)...);
    }
private:
    std::shared_ptr<spdlog::logger> m_Console;
    std::shared_ptr<spdlog::logger> m_LatestLogFile;
};

export class Math : public IService {
public:
    using Dependencies = std::tuple<Logger>;
    explicit Math(Logger* logger) : logger_(logger) {
        logger_->info("Math service created.");
    }

    int add(int a, int b) const {
        logger_->info("Performing addition.");
        return a + b;
    }
private:
    Logger* logger_;
};