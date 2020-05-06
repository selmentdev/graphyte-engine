#include <GxBase/Threading/Thread.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#endif

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

static_assert(sizeof(unsigned) == sizeof(DWORD));
static_assert(alignof(unsigned) == alignof(DWORD));

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

    static void Win32SetThreadName(DWORD dwThreadID, LPCSTR szThreadName)
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

    static unsigned int __stdcall ThreadEntryPoint(void* context)
    {
        GX_ABORT_UNLESS(context != nullptr, "Invalid context provided to thread.");

        IRunnable* runnable = reinterpret_cast<IRunnable*>(context);

        unsigned int result{ 1 };

        __try
        {
            if (runnable->OnStart())
            {
                result = runnable->OnRun();
                runnable->OnStop();
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            result = ~unsigned int{};

            GX_ABORT("Exception occured on other thread");
        }

        _endthreadex(result);

        return result;
    }
}

#endif

#if GRAPHYTE_PLATFORM_POSIX
namespace Graphyte::Threading::Impl
{
    static int ConvertThreadPriority(ThreadPriority priority) noexcept
    {
        switch (priority)
        {
        case ThreadPriority::TimeCritical:
        case ThreadPriority::Highest:
            return 30;
        case ThreadPriority::AboveNormal:
            return 25;
        case ThreadPriority::Normal:
            return 15;
        case ThreadPriority::BelowNormal:
            return 5;
        case ThreadPriority::Lower:
            return 14;
        case ThreadPriority::Lowest:
            return 1;
            }

        GX_ASSERT(false);
        return 5;
    }

    static void* ThreadEntryPoint(void* context)
    {
        GX_ABORT_UNLESS(context != nullptr, "Invalid context provided to thread.");

        IRunnable* runnable = reinterpret_cast<IRunnable*>(context);

        unsigned int result{ 1 };

        if (runnable->OnStart())
        {
            result = runnable->OnRun();
            runnable->OnStop();
        }

        pthread_exit(reinterpret_cast<void*>(result));
        return reinterpret_cast<void*>(result);
    }
}
#endif

namespace Graphyte::Threading::Impl
{
    static void SetThreadName(
        [[maybe_unused]] ThreadHandle handle,
        [[maybe_unused]] ThreadId id,
        [[maybe_unused]] std::string_view name
    ) noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#if WDK_NTDDI_VERSION < NTDDI_WIN10_RS1
        if (IsDebuggerPresent() != FALSE)
        {
            std::string const sname{ name };
            Impl::Win32SetThreadName(id.Value, sname.c_str());
        }
#else
        std::wstring const wname = System::Impl::WidenString(name);

        HRESULT hr = SetThreadDescription(handle.Value, wname.c_str());

        GX_ABORT_UNLESS(SUCCEEDED(hr), "Failed to set thread {} name to `{}`, because `{}`",
            id.Value,
            name,
            Diagnostics::GetMessageFromHRESULT(hr)
        );
#endif
#elif GRAPHYTE_PLATFORM_POSIX
        std::string sname{ name };
        pthread_setname_np(handle.Value, sname.c_str());
#else
#error Not implemented
#endif
    }
}

namespace Graphyte::Threading
{
    Thread::Thread() noexcept = default;

    Thread::Thread(Thread&& other) noexcept
        : m_Handle{ std::exchange(other.m_Handle, {}) }
        , m_Id{ std::exchange(other.m_Id, {}) }
        , m_Runnable{ std::exchange(other.m_Runnable, {}) }
    {
    }

    Thread::~Thread() noexcept
    {
        if (m_Handle.IsValid())
        {
            Stop(true);
        }
    }

    Thread& Thread::operator=(Thread&& other) noexcept
    {
        m_Handle = std::exchange(other.m_Handle, {});
        m_Id = std::exchange(other.m_Id, {});
        m_Runnable = std::exchange(other.m_Runnable, {});

        return (*this);
    }

    bool Thread::Start(
        IRunnable* runnable,
        std::string_view name,
        [[maybe_unused]] size_t stacksize,
        ThreadPriority priority,
        ThreadAffinity affinity
    ) noexcept
    {
        GX_ABORT_UNLESS(!m_Handle.IsValid(), "Thread already created");

        m_Runnable = runnable;

        GX_ASSERT(runnable != nullptr);

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        m_Handle.Value = reinterpret_cast<HANDLE>(_beginthreadex(
            nullptr,
            static_cast<unsigned int>(stacksize),
            &Impl::ThreadEntryPoint,
            m_Runnable,
            STACK_SIZE_PARAM_IS_A_RESERVATION | CREATE_SUSPENDED,
            reinterpret_cast<unsigned int*>(&m_Id.Value)
        ));

        bool const success = m_Handle.IsValid();

#elif GRAPHYTE_PLATFORM_POSIX

        pthread_attr_t attrs{};
        pthread_attr_init(&attrs);
        pthread_attr_setscope(&attrs, PTHREAD_SCOPE_SYSTEM);
        int const result = pthread_create(&m_Handle.Value, &attrs, &Impl::ThreadEntryPoint, m_Runnable);
        pthread_attr_destroy(&attrs);

        bool const success = (m_Handle.IsValid() && result == 0);
#else
#error Not implemented
#endif

        if (success)
        {
            this->SetAffinity(affinity);
            this->SetPriority(priority);

            if (!name.empty())
            {
                Impl::SetThreadName(m_Handle, m_Id, name);
            }

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

            //
            // Thread was created suspended. Resume it.
            //

            ResumeThread(m_Handle.Value);
#endif

            return true;
        }
        else
        {
            GX_ABORT("Failed to start thread");
            m_Runnable = {};
            return false;
        }
    }

    bool Thread::Stop(bool wait) noexcept
    {
        GX_ABORT_UNLESS(m_Handle.IsValid(), "Thread not created");

        if (m_Runnable != nullptr)
        {
            m_Runnable->OnStop();
        }

        if (wait)
        {
            this->Join();
        }

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        CloseHandle(m_Handle.Value);
        m_Handle.Value = nullptr;
#elif GRAPHYTE_PLATFORM_POSIX
        m_Handle.Value = 0;
#endif


        return true;
    }

    bool Thread::Join() noexcept
    {
        GX_ABORT_UNLESS(m_Handle.IsValid(), "Thread not created");

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        WaitForSingleObject(m_Handle.Value, INFINITE);

#elif GRAPHYTE_PLATFORM_POSIX

        pthread_join(m_Handle.Value, nullptr);

#else
#error Not implemented
#endif

        return true;
    }

    void Thread::SetAffinity([[maybe_unused]] ThreadAffinity affinity) noexcept
    {
        GX_ABORT_UNLESS(m_Handle.IsValid(), "Thread not created");

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        SetThreadAffinityMask(m_Handle.Value, static_cast<DWORD_PTR>(affinity));

#elif GRAPHYTE_PLATFORM_POSIX

        // Not implemented

#else
#error Not implemented
#endif
    }

    void Thread::SetPriority(ThreadPriority priority) noexcept
    {
        GX_ABORT_UNLESS(m_Handle.IsValid(), "Thread not created");

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        SetThreadPriority(m_Handle.Value, Impl::ConvertThreadPriority(priority));

#elif GRAPHYTE_PLATFORM_POSIX

        sched_param sched{};
        int32_t policy = SCHED_RR;
        pthread_getschedparam(m_Handle.Value, &policy, &sched);
        sched.sched_priority = Impl::ConvertThreadPriority(priority);
        pthread_setschedparam(m_Handle.Value, policy, &sched);

#else
#error Not implemented
#endif
    }
}

