#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Status.hxx>


// =================================================================================================
//
// Diagnostics initialization and finalization.
//

namespace Graphyte::Diagnostics
{
    /// @brief Initializes diagnostics subsystem.
    BASE_API void Initialize() noexcept;

    /// @brief Shuts down diagnostics subsystem.
    BASE_API void Finalize() noexcept;
}


// =================================================================================================
//
// Common functions and error reporting.
//

namespace Graphyte::Diagnostics
{
    /// @brief Determines whether debugger is attached to current process.
    ///
    /// @return \c true when debugger is attached, \c false otherwise.
    [[nodiscard]] BASE_API bool IsDebuggerAttached() noexcept;

    /// @brief Exits from current process with provided exit code.
    ///
    /// @param exitCode Provides exit code.
    [[noreturn]] BASE_API void Exit(int32_t exitCode) noexcept;

    /// @brief Performs fast fail exit from current process.
    [[noreturn]] BASE_API void FailFast() noexcept;

    /// @brief Represents possible error reporting modes.
    enum struct ErrorReporting
    {
        Interactive,
        Unattended,
    };

    /// @brief Gets current error reporting mode.
    [[nodiscard]] BASE_API ErrorReporting GetErrorReporting() noexcept;

    /// @brief Sets current error reporting mode.
    ///
    /// @param value Provides new reporting mode.
    BASE_API void SetErrorReporting(
        ErrorReporting value) noexcept;
}


// =================================================================================================
//
// Assert handling.
//

namespace Graphyte::Diagnostics
{
    /// @brief Determines whether source code is executing assert right now.
    [[nodiscard]] BASE_API bool IsAsserting() noexcept;

    /// @brief Handles assertion request.
    ///
    /// @param condition Provides string expression of failing condition.
    /// @param function  Provides name of function.
    /// @param file      Provides name of file.
    /// @param line      Provides line number.
    /// @param format    Provides formatter string.
    /// @param args      Provides list of format args.
    ///
    /// @return \c true when assert should break into debugger, \c false otherwise.
    [[nodiscard]] BASE_API bool OnAssertArgs(
        bool& always_ignore,
        std::string_view condition,
        std::string_view function,
        std::string_view file,
        std::uint_least32_t line,
        std::string_view format,
        fmt::format_args args) noexcept;

    /// @brief Handles assertion request.
    ///
    /// @tparam TArgs Provides list of types of format args.
    ///
    /// @param condition Provides string expression of failing condition.
    /// @param function  Provides name of function.
    /// @param file      Provides name of file.
    /// @param line      Provides line number.
    /// @param format    Provides formatter string.
    /// @param args      Provides list of format args.
    ///
    /// @return \c true when assert should break into debugger, \c false otherwise.
    template <typename... TArgs>
    [[nodiscard]] bool OnAssert(
        bool& always_ignore,
        std::string_view condition,
        std::string_view function,
        std::string_view file,
        std::uint_least32_t line,
        std::string_view format,
        const TArgs&... args) noexcept
    {
        return Diagnostics::OnAssertArgs(
            always_ignore,
            condition,
            function,
            file,
            line,
            format,
            fmt::make_format_args(args...));
    }
}

#if GRAPHYTE_CONFIG_DO_ASSERT

