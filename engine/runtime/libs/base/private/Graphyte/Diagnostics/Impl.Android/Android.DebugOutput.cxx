#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    constexpr android_LogPriority ToAndroidLogPriority(LogLevel level) noexcept
    {
        switch (level)
        {
        case LogLevel::None:
            return ANDROID_LOG_DEFAULT;
        case LogLevel::Fatal:
            return ANDROID_LOG_FATAL;
        case LogLevel::Error:
            return ANDROID_LOG_ERROR;
        case LogLevel::Warn:
            return ANDROID_LOG_WARN;
        case LogLevel::Info:
            return ANDROID_LOG_INFO;
        case LogLevel::Trace:
            return ANDROID_LOG_DEBUG;
        }
    }

    void DebugOutput(
        LogLevel level,
        const char* text
    ) noexcept
    {
        __android_log_write(
            ToAndroidLogPriority(level),
            "graphyte",
            text
        );
    }
}
