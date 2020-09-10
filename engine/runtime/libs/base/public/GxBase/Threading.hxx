#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>

// =================================================================================================
//
// Parallel For
//

namespace Graphyte::Threading
{
    /// @brief Executes specified code in parallel threads for specified amount of items.
    ///
    /// @param count         Provides number of items to run on parallel threads.
    /// @param code          Provides delegate to invoke for each item in parallel.
    /// @param single_thread Specifies whether this loop should be invoked on single thread.
    BASE_API void ParallelFor(
        uint32_t count,
        std::function<void(uint32_t)> code,
        bool single_thread = false) noexcept;

    /// @brief Executes specified code in parallel threads for specified amount of items.
    ///
    /// @param count         Provides number of items to run on parallel threads.
    /// @param code          Provides delegate to invoke for each item in parallel.
    /// @param preprocess    Provides delegate to invoke before parallel for runs.
    /// @param single_thread Specifies whether this loop should be invoked on single thread.
    BASE_API void ParallelFor(
        uint32_t count,
        std::function<void(uint32_t)> code,
        std::function<void(void)> preprocess,
        bool singlethreaded = false) noexcept;
}


// =================================================================================================
//
// Volatile load/store.
//
// ref: https://embeddedartistry.com/blog/2019/3/11/improving-volatile-usage-with-volatileload-and-volatilestore
//

namespace Graphyte::Threading
{
    template <typename T>
    [[nodiscard]] inline T VolatileLoad(const T* p) noexcept
        requires(std::is_trivially_copyable_v<T>)
    {
        GX_ASSERT(p != nullptr);

        return *static_cast<const volatile T*>(p);
    }

    template <typename T>
    inline void VolatileStore(T* p, T v) noexcept
        requires(std::is_trivially_copyable_v<T>)
    {
        GX_ASSERT(p != nullptr);

        *static_cast<volatile T*>(p) = v;
    }
}


// =================================================================================================
//
// Common thread types.
//

namespace Graphyte::Threading
{
    enum class ThreadPriority
    {
        TimeCritical,
        Highest,
        AboveNormal,
        Normal,
        BelowNormal,
        Lower,
        Lowest,
    };

    enum struct ThreadAffinity : uint64_t
    {
        None = uint64_t{},
        All  = ~uint64_t{},
    };

    [[nodiscard]] constexpr ThreadAffinity MakeThreadAffinity(uint64_t processor) noexcept
    {
        return static_cast<ThreadAffinity>(uint64_t{ 1 } << processor);
    }

    struct ThreadHandle final
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
        ::HANDLE Value;
#elif GX_PLATFORM_POSIX
        ::pthread_t Value;
#else
#error Not supported.
#endif

        [[nodiscard]] bool IsValid() const noexcept
        {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
            return Value != nullptr;
#elif GX_PLATFORM_POSIX
            return Value != 0;
#else
#error Not supported
#endif
        }
    };

    struct ThreadId final
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
        ::DWORD Value;
#elif GX_PLATFORM_POSIX
        ::pthread_t Value;
#else
#error Not supported.
#endif
    };
}


// =================================================================================================
//
// Common functions.
//

namespace Graphyte::Threading
{
    /// @brief Yields execution of current thread.
    __forceinline void YieldThread() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        ::Sleep(0);

#elif GX_PLATFORM_POSIX

        sched_yield();

#else
#error Not implemented
#endif
    }

    /// @brief Sleeps current thread for specified time in milliseconds.
    ///
    /// @param milliseconds Provides timeout in milliseconds.
    __forceinline void SleepThread(uint32_t milliseconds) noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        ::Sleep(milliseconds);

#elif GX_PLATFORM_POSIX

        usleep(milliseconds * 1000);

#else
#error Not implemented
#endif
    }

    /// @brief Gets current thread id.
    [[nodiscard]] __forceinline ThreadId CurrentThreadId() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        return ThreadId{ .Value = ::GetCurrentThreadId() };

#elif GX_PLATFORM_POSIX

        return ThreadId{ ::pthread_self() };

#else
#error Not implemented
#endif
    }
}

// =================================================================================================
//
// Barriers
//

namespace Graphyte::Threading
{
    __forceinline void LoadBarrier() noexcept
    {
#if GX_COMPILER_MSVC
        _ReadBarrier();
#else
        // clang-format off
        __asm__ __volatile__("" : : : "memory");
        // clang-format on
#endif
    }

