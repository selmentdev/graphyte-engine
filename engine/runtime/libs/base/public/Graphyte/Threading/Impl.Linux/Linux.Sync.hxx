#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Threading/Sync.hxx>
#include <Graphyte/Platform/Impl.Posix/Posix.Types.hxx>

namespace Graphyte::Threading
{
    class LinuxBarrier final
    {
        LinuxBarrier(const LinuxBarrier&) = delete;
        LinuxBarrier& operator= (const LinuxBarrier&) = delete;
    private:
        mutable pthread_barrier_t m_Barrier;

    public:
        LinuxBarrier(uint32_t count) noexcept
        {
            pthread_barrier_init(&m_Barrier, nullptr, count);
        }

        ~LinuxBarrier() noexcept
        {
            pthread_barrier_destroy(&m_Barrier);
        }

    public:
        bool Wait() noexcept
        {
            return pthread_barrier_wait(&m_Barrier) != 0;
        }
    };

    class LinuxCriticalSection final
    {
        friend class LinuxConditionVariable;
        LinuxCriticalSection(const LinuxCriticalSection&) = delete;
        LinuxCriticalSection& operator= (const LinuxCriticalSection&) = delete;
    private:
        pthread_mutex_t m_CriticalSection;

    public:
        LinuxCriticalSection() noexcept
        {
            pthread_mutexattr_t attr{};
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
            pthread_mutex_init(&m_CriticalSection, &attr);
            pthread_mutexattr_destroy(&attr);
        }

        ~LinuxCriticalSection() noexcept
        {
            pthread_mutex_destroy(&m_CriticalSection);
        }

    public:
        void Enter() noexcept
        {
            pthread_mutex_lock(&m_CriticalSection);
        }

        bool TryEnter() noexcept
        {
            return pthread_mutex_trylock(&m_CriticalSection) == 0;
        }

        void Leave() noexcept
        {
            pthread_mutex_unlock(&m_CriticalSection);
        }
    };

    class LinuxConditionVariable final
    {
        LinuxConditionVariable(const LinuxConditionVariable&) = delete;
        LinuxConditionVariable& operator= (const LinuxConditionVariable&) = delete;
    private:
        pthread_cond_t m_ConditionVariable;

    public:
        LinuxConditionVariable() noexcept
        {
            pthread_cond_init(&m_ConditionVariable, nullptr);
        }

        ~LinuxConditionVariable() noexcept
        {
            pthread_cond_destroy(&m_ConditionVariable);
        }

    public:
        bool Wait(LinuxCriticalSection& lock) noexcept
        {
            return pthread_cond_wait(&m_ConditionVariable, &lock.m_CriticalSection) == 0;
        }

        bool Wait(LinuxCriticalSection& lock, uint32_t timeout) noexcept
        {
            auto ts = Platform::TypeConverter<timespec>::ConvertMilliseconds(timeout);

            return pthread_cond_timedwait(&m_ConditionVariable, &lock.m_CriticalSection, &ts);
        }

        void NotifyAll() noexcept
        {
            pthread_cond_broadcast(&m_ConditionVariable);
        }

        void Notify() noexcept
        {
            pthread_cond_signal(&m_ConditionVariable);
        }
    };

    class LinuxSemaphore final
    {
        LinuxSemaphore(const LinuxSemaphore&) = delete;
        LinuxSemaphore& operator= (const LinuxSemaphore&) = delete;
    private:
        sem_t m_Handle;

    public:
        LinuxSemaphore(int32_t count) noexcept
            : m_Handle{}
        {
            sem_init(&m_Handle, 0, static_cast<unsigned int>(count));
        }

        ~LinuxSemaphore() noexcept
        {
            sem_destroy(&m_Handle);
        }

    public:
        void Wait() noexcept
        {
            sem_wait(&m_Handle);
        }

        bool Wait(uint32_t timeout) noexcept
        {
            auto ts = Platform::TypeConverter<timespec>::ConvertMilliseconds(timeout);
            return sem_timedwait(&m_Handle, &ts) == 0;
        }

