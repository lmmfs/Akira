#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Akira {
    class Logger
    {
        private:
            static std::shared_ptr<spdlog::logger> m_CoreLogger;
            static std::shared_ptr<spdlog::logger> m_AppLogger;
        public:
            static void init();

            inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return m_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& getAppLogger() { return m_AppLogger; }
    };

    //Core Logger Macros
    #define CORE_TRACE(...) ::Akira::Logger::getCoreLogger()->trace(__VA_ARGS__)
    #define CORE_INFO(...) ::Akira::Logger::getCoreLogger()->info(__VA_ARGS__)
    #define CORE_WARN(...) ::Akira::Logger::getCoreLogger()->warn(__VA_ARGS__)
    #define CORE_ERROR(...) ::Akira::Logger::getCoreLogger()->error(__VA_ARGS__)

    //App Logger Macros
    #define APP_TRACE(...) ::Akira::Logger::getAppLogger()->trace(__VA_ARGS__)
    #define APP_INFO(...) ::Akira::Logger::getAppLogger()->info(__VA_ARGS__)
    #define APP_WARN(...) ::Akira::Logger::getAppLogger()->warn(__VA_ARGS__)
    #define APP_ERROR(...) ::Akira::Logger::getAppLogger()->error(__VA_ARGS__)
}
