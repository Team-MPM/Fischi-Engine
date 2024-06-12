#pragma once

#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/bundled/core.h>

template <typename... Args>
using format_string_t = fmt::format_string<Args...>;

namespace FischiEngine
{
    class Log
    {
    public:
        enum class Level
        {
            None = 0,
            Trace,
            Debug,
            Info,
            Warn,
            Assert,
            Error,
            Fatal
        };
        
        static void LogMessage(std::string_view message, Level level);
        
        static void Init();

        template <typename... Params>
        static void Trace(format_string_t<Params...> message, Params&& ... params)
        {
            const std::string formatted_message = fmt::format(message, std::forward<Params>(params)...);
            LogMessage(formatted_message, Level::Trace);
        }

        template <typename ...Params>
        static void Debug(format_string_t<Params...> message, Params &&... params)
        {
            const std::string formatted_message = fmt::format(message, std::forward<Params>(params)...);
            LogMessage(formatted_message, Level::Debug);
        }
        
        template <typename ... Params>
        static void Info(format_string_t<Params...> message, Params &&... params)
        {
            const std::string formatted_message = fmt::format(message, std::forward<Params>(params)...);
            LogMessage(formatted_message, Level::Info);
        }
        
        template <typename ... Params>
        static void Warn(format_string_t<Params...> message, Params &&... params)
        {
            const std::string formatted_message = fmt::format(message, std::forward<Params>(params)...);
            LogMessage(formatted_message, Level::Warn);
        }
        
        template <typename ... Params>
        static void Error(format_string_t<Params...> message, Params &&... params)
        {
            const std::string formatted_message = fmt::format(message, std::forward<Params>(params)...);
            LogMessage(formatted_message, Level::Error);
        }
        
        template <typename ... Params>
        static void Fatal(format_string_t<Params...> message, Params &&... params)
        {
            const std::string formatted_message = fmt::format(message, std::forward<Params>(params)...);
            LogMessage(formatted_message, Level::Fatal);
        }
    };
}
