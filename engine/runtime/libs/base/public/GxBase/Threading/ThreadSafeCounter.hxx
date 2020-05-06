#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Threading
{
    template <typename T>
    struct ThreadSafeCounter
    {
        static_assert(std::is_integral<T>::value == true, "T must be integral type");

    private:
        std::atomic<T> m_Counter;

    public:
        ThreadSafeCounter() noexcept
            : m_Counter{ 0 }
        {
        }
        ThreadSafeCounter(T value) noexcept
            : m_Counter{ value }
        {
        }
        ThreadSafeCounter(const ThreadSafeCounter& value) noexcept
            : m_Counter{ value.m_Counter }
        {
        }

    public:
        T Value() const noexcept
        {
            return this->m_Counter;
        }
        T Value(T value) noexcept
        {
            return this->m_Counter.exchange(value);
        }
        T Reset() noexcept
        {
            return this->m_Counter.exchange(0);
        }

    public:
        T Add(T value) noexcept
        {
            return this->m_Counter += value;
        }
        T Subtract(T value) noexcept
        {
            return this->m_Counter -= value;
        }

        T Increment() noexcept
        {
            return ++this->m_Counter;
        }
        T Decrement() noexcept
        {
            return --this->m_Counter;
        }
    };
}