        bool TryWait() noexcept
        {
            return sem_trywait(&m_Handle) == 0;
        }

        void Release() noexcept
        {
            sem_post(&m_Handle);
        }

        void Release(int32_t count) noexcept
        {
            GX_ASSERT(count >= 0);

            const auto limit = static_cast<size_t>(count);

            for (size_t i = 0; i < limit; ++i)
            {
                sem_post(&m_Handle);
            }
        }
    };

    class LinuxReaderWriterLock final
    {
        LinuxReaderWriterLock(const LinuxReaderWriterLock&) = delete;
        LinuxReaderWriterLock& operator= (const LinuxReaderWriterLock&) = delete;
    private:
        pthread_rwlock_t m_Lock;

    public:
        LinuxReaderWriterLock() noexcept
        {
            pthread_rwlock_init(&m_Lock, nullptr);
        }

        ~LinuxReaderWriterLock() noexcept
        {
        }

    public:
        void EnterWriter() noexcept
        {
            pthread_rwlock_wrlock(&m_Lock);
        }

        void EnterReader() noexcept
        {
            pthread_rwlock_rdlock(&m_Lock);
        }

        bool TryEnterWriter() noexcept
        {
            return pthread_rwlock_trywrlock(&m_Lock) == 0;
        }

        bool TryEnterReader() noexcept
        {
            return pthread_rwlock_tryrdlock(&m_Lock) == 0;
        }

        void LeaveWriter() noexcept
        {
            pthread_rwlock_unlock(&m_Lock);
        }

        void LeaveReader() noexcept
        {
            pthread_rwlock_unlock(&m_Lock);
        }
    };

    class LinuxEvent final
    {
        LinuxEvent(const LinuxEvent&) = delete;
        LinuxEvent& operator= (const LinuxEvent&) = delete;
    private:
        LinuxCriticalSection m_CriticalSection;
        LinuxConditionVariable m_ConditionVariable;
        EventType m_EventType;
        bool m_State;

    public:
        LinuxEvent(bool state, EventType event_type) noexcept
            : m_CriticalSection{}
            , m_ConditionVariable{}
            , m_EventType{ event_type }
            , m_State{ state }
        {
        }
        ~LinuxEvent() noexcept
        {
        }

    public:
        void Set() noexcept
        {
            ScopedLock<LinuxCriticalSection> lock{ m_CriticalSection };

            m_State = true;

            if (m_EventType == EventType::AutoReset)
            {
                m_ConditionVariable.Notify();
            }
            else
            {
                m_ConditionVariable.NotifyAll();
            }
        }

        void Reset() noexcept
        {
            ScopedLock<LinuxCriticalSection> lock{ m_CriticalSection };

            m_State = false;
        }

        bool Wait() noexcept
        {
            while (m_State == false)
            {
                m_ConditionVariable.Wait(m_CriticalSection);
            }

            if (m_EventType == EventType::AutoReset)
            {
                m_State = false;
            }

            return true;
        }

        bool Wait(uint32_t timeout) noexcept
        {
            ScopedLock<LinuxCriticalSection> lock{ m_CriticalSection };

            if (m_State == false)
            {
                if (m_ConditionVariable.Wait(m_CriticalSection, timeout) == false)
                {
                    return false;
                }
            }

            if (m_EventType == EventType::AutoReset)
            {
                m_State = false;
            }

            return true;
        }

        bool Test() noexcept
        {
            ScopedLock<LinuxCriticalSection> lock{ m_CriticalSection };

            if (m_State == true)
            {
                if (m_EventType == EventType::AutoReset)
                {
                    m_State = false;
                }

                return true;
            }
            else
            {
                return false;
            }
        }
    };
}

namespace Graphyte::Threading
{
    using Barrier = LinuxBarrier;
    using CriticalSection = LinuxCriticalSection;
    using ConditionVariable = LinuxConditionVariable;
    using Semaphore = LinuxSemaphore;
    using ReaderWriterLock = LinuxReaderWriterLock;
    using Event = LinuxEvent;
}
