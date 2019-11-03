#include "Base.pch.hxx"
#include <Graphyte/Threading/Impl.Linux/Linux.Thread.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::Threading
{
    namespace
    {
        inline int ConvertThreadPriority(
            ThreadPriority priority
        ) noexcept
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
    }

    void* LinuxThread::ThreadEntryPoint(
        void* context
    )
    {
        GX_ASSERT(context != nullptr);
        LinuxThread* thread = static_cast<LinuxThread*>(context);

        uint32_t const result = thread->Run();

        pthread_exit(reinterpret_cast<void*>(result));
    }

    LinuxThread::LinuxThread() noexcept
        : m_Handle{}
        , m_Affinity{ ThreadAffinity::All }
        , m_Runnable{}
    {
    }

    LinuxThread::~LinuxThread() noexcept
    {
        if (m_Handle != 0)
        {
            Stop(true);
        }
    }

    bool LinuxThread::Start(
        IRunnable* runnable,
        const char* thread_name,
        size_t stack_size,
        ThreadPriority priority,
        ThreadAffinity affinity
    ) noexcept
    {
        (void)thread_name;
        (void)stack_size;
        GX_ASSERT(runnable != nullptr);

        m_Runnable = runnable;
        m_Affinity = affinity;

        pthread_attr_t attr{};
        pthread_attr_init(&attr);
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

        int const result = pthread_create(&m_Handle, &attr, &Thread::ThreadEntryPoint, this);
        pthread_attr_destroy(&attr);

        if (m_Handle != 0 && result == 0)
        {
            // TODO: Implement thread affinity setting

            {
                struct sched_param sched { };
                int32_t policy = SCHED_RR;
                pthread_getschedparam(m_Handle, &policy, &sched);
                sched.sched_priority = ConvertThreadPriority(priority);
                pthread_setschedparam(m_Handle, policy, &sched);
            }
            //SetThreadName(m_Handle, thread_name);
            //ResumeThread(m_Handle);
        }
        else
        {
            m_Runnable = nullptr;
        }

        return m_Handle != 0;
    }

    bool LinuxThread::Stop(
        bool wait
    ) noexcept
    {
        GX_ASSERT(m_Handle != 0);

        if (m_Runnable != nullptr)
        {
            m_Runnable->OnStop();
        }

        if (wait)
        {
            pthread_join(m_Handle, nullptr);
        }

        m_Handle = 0;
        return true;
    }

    void LinuxThread::Join() noexcept
    {
        GX_ASSERT(m_Handle != 0);

        pthread_join(m_Handle, nullptr);
    }

    uint32_t LinuxThread::Run() noexcept
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

    void LinuxThread::Yield() noexcept
    {
        sched_yield();
    }

    void LinuxThread::Sleep(
        uint32_t timeout
    ) noexcept
    {
        usleep(timeout * 1000);
    }

    ThreadId LinuxThread::CurrentThreadId() noexcept
    {
        return pthread_self();
    }
}
