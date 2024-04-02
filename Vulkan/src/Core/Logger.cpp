#include "Precompiled.h"

#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace lve
{
    std::shared_ptr<spdlog::logger> Logger::sLogger = nullptr;

    void Logger::Init()
    {
        spdlog::set_pattern("%^[%T] %l: %v%$");
        sLogger = spdlog::stdout_color_mt("Default Logger");
        sLogger->set_level(spdlog::level::trace);
    }
}