    __forceinline void StoreBarrier() noexcept
    {
#if GX_COMPILER_MSVC
        _WriteBarrier();
#else
        // clang-format off
        __asm__ __volatile__("" : : : "memory");
        // clang-format on
#endif
    }

    __forceinline void LoadStoreBarrier() noexcept
    {
#if GX_COMPILER_MSVC
        _ReadWriteBarrier();
#else
        // clang-format off
        __asm__ __volatile__("" : : : "memory");
        // clang-format on
#endif
    }
}


// =================================================================================================
//
// Fences
//

namespace Graphyte::Threading
{
    // See: https://preshing.com/20120710/memory-barriers-are-like-source-control-operations/

    __forceinline void StoreStoreFence() noexcept
    {
#if GX_CPU_X86_32 || GX_CPU_X86_64
        StoreBarrier();
        _mm_sfence();
#elif GX_CPU_ARM_64 && GX_COMPILER_MSVC
        __dmb(_ARM64_BARRIER_ISHST);
#elif GX_CPU_ARM_64 && (GX_COMPILER_GCC || GX_COMPILER_CLANG)
        // clang-format off
        __asm__ __volatile__("dmb ishst" : : : "memory");
        // clang-format on
#elif GX_CPU_ARM_32 && GX_COMPILER_MSVC
        __dmb(_ARM_BARRIER_ISHST);
#elif GX_CPU_ARM_32 && (GX_COMPILER_GCC || GX_COMPILER_CLANG)
        // clang-format off
        __asm__ __volatile__("dmb ishst" : : : "memory");
        // clang-format on
#else
#error "Not supported"
#endif
    }

    __forceinline void StoreLoadFence() noexcept
    {
#if GX_CPU_X86_32 || GX_CPU_X86_64
        StoreBarrier();
        _mm_mfence();
#elif GX_CPU_ARM_64 && GX_COMPILER_MSVC
        __dmb(_ARM64_BARRIER_ISH);
#elif GX_CPU_ARM_64 && (GX_COMPILER_GCC || GX_COMPILER_CLANG)
        // clang-format off
        __asm__ __volatile__("dmb ish" : : : "memory");
        // clang-format on
#elif GX_CPU_ARM_32 && GX_COMPILER_MSVC
        __dmb(_ARM_BARRIER_ISH);
#elif GX_CPU_ARM_32 && (GX_COMPILER_GCC || GX_COMPILER_CLANG)
        // clang-format off
        __asm__ __volatile__("dmb ish" : : : "memory");
        // clang-format on
#else
#error "Not supported"
#endif
    }

    __forceinline void LoadStoreFence() noexcept
    {
#if GX_CPU_X86_32 || GX_CPU_X86_64
        StoreBarrier();
        _mm_mfence();
#elif GX_CPU_ARM_64 && GX_COMPILER_MSVC
        __dmb(_ARM64_BARRIER_ISHLD);
#elif GX_CPU_ARM_64 && (GX_COMPILER_GCC || GX_COMPILER_CLANG)
        // clang-format off
        __asm__ __volatile__("dmb ishld" : : : "memory");
        // clang-format on
#elif GX_CPU_ARM_32 && GX_COMPILER_MSVC
        __dmb(_ARM_BARRIER_ISH);
#elif GX_CPU_ARM_32 && (GX_COMPILER_GCC || GX_COMPILER_CLANG)
        // clang-format off
        __asm__ __volatile__("dmb ish" : : : "memory");
        // clang-format on
#else
#error "Not supported"
#endif
    }

    __forceinline void LoadLoadFence() noexcept
    {
#if GX_CPU_X86_32 || GX_CPU_X86_64
        StoreBarrier();
        _mm_lfence();
#elif GX_CPU_ARM_64 && GX_COMPILER_MSVC
        __dmb(_ARM64_BARRIER_ISHLD);
#elif GX_CPU_ARM_64 && (GX_COMPILER_GCC || GX_COMPILER_CLANG)
        // clang-format off
        __asm__ __volatile__("dmb ishld" : : : "memory");
        // clang-format on
#elif GX_CPU_ARM_32 && GX_COMPILER_MSVC
        __dmb(_ARM_BARRIER_ISH);
#elif GX_CPU_ARM_32 && (GX_COMPILER_GCC || GX_COMPILER_CLANG)
        // clang-format off
        __asm__ __volatile__("dmb ish" : : : "memory");
        // clang-format on
#else
#error "Not supported"
#endif
    }

    __forceinline void FullFence() noexcept
    {
        LoadStoreFence();
    }
}
