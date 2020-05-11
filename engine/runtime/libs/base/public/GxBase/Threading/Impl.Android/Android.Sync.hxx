#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Threading/Sync.hxx>
#include <GxBase/System/Android/AndroidTypeConverter.hxx>

namespace Graphyte::Threading
{
    class AndroidBarrier final
    {
        AndroidBarrier(const AndroidBarrier&) = delete;
        AndroidBarrier& operator= (const AndroidBarrier&) = delete;
    private:
        uint32_t m_Needed;
        uint32_t m_Called;
        pthread_mutex_t m_Mutex;
        pthread_cond_t m_ConditionVariable;

    public:
        AndroidBarrier(uint32_t count) noexcept
            : m_Needed{ count }
            , m_Called{}
            , m_Mutex{}
            , m_ConditionVariable{}
        {
            pthread_mutex_init(&m_Mutex, nullptr);
            pthread_cond_init(&m_ConditionVariable, nullptr);
        }

        ~AndroidBarrier() noexcept
        {
            pthread_cond_destroy(&m_ConditionVariable);
            pthread_mutex_destroy(&m_Mutex);
        }

    public:
        bool Wait() noexcept
        {
            pthread_mutex_lock(&m_Mutex);
            ++m_Called;

            if (m_Called == m_Needed)
            {
                m_Called = 0;
                pthread_cond_broadcast(&m_ConditionVariable);
            }
            else
            {
                pthread_cond_wait(&m_ConditionVariable, &m_Mutex);
            }

            pthread_mutex_unlock(&m_Mutex);

            return true;
        }
    };

    class AndroidCriticalSection final
    {
        friend class AndroidConditionVariable;

        AndroidCriticalSection(const AndroidCriticalSection&) = delete;
        AndroidCriticalSection& operator= (const AndroidCriticalSection&) = delete;

    private:
        pthread_mutex_t m_CriticalSection;

    public:
        AndroidCriticalSection() noexcept
        {
            pthread_mutexattr_t attr{};
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
            pthread_mutex_init(&m_CriticalSection, &attr);
            pthread_mutexattr_destroy(&attr);
        }

        ~AndroidCriticalSection() noexcept
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

    class AndroidConditionVariable final
    {
        AndroidConditionVariable(const AndroidConditionVariable&) = delete;
        AndroidConditionVariable& operator= (const AndroidConditionVariable&) = delete;
    private:
        pthread_cond_t m_ConditionVariable;

    public:
        AndroidConditionVariable() noexcept
        {
            pthread_cond_init(&m_ConditionVariable, nullptr);
        }

        ~AndroidConditionVariable() noexcept
        {
            pthread_cond_destroy(&m_ConditionVariable);
        }

    public:
        bool Wait(AndroidCriticalSection& lock) noexcept
        {
            return pthread_cond_wait(&m_ConditionVariable, &lock.m_CriticalSection) == 0;
        }

        bool Wait(AndroidCriticalSection& lock, uint32_t timeout) noexcept
        {
            auto ts = System::TypeConverter<timespec>::ConvertMilliseconds(timeout);

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

    class AndroidSemaphore final
    {
        AndroidSemaphore(const AndroidSemaphore&) = delete;
        AndroidSemaphore& operator= (const AndroidSemaphore&) = delete;
    private:
        sem_t m_Handle;

    public:
        AndroidSemaphore(int32_t count) noexcept
            : m_Handle{}
        {
            sem_init(&m_Handle, 0, static_cast<unsigned int>(count));
        }

        ~AndroidSemaphore() noexcept
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
            auto ts = System::TypeConverter<timespec>::ConvertMilliseconds(timeout);
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

    class AndroidReaderWriterLock final
    {
        AndroidReaderWriterLock(const AndroidReaderWriterLock&) = delete;
        AndroidReaderWriterLock& operator= (const AndroidReaderWriterLock&) = delte;
    private:
        pthread_rwlock_t m_Lock;

    public:
        AndroidReaderWriterLock() noexcept
        {
            pthread_rwlock_init(&m_Lock, nullptr);
        }

        ~AndroidReaderWriterLock() noexcept
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

    class AndroidEvent final
    {
        AndroidEvent(const AndroidEvent&) = delete;
        AndroidEvent& operator= (const AndroidEvent&) = delete;
    private:
        AndroidCriticalSection m_CriticalSection;
        AndroidConditionVariable m_ConditionVariable;
        EventType m_EventType;
        bool m_State;

    public:
        AndroidEvent(bool state, EventType event_type) noexcept
            : m_CriticalSection{}
            , m_ConditionVariable{}
            , m_EventType{ event_type }
            , m_State{ state }
        {
        }
        ~AndroidEvent() noexcept
        {
        }

    public:
        void Set() noexcept
        {
            ScopedLock<AndroidCriticalSection> lock{ m_CriticalSection };

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
            ScopedLock<AndroidCriticalSection> lock{ m_CriticalSection };

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
            ScopedLock<AndroidCriticalSection> lock{ m_CriticalSection };

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
            ScopedLock<AndroidCriticalSection> lock{ m_CriticalSection };

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
    using Barrier = AndroidBarrier;
    using CriticalSection = AndroidCriticalSection;
    using ConditionVariable = AndroidConditionVariable;
    using Semaphore = AndroidSemaphore;
    using ReaderWriterLock = AndroidReaderWriterLock;
    using Event = AndroidEvent;
}
