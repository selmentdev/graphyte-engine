// =================================================================================================
// Single instance support

#if defined(GX_LAUNCH_SINGLE_INSTANCE) && GRAPHYTE_PLATFORM_WINDOWS

namespace Graphyte::Launch::Impl
{
    static HANDLE g_SingleInstance_Mutex{ nullptr };

    static void SingleInstance_Acquire() noexcept
    {
        HANDLE const mutex = CreateMutexW(nullptr, TRUE, GX_WIN32_WIDEN(GX_LAUNCH_SINGLE_INSTANCE));

        if (mutex != nullptr)
        {
            DWORD const dwError = GetLastError();

            if (dwError == ERROR_ALREADY_EXISTS)
            {
                // Mutex was already created by other instance of current application
                Graphyte::App::Impl::g_IsFirstInstance = false;
                ReleaseMutex(mutex);
            }
            else if (dwError == ERROR_ACCESS_DENIED)
            {
                GX_ABORT("Failed to setup single instance lock: {}", GX_LAUNCH_SINGLE_INSTANCE);
            }

            g_SingleInstance_Mutex = mutex;
        }
    }

    static void SingleInstance_Release() noexcept
    {
        if (g_SingleInstance_Mutex != nullptr)
        {
            ReleaseMutex(g_SingleInstance_Mutex);
        }
    }
}

#else

namespace Graphyte::Launch::Impl
{
    constexpr void SingleInstance_Acquire() noexcept
    {
        // Empty implementation - removed by compiler
    }

    constexpr void SingleInstance_Release() noexcept
    {
        // Empty implementation - removed by compiler
    }
}

#endif