#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Threading/Runnable.hxx>
#include <Graphyte/Threading/Thread.hxx>

namespace Graphyte::Threading
{
    using ThreadHandle = pthread_t;
    using ThreadId = pthread_t;

    class BASE_API LinuxThread final
    {
    private:
        pthread_t m_Handle;
        ThreadAffinity m_Affinity;
        IRunnable* m_Runnable;

    private:
        static void* ThreadEntryPoint(void* context);

    public:
        LinuxThread() noexcept;
        ~LinuxThread() noexcept;

    public:
        bool Start(
            IRunnable* runnable,
            const char* thread_name,
            size_t stack_size = 0,
            ThreadPriority priority = ThreadPriority::Normal,
            ThreadAffinity affinity = ThreadAffinity::All
        ) noexcept;

        bool Stop(bool wait) noexcept;

        void Join() noexcept;

    private:
        uint32_t Run() noexcept;

    public:
        ThreadId GetThreadId() const noexcept
        {
            return m_Handle;
        }

        ThreadHandle GetHandle() const noexcept
        {
            return m_Handle;
        }

        ThreadAffinity GetAffinityMask() const noexcept
        {
            return m_Affinity;
        }

    public:
        static void Yield() noexcept;
        static void Sleep(uint32_t timeout) noexcept;
        static ThreadId CurrentThreadId() noexcept;
    };

    using Thread = LinuxThread;
}
