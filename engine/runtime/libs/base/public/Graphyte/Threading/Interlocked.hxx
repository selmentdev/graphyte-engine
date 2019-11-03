#pragma once
#include <Graphyte/Base.module.hxx>


//
// ref: https://embeddedartistry.com/blog/2019/3/11/improving-volatile-usage-with-volatileload-and-volatilestore
//

namespace Graphyte::Threading
{
    template <typename T>
    inline T VolatileLoad(const T* p) noexcept
    {
        GX_ASSERT(p != nullptr);

        static_assert(std::is_trivially_copyable_v<T>, "T must be TriviallyCopyable");
        return *static_cast<const volatile T*>(p);
    }

    template <typename T>
    inline void VolatileStore(T* p, T v) noexcept
    {
        GX_ASSERT(p != nullptr);

        static_assert(std::is_trivially_copyable_v<T>, "T must be TriviallyCopyable");
        *static_cast<volatile T*>(p) = v;
    }


    // XXX: Move to separate header
    class Fence final
    {
    public:
        static void StoreStore() noexcept;
        static void StoreLoad() noexcept;
        static void LoadStore() noexcept;
        static void LoadLoad() noexcept;
    };
}

#include <Graphyte/Threading/Interlocked.impl.hxx>