#define GX_ASSERT(condition) \
    { \
        if (!(condition)) \
        { \
            static bool GX_UNIQUE_NAME(_gx_always_ignore_this_assert) = false; \
            if (::Graphyte::Diagnostics::OnAssert(GX_UNIQUE_NAME(_gx_always_ignore_this_assert), #condition, __FUNCTION__, __FILE__, __LINE__, {})) \
            { \
                GX_DEBUG_BREAK(); \
            } \
        } \
    }

#define GX_ASSERTF(condition, format, ...) \
    { \
        if (!(condition)) \
        { \
            static bool GX_UNIQUE_NAME(_gx_always_ignore_this_assert) = false; \
            if (::Graphyte::Diagnostics::OnAssert(GX_UNIQUE_NAME(_gx_always_ignore_this_assert), #condition, __FUNCTION__, __FILE__, __LINE__, format, ##__VA_ARGS__)) \
            { \
                GX_DEBUG_BREAK(); \
            } \
        } \
    }

#else

#define GX_ASSERT(condition) \
    { \
        ((void)0); \
        GX_COMPILER_ASSUME(condition); \
    }

#define GX_ASSERTF(condition, format, ...) \
    { \
        ((void)0); \
        GX_COMPILER_ASSUME(condition); \
    }

#endif


// =================================================================================================
//
// Abort handling.
//

namespace Graphyte::Diagnostics
{
    /// @brief Determines whether source code is executing abort right now.
    [[nodiscard]] BASE_API bool IsAborting() noexcept;

    /// @brief Handles abort request.
    ///
    /// @param condition Provides string expression of failing condition.
    /// @param function  Provides name of function.
    /// @param file      Provides name of file.
    /// @param line      Provides line number.
    /// @param format    Provides formatter string.
    /// @param args      Provides list of format args.
    ///
    /// @return \c true when assert should continue, \c false otherwise.
    [[nodiscard]] BASE_API bool OnAbortArgs(
        std::string_view condition,
        std::string_view function,
        std::string_view file,
        std::uint_least32_t line,
        std::string_view format,
        fmt::format_args args) noexcept;

    /// @brief Handles abort request.
    ///
    /// @tparam TArgs Provides list of types of format args.
    ///
    /// @param condition Provides string expression of failing condition.
    /// @param function  Provides name of function.
    /// @param file      Provides name of file.
    /// @param line      Provides line number.
    /// @param format    Provides formatter string.
    /// @param args      Provides list of format args.
    ///
    /// @return \c true when assert should continue, \c false otherwise.
    template <typename... TArgs>
    [[nodiscard]] bool OnAbort(
        std::string_view condition,
        std::string_view function,
        std::string_view file,
        std::uint_least32_t line,
        std::string_view format,
        const TArgs&... args) noexcept
    {
        return Diagnostics::OnAbortArgs(
            condition,
            function,
            file,
            line,
            format,
            fmt::make_format_args(args...));
    }
}


/// @brief Stops application execution.
///
/// @param format Provides format string with message to be output to log.
/// @param ...    Provides format arguments.
#define GX_ABORT(format, ...) \
    if (::Graphyte::Diagnostics::OnAbort({}, __FUNCTION__, __FILE__, __LINE__, format, ##__VA_ARGS__)) \
    { \
        GX_DEBUG_BREAK(); \
    }

/// @brief Conditionally stops application execution.
///
/// @param condition Provides stop condition to be tested.
/// @param format    Provides format string with message to be output to log.
/// @param ...       Provides format arguments.
#define GX_ABORT_UNLESS(condition, format, ...) \
    if (!(condition)) \
    { \
        if (::Graphyte::Diagnostics::OnAbort(#condition, __FUNCTION__, __FILE__, __LINE__, format, ##__VA_ARGS__)) \
        { \
            GX_DEBUG_BREAK(); \
        } \
    }


// =================================================================================================
//
// Crash handling.
//

namespace Graphyte::Diagnostics
{
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

    /// @brief Handles crash request.
    ///
    /// @param reason    Provides failure reason.
    /// @param context   Provides processor context.
    /// @param exception Provides exception information.
    BASE_API void OnCrash(
        EXCEPTION_POINTERS* exception) noexcept;

#endif

#if GRAPHYTE_PLATFORM_LINUX

    /// @brief Handles crash request.
    ///
    /// @param reason      Provides failure reason.
    /// @param signal_info Provides catched signal info.
    /// @param context     Provides processor context.
    BASE_API void OnCrash(
        ucontext_t* context,
        siginfo_t* signal_info) noexcept;

#endif
}


// =================================================================================================
//
// Loaded native modules.
//

namespace Graphyte::Diagnostics
{
    /// @brief Gets list of modules.
    ///
    /// @param modules Returns list of loaded modules.
    [[nodiscard]] BASE_API std::vector<std::string> GetModules() noexcept;
}


// =================================================================================================
//
// Stack trace access.
//

namespace Graphyte::Diagnostics
{
    enum struct StackFrameFormat
    {
        Function = 1 << 0,
        Address  = 1 << 1,
        Module   = 1 << 2,
        Location = 1 << 3,
        Standard = Function | Address,
        Extended = Function | Address | Module | Location,
    };

    GX_ENUM_CLASS_FLAGS(StackFrameFormat);

    struct StackFrame final
    {
        std::string Function;
        std::string Module;
        std::string File;
        std::uint64_t Address;
        std::uint_least32_t Line;
    };

    /// @brief Converts stack frame to string.
    ///
    /// @param frame  Provides stack frame.
    /// @param format Provides output format.
    ///
    /// @return The string representation of stack frame.
    [[nodiscard]] BASE_API std::string ToString(
        const StackFrame& frame,
        StackFrameFormat format = StackFrameFormat::Standard) noexcept;

    /// @brief Converts stack trace to string.
    ///
    /// @param frame  Provides stack trace.
    /// @param format Provides output format.
    ///
    /// @return The string representation of stack trace.
    [[nodiscard]] BASE_API std::string ToString(
        std::span<const StackFrame> frames,
        StackFrameFormat format = StackFrameFormat::Standard) noexcept;


    /// @brief Gets stack trace for current thread.
    ///
    /// @param frames Returns captured stack trace frames.
    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames) noexcept;

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

    /// @brief Gets stack trace for current thread.
    ///
    /// @param frames  Returns captured stack trace frames.
    /// @param context Provides captured thread context.
    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames,
        const CONTEXT& context) noexcept;

#endif

#if GRAPHYTE_PLATFORM_LINUX

    /// @brief Gets stack trace for current thread.
    ///
    /// @param frames  Returns captured stack trace frames.
    /// @param context Provides captured thread context.
    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames,
        ucontext_t* context) noexcept;

#endif
}


// =================================================================================================
//
// Logging.
//

namespace Graphyte::Diagnostics
{
    enum struct LogLevel
    {
        /// Logging Disabled.
        None = 0,

        /// Fatals in retail build; not compiled out
        Fatal,

        /// Errors in retail build; not compiled out
        Error,

        /// Warnings in retail build; not compiled out
        Warn,

        /// Additional info, compiled in, may be compiled out
        Info,

        /// Debug trace; removed from compilation on retail build
        Trace,
    };

    namespace Impl
    {
        BASE_API extern LogLevel GLogLevel;

        [[nodiscard]] constexpr bool IsCompiled(LogLevel level) noexcept
        {
            switch (level)
            {
                case LogLevel::None:
                case LogLevel::Trace:
                case LogLevel::Info:
                    return false;
                case LogLevel::Warn:
                case LogLevel::Error:
                case LogLevel::Fatal:
                    return true;
            }
        }
    }

    /// @brief Logs message to logger.
    ///
    /// @param level    Provides log level.
    /// @param category Provides name of category.
    /// @param format   Provides format string.
    /// @param args     Provides format args.
    ///
    /// @return \c true when successful, \c false otherwise.
    [[nodiscard]] BASE_API bool LogDispatchArgs(
        LogLevel level,
        std::string_view category,
        std::string_view format,
        fmt::format_args args) noexcept;

    /// @brief Logs message to logger.
    ///
    /// @param level    Provides log level.
    /// @param category Provides name of category.
    /// @param format   Provides format string.
    /// @param args     Provides format args.
    ///
    /// @return \c true when successful, \c false otherwise.
    template <typename... TArgs>
    bool LogDispatch(
        LogLevel level,
        std::string_view category,
        std::string_view format,
        const TArgs&... args) noexcept
    {
        return Diagnostics::LogDispatchArgs(
            level,
            category,
            format,
            fmt::make_format_args(args...));
    }
}

namespace Graphyte::Diagnostics
{
    struct LogCategoryBase
    {
        const char* Name;
        LogLevel Level;

        constexpr LogCategoryBase(const char* name, LogLevel level) noexcept
            : Name{ name }
            , Level{ level }
        {
        }

        [[nodiscard]] constexpr bool CanDispatch(LogLevel level) const noexcept
        {
            return level <= Level;
        }
    };

    template <LogLevel RuntimeValue, LogLevel CompileValue>
    struct LogCategory : public LogCategoryBase
    {
        enum
        {
            RuntimeLevel = static_cast<int>(RuntimeValue)
        };
        enum
        {
            CompileLevel = static_cast<int>(CompileValue)
        };

        constexpr LogCategory(const char* name) noexcept
            : LogCategoryBase(name, RuntimeValue)
        {
        }
    };
}


#define GX_DECLARE_LOG_CATEGORY(name, runtime, compile) \
    struct LogCategory##name : public Graphyte::Diagnostics::LogCategory< \
                                   Graphyte::Diagnostics::LogLevel::runtime, \
                                   Graphyte::Diagnostics::LogLevel::compile> \
    { \
        inline LogCategory##name() noexcept \
            : LogCategory(#name) \
        { \
        } \
    }; \
    extern LogCategory##name name;

#define GX_DEFINE_LOG_CATEGORY(name) \
    LogCategory##name name { }

#define GRAPHYTE_DIAGNOSTICS_IMPL_GX_LOG(category, level, format, ...) \
    { \
        if constexpr (level <= static_cast<::Graphyte::Diagnostics::LogLevel>(LogCategory##category::CompileLevel)) \
        { \
            if (category.CanDispatch(level)) \
            { \
                ::Graphyte::Diagnostics::LogDispatch(level, category.Name, format, ##__VA_ARGS__); \
            } \
        } \
    }


/// @brief Outputs formatted log message.
///
/// @param category Provides log category.
/// @param format   Provides format string.
/// @param ...      Provides list of arguments to format.
#define GX_LOG_FATAL(category, format, ...) \
    { \
        if (::Graphyte::Diagnostics::OnAbort("", __func__, __FILE__, __LINE__, format, ##__VA_ARGS__)) \
        { \
            GX_DEBUG_BREAK(); \
        } \
    }

#define GX_LOG_ERROR(category, format, ...) \
    GRAPHYTE_DIAGNOSTICS_IMPL_GX_LOG(category, ::Graphyte::Diagnostics::LogLevel::Error, format, ##__VA_ARGS__)

#define GX_LOG_WARN(category, format, ...) \
    GRAPHYTE_DIAGNOSTICS_IMPL_GX_LOG(category, ::Graphyte::Diagnostics::LogLevel::Warn, format, ##__VA_ARGS__)

#define GX_LOG_INFO(category, format, ...) \
    GRAPHYTE_DIAGNOSTICS_IMPL_GX_LOG(category, ::Graphyte::Diagnostics::LogLevel::Info, format, ##__VA_ARGS__)

#define GX_LOG_TRACE(category, format, ...) \
    GRAPHYTE_DIAGNOSTICS_IMPL_GX_LOG(category, ::Graphyte::Diagnostics::LogLevel::Trace, format, ##__VA_ARGS__)


// =================================================================================================
//
// Common system status and diagnostic messages.
//

namespace Graphyte::Diagnostics
{
    /// @brief Gets status code from errno.
    ///
    /// @param error Provides errno value.
    ///
    /// @return The matching status code.
    BASE_API Status GetStatusFromErrno(
        int error) noexcept;

    /// @brief Gets message from errno.
    ///
    /// @param error Provides errno value.
    ///
    /// @return The matching error message.
    [[nodiscard]] BASE_API std::string GetMessageFromErrno(
        int error) noexcept;

    /// @brief Gets message from status code.
    ///
    /// @param error Provides status code value.
    ///
    /// @return The matching message.
    [[nodiscard]] BASE_API std::string_view GetMessageFromStatus(
        Status status) noexcept;

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

    /// @brief Gets status from WinAPI Error Code.
    ///
    /// @param error Provides WinAPI Error Code.
    ///
    /// @return The matching status code.
    BASE_API Status GetStatusFromSystemError(
        DWORD error) noexcept;

    /// @brief Gets status from last WinAPI error code.
    ///
    /// @return The matching status code.
    BASE_API Status GetStatusFromSystemError() noexcept;

    /// @brief Gets message from WinAPI exception code.
    ///
    /// @param code Provides exception code.
    ///
    /// @return The matching message.
    [[nodiscard]] BASE_API std::string_view GeMessageFromtExceptionCode(
        DWORD code) noexcept;

    /// @brief Gets messge from WinAPI Error Code.
    ///
    /// @param error Provides WinAPI Error Code.
    ///
    /// @return The matching message.
    [[nodiscard]] BASE_API std::string GetMessageFromSystemError(
        DWORD error) noexcept;

    /// @brief Gets message from last WinAPI error code.
    ///
    /// @return The matching message.
    [[nodiscard]] BASE_API std::string GetMessageFromSystemError() noexcept;

    /// @brief Gets message from WinAPI HRESULT.
    ///
    /// @param hr Provides HRESULT value.
    ///
    /// @return The matching message.
    [[nodiscard]] BASE_API std::string_view GetMessageFromHRESULT(
        HRESULT hr) noexcept;

#endif

#if GRAPHYTE_PLATFORM_POSIX

    [[nodiscard]] BASE_API std::string_view GetSignalName(
        const siginfo_t* signal_info) noexcept;

    [[nodiscard]] BASE_API Status GetStatusFromSiginfo(
        const siginfo_t* signal_info) noexcept;

#endif

}


// =================================================================================================
//
// Recursion watcher.
//

namespace Graphyte::Diagnostics
{
    class RecursionWatcher final
    {
    private:
        size_t& m_Counter;

    public:
        RecursionWatcher() = delete;

        RecursionWatcher(const RecursionWatcher&) = delete;

        RecursionWatcher& operator=(const RecursionWatcher&) = delete;

    public:
        RecursionWatcher(size_t& counter) noexcept
            : m_Counter{ counter }
        {
            ++m_Counter;
        }

        ~RecursionWatcher() noexcept
        {
            --m_Counter;
        }
    };
}


#if GRAPHYTE_CONFIG_DO_ASSERT

#define GX_RECURSION() \
    static size_t GX_UNIQUE_NAME(gx_recursion_watch_count){}; \
    GX_ASSERTF(GX_UNIQUE_NAME(gx_recursion_watch_count) == 0, "Recursion detected"); \
    const ::Graphyte::Diagnostics::RecursionWatcher GX_UNIQUE_NAME(gx_recursion_watch) { GX_UNIQUE_NAME(gx_recursion_watch_count) }

#define GX_RECURSIONF(format, ...) \
    static size_t GX_UNIQUE_NAME(gx_recursion_watch_count){}; \
    GX_ASSERTF(GX_UNIQUE_NAME(gx_recursion_watch_count) == 0, format, __VA_ARGS__); \
    const ::Graphyte::Diagnostics::RecursionWatcher GX_UNIQUE_NAME(gx_recursion_watch) { GX_UNIQUE_NAME(gx_recursion_watch_count) }

#else

#define GX_RECURSION()     ((void)0)
#define GX_RECURSIONF(...) ((void)0)

#endif


// =================================================================================================
//
// Unimplemented functionality reporting.
//

#define GX_ASSERT_NOT_IMPLEMENTED() GX_ASSERTF(false, "Not Implemented: {}", __FUNCTION__)


// =================================================================================================
//
// Asserting single call.
//

#if GRAPHYTE_CONFIG_DO_ASSERT

#define GX_ASSERT_SINGLE_CALL_MSG(message, ...) \
    { \
        static bool GX_UNIQUE_NAME(gx_single_call_scope_mark) = false; \
        GX_ASSERTF(GX_UNIQUE_NAME(gx_single_call_scope_mark) == false, message, ##__VA_ARGS__); \
        (void)GX_UNIQUE_NAME(gx_single_call_scope_mark); \
        GX_UNIQUE_NAME(gx_single_call_scope_mark) = true; \
    }

#define GX_ASSERT_SINGLE_CALL() GX_ASSERT_SINGLE_CALL_MSG(" called more than once")

#else

#define GX_ASSERT_SINGLE_CALL_MSG(message)
#define GX_ASSERT_SINGLE_CALL()

#endif


// =================================================================================================
//
// std::format formatters
//


template <>
struct fmt::formatter<Graphyte::Status> : fmt::formatter<std::string_view>
{
    template <typename FormatContext>
    auto format(Graphyte::Status value, FormatContext& context)
    {
        auto const result = Graphyte::Diagnostics::GetMessageFromStatus(value);
        return fmt::formatter<std::string_view>::format(result, context);
    }
};
