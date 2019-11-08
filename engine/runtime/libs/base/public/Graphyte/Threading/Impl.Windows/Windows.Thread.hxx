#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Threading.hxx>
#include <Graphyte/Threading/Runnable.hxx>
#include <Graphyte/Threading/Thread.hxx>

namespace Graphyte::Threading
{
    class BASE_API Thread final
    {
    private:
        ThreadHandle m_Handle;
        ThreadId m_Id;
        IRunnable* m_Runnable;

    public:
        Thread() noexcept;
        Thread(const Thread&) = delete;
        Thread(Thread&&) noexcept;
        Thread& operator=(const Thread&) = delete;
        Thread& operator=(Thread&&) noexcept;
        ~Thread() noexcept;

    public:
        ThreadHandle GetHandle() const noexcept
        {
            return m_Handle;
        }

        ThreadId GetId() const noexcept
        {
            return m_Id;
        }

    public:
        bool Start(
            IRunnable* runnable,
            std::string_view name,
            size_t stacksize = 0,
            ThreadPriority priority = ThreadPriority::Normal,
            ThreadAffinity affinity = ThreadAffinity::All
        ) noexcept;

        bool Stop(bool wait) noexcept;

        bool Join() noexcept;

        void SetAffinity(ThreadAffinity affinity) noexcept;

        void SetPriority(ThreadPriority priority) noexcept;
    };
}

#if false
namespace Graphyte::Threading
{
    class BASE_API Thread final
    {
    private:
        ThreadHandle m_Handle;
        ThreadId m_ThreadId;
        ThreadAffinity m_Affinity;
        IRunnable* m_Runnable;

    private:
        static DWORD CALLBACK ThreadEntryPoint(
            LPVOID context
        ) noexcept;

        static void SetThreadName(
            const Thread& thread,
            const char* name
        ) noexcept;

    public:
        Thread() noexcept;
        Thread(const Thread&) = delete;
        Thread(Thread&&) = default;
        Thread& operator=(const Thread&) = delete;
        Thread& operator=(Thread&&) = default;
        ~Thread() noexcept;

    public:
        bool Start(
            IRunnable* runnable,
            const char* thread_name,
            size_t stack_size = 0,
            ThreadPriority priority = ThreadPriority::Normal,
            ThreadAffinity affinity = ThreadAffinity::All
        ) noexcept;

        bool Stop(
            bool wait
        ) noexcept;

        void Join() noexcept;

    private:
        uint32_t Run() noexcept;

    public:
        ThreadId GetThreadId() const noexcept
        {
            return m_ThreadId;
        }

        ThreadHandle GetHandle() const noexcept
        {
            return m_Handle;
        }

        ThreadAffinity GetAffinity() const noexcept
        {
            return m_Affinity;
        }

    public:
        static void Yield() noexcept;

        static void Sleep(
            uint32_t timeout
        ) noexcept;

        static ThreadId CurrentThreadId() noexcept;
    };
}

#endif // false
