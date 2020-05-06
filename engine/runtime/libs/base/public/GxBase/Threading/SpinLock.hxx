#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Threading
{
    class SpinLock final
    {
    private:
        std::atomic_flag m_Lock;

    public:
        SpinLock() noexcept
            : m_Lock{}
        {
            m_Lock.clear(std::memory_order_relaxed);
        }

        void Enter() noexcept
        {
            while (m_Lock.test_and_set(std::memory_order_acquire))
            {
                ;
            }
        }

        void Leave() noexcept
        {
            m_Lock.clear(std::memory_order_release);
        }
    };
}
