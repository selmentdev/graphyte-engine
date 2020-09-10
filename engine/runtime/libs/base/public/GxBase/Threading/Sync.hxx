#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>

namespace Graphyte::Threading
{
    enum class EventType
    {
        AutoReset,
        ManualReset,
    };

    template <typename TLock>
    class [[nodiscard]] ScopedLock final
    {
    public:
        ScopedLock(const ScopedLock&) = delete;

        ScopedLock& operator=(const ScopedLock&) = delete;

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
    class [[nodiscard]] ScopedReaderLock final
    {
    public:
        ScopedReaderLock(const ScopedReaderLock&) = delete;

        ScopedReaderLock& operator=(const ScopedReaderLock&) = delete;

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
    class [[nodiscard]] ScopedWriterLock final
    {
    public:
        ScopedWriterLock(const ScopedWriterLock&) = delete;

        ScopedWriterLock& operator=(const ScopedWriterLock&) = delete;

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

#if GX_PLATFORM_WINDOWS
#include <GxBase/Threading/Impl.Windows/Windows.Sync.hxx>
#elif GX_PLATFORM_UWP
#include <GxBase/Threading/Impl.UWP/UWP.Sync.hxx>
#elif GX_PLATFORM_LINUX
#include <GxBase/Threading/Impl.Linux/Linux.Sync.hxx>
#elif GX_PLATFORM_ANDROID
#include <GxBase/Threading/Impl.Android/Android.Sync.hxx>
#else
#error "Unknown platform"
#endif
