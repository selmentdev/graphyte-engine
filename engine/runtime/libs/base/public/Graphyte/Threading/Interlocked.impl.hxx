#pragma once
#include <Graphyte/Threading/Interlocked.hxx>

namespace Graphyte::Threading
{
    // See: https://preshing.com/20120710/memory-barriers-are-like-source-control-operations/
    __forceinline void Fence::StoreStore() noexcept
    {
#if GRAPHYTE_CPU_X86_32 || GRAPHYTE_CPU_X86_64
#   if GRAPHYTE_COMPILER_MSVC
        _WriteBarrier();
#   elif GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG
        __asm__ __volatile__("" ::: "memory");
#   endif
        _mm_sfence();
#elif GRAPHYTE_CPU_ARM_64 && GRAPHYTE_COMPILER_MSVC
        __dmb(_ARM64_BARRIER_ISHST);
#elif GRAPHYTE_CPU_ARM_64 && (GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG)
        __asm__ __volatile__("dmb ishst" : : : "memory");
#elif GRAPHYTE_CPU_ARM_32 && GRAPHYTE_COMPILER_MSVC
        __dmb(_ARM_BARRIER_ISHST);
#elif GRAPHYTE_CPU_ARM_32 && (GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG)
        __asm__ __volatile__("dmb ishst" : : : "memory");
#else
#   error "Not supported"
#endif
    }

    __forceinline void Fence::StoreLoad() noexcept
    {
#if GRAPHYTE_CPU_X86_32 || GRAPHYTE_CPU_X86_64
#   if GRAPHYTE_COMPILER_MSVC
        _WriteBarrier();
#   elif GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG
        __asm__ __volatile__("" ::: "memory");
#   endif
        _mm_mfence();
#elif GRAPHYTE_CPU_ARM_64 && GRAPHYTE_COMPILER_MSVC
        __dmb(_ARM64_BARRIER_ISH);
#elif GRAPHYTE_CPU_ARM_64 && (GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG)
        __asm__ __volatile__("dmb ish" : : : "memory");
#elif GRAPHYTE_CPU_ARM_32 && GRAPHYTE_COMPILER_MSVC
        __dmb(_ARM_BARRIER_ISH);
#elif GRAPHYTE_CPU_ARM_32 && (GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG)
        __asm__ __volatile__("dmb ish" : : : "memory");
#else
#   error "Not supported"
#endif
    }

    __forceinline void Fence::LoadStore() noexcept
    {
#if GRAPHYTE_CPU_X86_32 || GRAPHYTE_CPU_X86_64
#   if GRAPHYTE_COMPILER_MSVC
        _WriteBarrier();
#   elif GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG
        __asm__ __volatile__("" ::: "memory");
#   endif
        _mm_mfence();
#elif GRAPHYTE_CPU_ARM_64 && GRAPHYTE_COMPILER_MSVC
        __dmb(_ARM64_BARRIER_ISHLD);
#elif GRAPHYTE_CPU_ARM_64 && (GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG)
        __asm__ __volatile__("dmb ishld" : : : "memory");
#elif GRAPHYTE_CPU_ARM_32 && GRAPHYTE_COMPILER_MSVC
        __dmb(_ARM_BARRIER_ISH);
#elif GRAPHYTE_CPU_ARM_32 && (GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG)
        __asm__ __volatile__("dmb ish" : : : "memory");
#else
#   error "Not supported"
#endif
    }

    __forceinline void Fence::LoadLoad() noexcept
    {
#if GRAPHYTE_CPU_X86_32 || GRAPHYTE_CPU_X86_64
#   if GRAPHYTE_COMPILER_MSVC
        _WriteBarrier();
#   elif GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG
        __asm__ __volatile__("" ::: "memory");
#   endif
        _mm_lfence();
#elif GRAPHYTE_CPU_ARM_64 && GRAPHYTE_COMPILER_MSVC
        __dmb(_ARM64_BARRIER_ISHLD);
#elif GRAPHYTE_CPU_ARM_64 && (GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG)
        __asm__ __volatile__("dmb ishld" : : : "memory");
#elif GRAPHYTE_CPU_ARM_32 && GRAPHYTE_COMPILER_MSVC
        __dmb(_ARM_BARRIER_ISH);
#elif GRAPHYTE_CPU_ARM_32 && (GRAPHYTE_COMPILER_GCC || GRAPHYTE_COMPILER_CLANG)
        __asm__ __volatile__("dmb ish" : : : "memory");
#else
#   error "Not supported"
#endif
    }
}
