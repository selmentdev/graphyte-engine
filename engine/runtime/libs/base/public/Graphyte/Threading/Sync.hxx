#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::Threading
{
    enum class EventType
    {
        AutoReset,
        ManualReset,
    };

    template <typename TLock>
    class ScopedLock final
    {
        ScopedLock(const ScopedLock&) = delete;
        ScopedLock& operator= (const ScopedLock&) = delete;
    private:
        TLock& m_Lock;

    public:
        ScopedLock(TLock& lock) noexcept
            : m_Lock{ lock }
        {
            m_Lock.Enter();
        }
        ~ScopedLock() noexcept
        {
            m_Lock.Leave();
        }
    };

    template <typename TLock>
    class ScopedReaderLock final
    {
        ScopedReaderLock(const ScopedReaderLock&) = delete;
        ScopedReaderLock& operator= (const ScopedReaderLock&) = delete;
    private:
        TLock& m_Lock;

    public:
        ScopedReaderLock(TLock& lock) noexcept
            : m_Lock{ lock }
        {
            m_Lock.EnterReader();
        }
        ~ScopedReaderLock() noexcept
        {
            m_Lock.LeaveReader();
        }
    };

    template <typename TLock>
    class ScopedWriterLock final
    {
        ScopedWriterLock(const ScopedWriterLock&) = delete;
        ScopedWriterLock& operator= (const ScopedWriterLock&) = delete;
    private:
        TLock& m_Lock;

    public:
        ScopedWriterLock(TLock& lock) noexcept
            : m_Lock{ lock }
        {
            m_Lock.EnterWriter();
        }
        ~ScopedWriterLock() noexcept
        {
            m_Lock.LeaveWriter();
        }
    };
}

#if GRAPHYTE_PLATFORM_WINDOWS
#include <Graphyte/Threading/Impl.Windows/Windows.Sync.hxx>
#elif GRAPHYTE_PLATFORM_LINUX
#include <Graphyte/Threading/Impl.Linux/Linux.Sync.hxx>
#elif GRAPHYTE_PLATFORM_ANDROID
#include <Graphyte/Threading/Impl.Android/Android.Sync.hxx>
#else
#error "Unknown platform"
#endif
