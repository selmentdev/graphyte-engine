#pragma once
#include <GxBase/Threading.hxx>
#include <GxBase/Threading/Runnable.hxx>

namespace Graphyte::Threading
{
    class BASE_API Thread final
    {
    private:
        ThreadHandle m_Handle{};
        ThreadId m_Id{};
        IRunnable* m_Runnable{};

    public:
        Thread() noexcept;

        Thread(const Thread&) = delete;

        Thread(Thread&& other) noexcept;

        ~Thread() noexcept;

        Thread& operator=(const Thread&) = delete;

        Thread& operator=(Thread&& other) noexcept;

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
        /// @brief Starts thread with specified runnable.
        ///
        /// @param runnable  Provides object to run in thread.
        /// @param name      Provides name of newly created thread.
        /// @param stacksize Provides hint for initial size of thread stack.
        /// @param priority  Provides initial thread priorirty.
        /// @param affinity  Provides initial thread affinity.
        ///
        /// @return The value indicating whether thread started successfully.
        bool Start(
            IRunnable* runnable,
            std::string_view name,
            size_t stacksize        = 0,
            ThreadPriority priority = ThreadPriority::Normal,
            ThreadAffinity affinity = ThreadAffinity::All) noexcept;

        bool Stop(bool wait) noexcept;

        bool Join() noexcept;

        void SetAffinity(ThreadAffinity affinity) noexcept;

        void SetPriority(ThreadPriority priority) noexcept;
    };
}
