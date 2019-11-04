#include "Base.pch.hxx"
#include <Graphyte/Threading/Impl.Windows/Windows.Thread.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Application.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>

namespace Graphyte::Threading::Impl
{
    constexpr int ConvertThreadPriority(ThreadPriority value) noexcept
    {
        switch (value)
        {
        case ThreadPriority::TimeCritical:
            return THREAD_PRIORITY_TIME_CRITICAL;
        case ThreadPriority::Highest:
            return THREAD_PRIORITY_HIGHEST;
        case ThreadPriority::AboveNormal:
            return THREAD_PRIORITY_ABOVE_NORMAL;
        case ThreadPriority::Normal:
            return THREAD_PRIORITY_NORMAL;
        case ThreadPriority::BelowNormal:
            return THREAD_PRIORITY_BELOW_NORMAL;
        case ThreadPriority::Lower:
            return THREAD_PRIORITY_NORMAL - 1;
        case ThreadPriority::Lowest:
            return THREAD_PRIORITY_LOWEST;
        }

        return THREAD_PRIORITY_NORMAL;
    }

#if WDK_NTDDI_VERSION < NTDDI_WIN10_RS1
    //
    // More info:
    //  https://en.wikipedia.org/wiki/Windows_10_version_history
    //  https://docs.microsoft.com/pl-pl/visualstudio/debugger/how-to-set-a-thread-name-in-native-code?view=vs-2019
    //

    constexpr const DWORD MS_VC_EXCEPTION = 0x406D1388;

    typedef struct alignas(8) tagTHREADNAME_INFO
    {
        DWORD dwType; // Must be 0x1000.
        LPCSTR szName; // Pointer to name (in user addr space).
        DWORD dwThreadID; // Thread ID (-1=caller thread).
        DWORD dwFlags; // Reserved for future use, must be zero.
    } THREADNAME_INFO;

    void Win32SetThreadName(DWORD dwThreadID, LPCSTR szThreadName)
    {
        THREADNAME_INFO info{
            .dwType = 0x1000,
            .szName = szThreadName,
            .dwThreadID = dwThreadID,
            .dwFlags = 0,
        };

#pragma warning(push)
#pragma warning(disable: 6320 6322)
        __try
        {
            RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
#pragma warning(pop)
    }
#endif
}

namespace Graphyte::Threading
{
    DWORD CALLBACK Thread::ThreadEntryPoint(
        LPVOID context
    ) noexcept
    {
        GX_ASSERT(context != nullptr);
        Thread* thread = static_cast<Thread*>(context);

        DWORD result{};

        __try
        {
            result = thread->Run();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            result = ~DWORD{};
            Graphyte::Application::RequestExit(true);
        }

        return result;
    }

    void Thread::SetThreadName(
        const Thread& thread,
        const char* name
    ) noexcept
    {
        GX_ABORT_UNLESS(name != nullptr, "What's the point of naming thread with empty name?");

#if WDK_NTDDI_VERSION < NTDDI_WIN10_RS1
        if (IsDebuggerPresent() != FALSE)
        {
            Impl::Win32SetThreadName(thread.m_ThreadId, name);
        }
#else
        auto const wname = System::Impl::ConvertString(name);
        HRESULT hr = SetThreadDescription(thread.m_Handle, wname.c_str());

        GX_ABORT_UNLESS(SUCCEEDED(hr), "Failed to set thread {} name to `{}`, because `{}`",
            thread.m_ThreadId,
            name,
            Diagnostics::GetMessageFromHRESULT(hr)
        );
#endif
    }

    Thread::Thread() noexcept
        : m_Handle{}
        , m_ThreadId{}
        , m_Affinity{ ThreadAffinity::All }
        , m_Runnable{}
    {
    }

    Thread::~Thread() noexcept
    {
        if (m_Handle != nullptr)
        {
            Stop(true);
        }
    }

    bool Thread::Start(
        IRunnable* runnable,
        const char* thread_name,
        size_t stack_size,
        ThreadPriority priority,
        ThreadAffinity affinity
    ) noexcept
    {
        GX_ASSERT(runnable != nullptr);
        GX_ASSERT(thread_name != nullptr);

        m_Runnable = runnable;
        m_Affinity = affinity;

        m_Handle = CreateThread(
            nullptr,
            stack_size,
            ThreadEntryPoint,
            this,
            STACK_SIZE_PARAM_IS_A_RESERVATION | CREATE_SUSPENDED,
            (DWORD*)&m_ThreadId
        );

        if (m_Handle != nullptr)
        {
            if (SetThreadAffinityMask(m_Handle, static_cast<DWORD_PTR>(affinity)) == FALSE)
            {
                GX_LOG(LogPlatform, Error, "Failed to set thread affinity (thread: `{}`, affinity: {:016x}\n",
                    thread_name != nullptr ? thread_name : "<unknown>",
                    static_cast<std::underlying_type_t<ThreadAffinity>>(affinity)
                );
            }

            SetThreadPriority(m_Handle, Impl::ConvertThreadPriority(priority));

            SetThreadName(*this, thread_name);

            ResumeThread(m_Handle);
        }
        else
        {
            m_Runnable = nullptr;
        }

        return m_Handle != nullptr;
    }

    bool Thread::Stop(
        bool wait
    ) noexcept
    {
        GX_ASSERT(m_Handle != nullptr);

        if (m_Runnable != nullptr)
        {
            m_Runnable->OnStop();
        }

        if (wait)
        {
            WaitForSingleObject(m_Handle, INFINITE);
        }

        CloseHandle(m_Handle);

        m_Handle = nullptr;

        return true;
    }

    void Thread::Join() noexcept
    {
        GX_ASSERT(m_Handle != nullptr);

        WaitForSingleObject(m_Handle, INFINITE);
    }

    uint32_t Thread::Run() noexcept
    {
        GX_ASSERT(m_Runnable != nullptr);

        uint32_t result = 1;

        if (m_Runnable->OnStart())
        {
            result = m_Runnable->OnRun();
            m_Runnable->OnExit();
        }

        return result;
    }

    void Thread::Yield() noexcept
    {
        ::Sleep(0);
    }

    void Thread::Sleep(
        uint32_t timeout
    ) noexcept
    {
        // Explicitely call Windows API function

        ::Sleep(timeout);
    }

    ThreadId Thread::CurrentThreadId() noexcept
    {
        return GetCurrentThreadId();
    }
}
