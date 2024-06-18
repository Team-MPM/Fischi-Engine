#pragma once

#include <filesystem>
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/bundled/core.h>

#define oldNone None
#undef None

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

        static void Init(std::filesystem::path logPath);

        template <typename... Params>
        static void Trace(format_string_t<Params...> message, Params&& ... params)
        {
            const std::string formatted_message = fmt::format(message, std::forward<Params>(params)...);
            LogMessage(formatted_message, Level::Trace);
        }

        template <typename ...Params>
        static void Debug(format_string_t<Params...> message, Params &&... params)
        {
            #ifdef FISCHI_DEBUG
            const std::string formatted_message = fmt::format(message, std::forward<Params>(params)...);
            LogMessage(formatted_message, Level::Debug);
            #endif
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

template <typename T, typename = void>
struct has_to_string : std::false_type {};

template <typename T>
struct has_to_string<T, std::void_t<decltype(std::declval<T>().ToString())>> : std::true_type {};

namespace fmt {
    template<typename T>
    struct formatter<T, std::enable_if_t<has_to_string<T>::value>> {
        template<typename ParseContext>
        constexpr auto parse(ParseContext& ctx) {
            return ctx.begin();
        }

        template<typename FormatContext>
        auto format(const T& value, FormatContext& ctx) {
            return format_to(ctx.out(), "{}", value.ToString());
        }
    };
}

#define None oldNone