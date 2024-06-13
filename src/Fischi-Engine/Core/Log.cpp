#include "Log.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace FischiEngine
{
    static std::shared_ptr<spdlog::logger> s_Logger;
    
    void Log::Init(std::filesystem::path logPath)
    {
        const auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_level(spdlog::level::trace);

        const auto errorLogSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::filesystem::path(logPath).append("error.log").string());
        errorLogSink->set_level(spdlog::level::warn);

        const auto debugLogSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::filesystem::path(logPath).append("debug.log").string());
        debugLogSink->set_level(spdlog::level::trace);
        
        s_Logger = std::make_shared<spdlog::logger>("FischiEngine");
        s_Logger->set_level(spdlog::level::trace);
        
        // "[ColorBegin] [ISO_TIME] [THREAD_ID] [LOGGER] [LEVEL] [ColorEnd] [Message]"
        consoleSink->set_pattern("[%T] [%t] [%n] %^[%l]%$ %v");
        // " [ISO_DATE ISO_TIME] [THREAD_ID] [LOGGER] [LEVEL] [Message]"
        errorLogSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%n] %^[%l]%$ %v");
        debugLogSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%t] [%n] %^[%l]%$ %v");
        
        s_Logger->sinks().push_back(consoleSink);
        s_Logger->sinks().push_back(errorLogSink);
        s_Logger->sinks().push_back(debugLogSink);
    }
    
    void Log::LogMessage(std::string_view message, Level level)
    {
        switch (level) {
        case Level::None:
            break;
        case Level::Trace:
            s_Logger->trace(message);
            break;
        case Level::Debug:
            s_Logger->debug(message);
            break;
        case Level::Info:
            s_Logger->info(message);
            break;
        case Level::Warn:
            s_Logger->warn(message);
            break;
        case Level::Assert:
            s_Logger->debug(message);
            break;
        case Level::Error:
            s_Logger->error(message);
            break;
        case Level::Fatal:
            s_Logger->critical(message);
            break;
        }
    }
}
