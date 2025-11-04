#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Core {

    std::shared_ptr<spdlog::logger> Logger::m_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::m_AppLogger;

    void Logger::init() {
        spdlog::set_pattern("%^[%T] %n %v%$");

        m_CoreLogger = spdlog::stdout_color_mt("Core");
        m_CoreLogger->set_level(spdlog::level::trace);

        m_AppLogger = spdlog::stdout_color_mt("APP");
        m_AppLogger->set_level(spdlog::level::trace);
    }

}
