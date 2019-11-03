#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Delegate.hxx>

namespace Graphyte::Threading
{
    enum class TimerStatus : uint32_t
    {
        Pending,
        Active,
        Paused,
        Executing,
    };

    struct TimerHandle
    {
        uint64_t Handle;

        bool IsValid() const noexcept
        {
            return Handle != 0;
        }
        void Invalidate() noexcept
        {
            Handle = 0;
        }

        bool operator == (const TimerHandle& other) const noexcept
        {
            return Handle == other.Handle;
        }
        bool operator != (const TimerHandle& other) const noexcept
        {
            return Handle != other.Handle;
        }
    };

    using TimerDelegate = Delegate<void(void)>;

    struct TimerDesc final
    {
        TimerDelegate Callback;
        TimerHandle Handle;
        double Expire;
        float Rate;
        TimerStatus Status;
        bool Looped;
        bool RequireCallback;

        bool operator < (const TimerDesc& other) const noexcept
        {
            return this->Expire < other.Expire;
        }

        void Clear()
        {
            Callback.Unbind();
            Handle.Invalidate();
        }
    };

    class TimerDispatcher final
    {
    public:
        TimerDispatcher() noexcept;
        ~TimerDispatcher() noexcept;

    public:
        void Tick(float delta_time) noexcept;

        /// \brief  Sets timer with delegate.
        ///
        /// \param  handle      A handle of dispatched timer.
        /// \param  callback    A callback to call.
        /// \param  rate        A rate on which timer callback will be fired.
        /// \param  loop        A value indicating whether timer works in loop
        bool SetTimer(TimerHandle& handle, TimerDelegate callback, float rate, bool loop = false) noexcept;

        /**
         *  \brief  Sets timer
         *
         *  \param  handle      A handle of dispatched timer.
         *  \param  rate        A rate of which event callback will be fired.
         *  \param  loop        A value indicating whether timer works in loop.
         */
        bool SetTimer(TimerHandle& handle, float rate, bool loop) noexcept;
        bool SetTimerNextTick(TimerDelegate callback) noexcept;

    public:
        bool PauseTimer(TimerHandle handle) noexcept;
        bool ResumeTimer(TimerHandle handle) noexcept;
        bool KillTimer(TimerHandle& handle) noexcept;
        float GetTimerRate(TimerHandle handle) noexcept;
        float GetTimerElapsed(TimerHandle handle) noexcept;
        float GetTimerRemaining(TimerHandle handle) noexcept;
        bool WasCalledThisFrame(TimerHandle handle) noexcept;
        bool IsTimerActive(TimerHandle handle) noexcept;
        bool IsTimerPaused(TimerHandle handle) noexcept;
        bool IsTimerPending(TimerHandle handle) noexcept;
        bool Exists(TimerHandle handle) noexcept;

    private:
        std::vector<TimerDesc> m_ActiveTimers;
        std::vector<TimerDesc> m_PausedTimers;
        std::vector<TimerDesc> m_PendingTimers;

    private:
        TimerDesc* FindTimer(TimerHandle handle) noexcept;
    };
}
