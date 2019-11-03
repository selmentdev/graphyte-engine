#include "Base.pch.hxx"
#include <Graphyte/Threading/Impl.Windows/Windows.Thread.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Application.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>

#if defined(ENABLE_NSIGHT_PROFILER)
#include <nvToolsExt.h>
#endif

namespace Graphyte::Threading
{
    namespace Impl
    {
        inline int ConvertThreadPriority(
            ThreadPriority priority
        ) noexcept
        {
            switch (priority)
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

            GX_ASSERT(false);
            return THREAD_PRIORITY_NORMAL;
        }
    }

    DWORD CALLBACK Thread::ThreadEntryPoint(
        LPVOID context
    ) noexcept
    {
        GX_ASSERT(context != nullptr);
        Thread* thread = static_cast<Thread*>(context);

        DWORD result{};

#if !(defined(__MINGW32__) || defined(__MINGW64__))
        __try
#endif
        {
            result = thread->Run();
        }

#if !(defined(__MINGW32__) || defined(__MINGW64__))
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            result = ~DWORD{};
            Graphyte::Application::RequestExit(true);
        }
#endif

        return result;
    }

    void Thread::SetThreadName(
        [[maybe_unused]] ThreadId thread_id,
        [[maybe_unused]] const char* thread_name
    ) noexcept
    {
        if (IsDebuggerPresent() != FALSE)
        {
            // We are using debug exception to set thread name in debugger:
            // http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx

#if !(defined(__MINGW32__) || defined(__MINGW64__))
            static const constexpr uint32_t EXCEPTION_CODE = 0x406D1388;

            struct THREADNAME_INFO
            {
                uint32_t dw_type;
                const char* sz_name;
                uint32_t dw_thread_id;
                uint32_t dw_flags;
            };

            ::Sleep(10);
            THREADNAME_INFO payload{
                .dw_type = 0x1000,
                .sz_name = thread_name,
                .dw_thread_id = thread_id,
                .dw_flags = 0,
            };

            __try
            {
                RaiseException(EXCEPTION_CODE, 0, sizeof(THREADNAME_INFO) / sizeof(ULONG_PTR), (ULONG_PTR*)&payload);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                ;
            }
        }
#endif

#if defined(ENABLE_NSIGHT_PROFILER)
        nvtxNameOsThreadA(thread_id, thread_name);
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

            SetThreadDescription(
                m_Handle,
                Graphyte::System::Impl::ConvertString(thread_name).c_str()
            );

            Thread::SetThreadName(
                m_ThreadId,
                thread_name
            );

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
