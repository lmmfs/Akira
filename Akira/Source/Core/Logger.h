#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Core {
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
    #define CORE_TRACE(...) ::Core::Logger::getCoreLogger()->trace(__VA_ARGS__)
    #define CORE_INFO(...) ::Core::Logger::getCoreLogger()->info(__VA_ARGS__)
    #define CORE_WARN(...) ::Core::Logger::getCoreLogger()->warn(__VA_ARGS__)
    #define CORE_ERROR(...) ::Core::Logger::getCoreLogger()->error(__VA_ARGS__)

    //App Logger Macros
    #define APP_TRACE(...) ::Core::Logger::getAppLogger()->trace(__VA_ARGS__)
    #define APP_INFO(...) ::Core::Logger::getAppLogger()->info(__VA_ARGS__)
    #define APP_WARN(...) ::Core::Logger::getAppLogger()->warn(__VA_ARGS__)
    #define APP_ERROR(...) ::Core::Logger::getAppLogger()->error(__VA_ARGS__)
}
