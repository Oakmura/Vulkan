#pragma once

#include <spdlog/spdlog.h>

class Logger final
{
public:
    Logger() = delete;
    ~Logger() = delete;
    Logger(const Logger& rhs) = delete;
    Logger& operator=(const Logger& rhs) = delete;

    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return sLogger; }

private:
    static std::shared_ptr<spdlog::logger> sLogger;
};

#ifndef DIST
#define LOG_TRACE(...) Logger::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::GetLogger()->error(__VA_ARGS__)
#else
#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#endif // DIST