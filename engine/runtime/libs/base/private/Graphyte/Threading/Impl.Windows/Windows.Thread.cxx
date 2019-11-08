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
    namespace Impl
    {
        unsigned __stdcall ThreadEntryPoint(void* context)
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
                result = ~DWORD{};

                GX_ABORT("Exception occured on other thread");
            }

            _endthreadex(result);

            return result;
        }
    }

    Thread::Thread() noexcept = default;

    Thread::Thread(Thread&& other) noexcept
        : m_Handle{ std::exchange(other.m_Handle, {}) }
        , m_Id{ std::exchange(other.m_Id, {}) }
        , m_Runnable{ std::exchange(other.m_Runnable, {}) }
    {
    }

    Thread& Thread::operator=(Thread&& other) noexcept
    {
        m_Handle = std::exchange(other.m_Handle, {});
        m_Id = std::exchange(other.m_Id, {});
        m_Runnable = std::exchange(other.m_Runnable, {});

        return (*this);
    }

    Thread::~Thread() noexcept
    {
        if (m_Handle.Value != nullptr)
        {
            Stop(true);
        }
    }

    bool Thread::Start(
        IRunnable* runnable,
        std::string_view name,
        size_t stacksize,
        ThreadPriority priority,
        ThreadAffinity affinity
    ) noexcept
    {
        static_assert(sizeof(unsigned) == sizeof(DWORD));
        static_assert(alignof(unsigned) == alignof(DWORD));

        m_Runnable = runnable;

        GX_ASSERT(runnable != nullptr);

        m_Handle.Value = reinterpret_cast<HANDLE>(_beginthreadex(
            nullptr,
            static_cast<unsigned int>(stacksize),
            Impl::ThreadEntryPoint,
            m_Runnable,
            STACK_SIZE_PARAM_IS_A_RESERVATION | CREATE_SUSPENDED,
            reinterpret_cast<unsigned int*>(&m_Id.Value)
        ));

        if (m_Handle.Value != nullptr)
        {
            this->SetAffinity(affinity);
            this->SetPriority(priority);

            if (!name.empty())
            {
                std::wstring const wname = System::Impl::ConvertString(name);
                SetThreadDescription(m_Handle.Value, wname.c_str());

            }

            //
            // Thread was created suspended. Resume it.
            //

            ResumeThread(m_Handle.Value);

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
        GX_ABORT_UNLESS(m_Handle.Value != nullptr, "Thread not created");
    
        if (m_Runnable != nullptr)
        {
            m_Runnable->OnStop();
        }

        if (wait)
        {
            WaitForSingleObject(m_Handle.Value, INFINITE);
        }

        CloseHandle(m_Handle.Value);

        m_Handle.Value = nullptr;

        return true;
    }

    bool Thread::Join() noexcept
    {
        GX_ABORT_UNLESS(m_Handle.Value != nullptr, "Thread not created");
        WaitForSingleObject(m_Handle.Value, INFINITE);

        return true;
    }

    void Thread::SetAffinity(ThreadAffinity affinity) noexcept
    {
        SetThreadAffinityMask(m_Handle.Value, static_cast<DWORD_PTR>(affinity));
    }

    void Thread::SetPriority(ThreadPriority priority) noexcept
    {
        SetThreadPriority(m_Handle.Value, Impl::ConvertThreadPriority(priority));
    }
}

#if false
namespace Graphyte::Threading
{
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
        HRESULT hr = SetThreadDescription(thread.m_Handle.Value, wname.c_str());

        GX_ABORT_UNLESS(SUCCEEDED(hr), "Failed to set thread {} name to `{}`, because `{}`",
            thread.m_ThreadId.Value,
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
        if (m_Handle.Value != nullptr)
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

        m_Handle.Value = CreateThread(
            nullptr,
            stack_size,
            ThreadEntryPoint,
            this,
            STACK_SIZE_PARAM_IS_A_RESERVATION | CREATE_SUSPENDED,
            &m_ThreadId.Value
        );

        if (m_Handle.Value != nullptr)
        {
            if (SetThreadAffinityMask(m_Handle.Value, static_cast<DWORD_PTR>(affinity)) == FALSE)
            {
                GX_LOG(LogPlatform, Error, "Failed to set thread affinity (thread: `{}`, affinity: {:016x}\n",
                    thread_name != nullptr ? thread_name : "<unknown>",
                    static_cast<std::underlying_type_t<ThreadAffinity>>(affinity)
                );
            }

            SetThreadPriority(m_Handle.Value, Impl::ConvertThreadPriority(priority));

            SetThreadName(*this, thread_name);

            ResumeThread(m_Handle.Value);
        }
        else
        {
            m_Runnable = nullptr;
        }

        return m_Handle.Value != nullptr;
    }

    bool Thread::Stop(
        bool wait
    ) noexcept
    {
        GX_ASSERT(m_Handle.Value != nullptr);

        if (m_Runnable != nullptr)
        {
            m_Runnable->OnStop();
        }

        if (wait)
        {
            WaitForSingleObject(m_Handle.Value, INFINITE);
        }

        CloseHandle(m_Handle.Value);

        m_Handle.Value = nullptr;

        return true;
    }

    void Thread::Join() noexcept
    {
        GX_ASSERT(m_Handle.Value != nullptr);

        WaitForSingleObject(m_Handle.Value, INFINITE);
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
}
#endif
