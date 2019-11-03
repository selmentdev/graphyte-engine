#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Threading/Runnable.hxx>
#include <Graphyte/Threading/Thread.hxx>

namespace Graphyte::Threading
{
    using ThreadHandle = pthread_t;
    using ThreadId = pthread_t;

    class BASE_API AndroidThread final
    {
    private:
        pthread_t m_Handle;
        uint64_t m_AffinityMask;
        IRunnable* m_Runnable;

    private:
        static void* ThreadEntryPoint(void* context);

    public:
        AndroidThread() noexcept;
        ~AndroidThread() noexcept;

    public:
        bool Start(
            IRunnable* runnable,
            const char* thread_name,
            size_t stack_size = 0,
            ThreadPriority priority = ThreadPriority::Normal,
            uint64_t affinity_mask = 0) noexcept;
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

        uint64_t GetAffinityMask() const noexcept
        {
            return m_AffinityMask;
        }

    public:
        static void Yield() noexcept;
        static void Sleep(uint32_t timeout) noexcept;
        static ThreadId CurrentThreadId() noexcept;
    };

    using Thread = AndroidThread;
}
