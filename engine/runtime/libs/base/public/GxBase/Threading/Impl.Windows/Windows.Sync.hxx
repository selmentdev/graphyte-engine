#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Threading/Sync.hxx>

namespace Graphyte::Threading
{
    class Barrier final
    {
        Barrier(const Barrier&) = delete;
        Barrier& operator= (const Barrier&) = delete;

    private:
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
        mutable SYNCHRONIZATION_BARRIER m_Barrier;
#else
        mutable HANDLE m_Event;
        mutable HANDLE m_EventSync;
        mutable volatile LONG m_Count;
        mutable LONG m_InitialCount;
#endif

    public:
        Barrier(uint32_t count) noexcept
        {
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
            InitializeSynchronizationBarrier(&m_Barrier, static_cast<LONG>(count), 4000);
#else
            m_Event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
            m_EventSync = CreateEventW(nullptr, TRUE, FALSE, nullptr);
            m_Count = static_cast<DWORD>(count);
            m_InitialCount = static_cast<LONG>(count);
#endif
        }
        ~Barrier() noexcept
        {
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
            DeleteSynchronizationBarrier(&m_Barrier);
#else
            CloseHandle(m_Event);
            CloseHandle(m_EventSync);
#endif
        }

    public:
        bool Wait() noexcept
        {
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
            return EnterSynchronizationBarrier(&m_Barrier, 0) != FALSE;
#else
            LONG last = InterlockedDecrement(&m_Count);

            if (last == 0)
            {
                ResetEvent(m_EventSync);
                SetEvent(m_Event);
            }

            WaitForSingleObject(m_Event, INFINITE);

            LONG last_next = InterlockedIncrement(&m_Count);

            if (last_next == m_InitialCount)
            {
                SetEvent(m_EventSync);
            }
            else
            {
                SetEvent(m_Event);
                WaitForSingleObject(m_EventSync, INFINITE);
            }

            return last == 0;
#endif
        }
    };

    class CriticalSection final
    {
        friend class ConditionVariable;
        CriticalSection(const CriticalSection&) = delete;
        CriticalSection& operator= (const CriticalSection&) = delete;

    private:
        CRITICAL_SECTION m_CriticalSection;

    public:
        CriticalSection() noexcept
        {
            InitializeCriticalSection(&m_CriticalSection);
        }

        ~CriticalSection() noexcept
        {
            DeleteCriticalSection(&m_CriticalSection);
        }

    public:
        void Enter() noexcept
        {
            EnterCriticalSection(&m_CriticalSection);
        }

        bool TryEnter() noexcept
        {
            return TryEnterCriticalSection(&m_CriticalSection) != FALSE;
        }

        void Leave() noexcept
        {
            LeaveCriticalSection(&m_CriticalSection);
        }
    };

    class ConditionVariable final
    {
        ConditionVariable(const ConditionVariable&) = delete;
        ConditionVariable& operator= (const ConditionVariable&) = delete;
    private:
        CONDITION_VARIABLE m_ConditionVariable;

    public:
        ConditionVariable() noexcept
        {
            InitializeConditionVariable(&m_ConditionVariable);
        }

        ~ConditionVariable() noexcept
        {
        }

    public:
        bool Wait(CriticalSection& lock) noexcept
        {
            return SleepConditionVariableCS(&m_ConditionVariable, &lock.m_CriticalSection, INFINITE) != FALSE;
        }

        bool Wait(CriticalSection& lock, uint32_t timeout) noexcept
        {
            return SleepConditionVariableCS(&m_ConditionVariable, &lock.m_CriticalSection, timeout) != FALSE;
        }

        void NotifyAll() noexcept
        {
            WakeAllConditionVariable(&m_ConditionVariable);
        }

        void Notify() noexcept
        {
            WakeConditionVariable(&m_ConditionVariable);
        }
    };

    class Semaphore final
    {
        Semaphore(const Semaphore&) = delete;
        Semaphore& operator= (const Semaphore&) = delete;
    private:
        HANDLE m_Handle;

    public:
        Semaphore(int32_t count) noexcept
            : m_Handle{}
        {
            m_Handle = CreateSemaphoreW(nullptr, static_cast<LONG>(count), 0x7fffffff, nullptr);
        }

        ~Semaphore() noexcept
        {
            CloseHandle(m_Handle);
        }

    public:
        void Wait() noexcept
        {
            WaitForSingleObject(m_Handle, INFINITE);
        }

        bool Wait(uint32_t timeout) noexcept
        {
            return WaitForSingleObject(m_Handle, timeout) != WAIT_TIMEOUT;
        }

        bool TryWait() noexcept
        {
            return WaitForSingleObject(m_Handle, 0) != WAIT_TIMEOUT;
        }

        void Release() noexcept
        {
            ReleaseSemaphore(m_Handle, 1, nullptr);
        }

        void Release(int32_t count) noexcept
        {
            GX_ASSERT(count >= 0);
            ReleaseSemaphore(m_Handle, count, nullptr);
        }
    };

    class ReaderWriterLock final
    {
        ReaderWriterLock(const ReaderWriterLock&) = delete;
        ReaderWriterLock& operator= (const ReaderWriterLock&) = delete;
    private:
        SRWLOCK m_Lock;

    public:
        ReaderWriterLock() noexcept
        {
            InitializeSRWLock(&m_Lock);
        }

        ~ReaderWriterLock() noexcept
        {
        }

    public:
        void EnterWriter() noexcept
        {
            AcquireSRWLockExclusive(&m_Lock);
        }

        void EnterReader() noexcept
        {
            AcquireSRWLockShared(&m_Lock);
        }

        bool TryEnterWriter() noexcept
        {
            return TryAcquireSRWLockExclusive(&m_Lock) != FALSE;
        }

        bool TryEnterReader() noexcept
        {
            return TryAcquireSRWLockShared(&m_Lock) != FALSE;
        }

        _Requires_lock_held_(&this->m_Lock)
        void LeaveWriter() noexcept
        {
            ReleaseSRWLockExclusive(&m_Lock);
        }

        void LeaveReader() noexcept
        {
            ReleaseSRWLockShared(&m_Lock);
        }
    };

    class Event final
    {
        Event(const Event&) = delete;
        Event& operator= (const Event&) = delete;
    private:
        HANDLE m_Handle;

    public:
        Event(bool state, EventType event_type) noexcept
            : m_Handle{}
        {
            m_Handle = CreateEventW(
                nullptr,
                (event_type == EventType::ManualReset) ? TRUE : FALSE,
                state ? TRUE : FALSE,
                nullptr
            );
        }

        ~Event() noexcept
        {
            CloseHandle(m_Handle);
        }

    public:
        void Set() noexcept
        {
            SetEvent(m_Handle);
        }

        void Reset() noexcept
        {
            ResetEvent(m_Handle);
        }

        bool Wait() noexcept
        {
            return WaitForSingleObject(m_Handle, INFINITE) != WAIT_TIMEOUT;
        }

        bool Wait(uint32_t timeout) noexcept
        {
            return WaitForSingleObject(m_Handle, timeout) != WAIT_TIMEOUT;
        }

        bool Test() noexcept
        {
            return WaitForSingleObject(m_Handle, 0) != WAIT_TIMEOUT;
        }
    };
}
