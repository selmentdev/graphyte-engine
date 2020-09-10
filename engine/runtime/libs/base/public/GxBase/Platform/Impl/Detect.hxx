#pragma once

// =================================================================================================
// Preprocessor token concatenation

#define GX_CONCATENATE_IMPL(x, y) x##y
#define GX_CONCATENATE(x, y)      GX_CONCATENATE_IMPL(x, y)


// =================================================================================================
// Preprocessor token stringize

#define GX_STRINGIZE_IMPL(x) #x
#define GX_STRINGIZE(x)      GX_STRINGIZE_IMPL(x)


// =================================================================================================
// Unique name

#define GX_UNIQUE_NAME(prefix) GX_CONCATENATE(prefix, __LINE__)


// =================================================================================================
// Architecture

#define GX_ARCH_32BIT  0
#define GX_ARCH_64BIT  0
#define GX_ARCH_128BIT 0


// =================================================================================================
// CPU

#define GX_CPU_ARM_64    0
#define GX_CPU_ARM_32    0
#define GX_CPU_X86_64    0
#define GX_CPU_X86_32    0
#define GX_CPU_MIPS_64   0
#define GX_CPU_MIPS_32   0
#define GX_CPU_PPC_64    0
#define GX_CPU_PPC_32    0
#define GX_CPU_RISCV_128 0
#define GX_CPU_RISCV_64  0
#define GX_CPU_RISCV_32  0


// =================================================================================================
// Endianess

#define GX_ENDIAN_LITTLE 0
#define GX_ENDIAN_BIG    0


// =================================================================================================
// CPU properties

#define GX_CACHELINE_SIZE   0
#define GX_UNALIGNED_ACCESS 0


// =================================================================================================
// Hardware CPU extensions

#define GX_HW_AVX   0
#define GX_HW_AVX2  0
#define GX_HW_SSE   0
#define GX_HW_SSE2  0
#define GX_HW_NEON  0
#define GX_HW_FMA3  0
#define GX_HW_FMA4  0
#define GX_HW_F16C  0
#define GX_HW_AESNI 0
#define GX_HW_SHA   0
#define GX_HW_QPX   0
#define GX_HW_VMX   0
#define GX_HW_VSX   0


// =================================================================================================
// Compiler

#define GX_COMPILER_MSVC           0
#define GX_COMPILER_CLANG          0
#define GX_COMPILER_CLANG_ANALYZER 0
#define GX_COMPILER_GCC            0


// =================================================================================================
// Compiler traits

#define GX_HAVE_VECTORCALL 0


// =================================================================================================
// C Runtime Library

#define GX_CRT_MSVC   0
#define GX_CRT_MINGW  0
#define GX_CRT_GLIBC  0
#define GX_CRT_NEWLIB 0
#define GX_CRT_BIONIC 0
#define GX_CRT_MUSL   0
#define GX_CRT_LIBCXX 0
#define GX_CRT_NONE   0


// =================================================================================================
// Platform

#define GX_PLATFORM_ANDROID    0
#define GX_PLATFORM_BSD        0
#define GX_PLATFORM_EMSCRIPTEN 0
#define GX_PLATFORM_IOS        0
#define GX_PLATFORM_LINUX      0
#define GX_PLATFORM_NX         0
#define GX_PLATFORM_OSX        0
#define GX_PLATFORM_PS4        0
#define GX_PLATFORM_RPI        0
#define GX_PLATFORM_STEAMLINK  0
#define GX_PLATFORM_WINDOWS    0
#define GX_PLATFORM_UWP        0
#define GX_PLATFORM_XBOXONE    0


// =================================================================================================
// Platform type

#define GX_PLATFORM_TYPE_MOBILE  0
#define GX_PLATFORM_TYPE_DESKTOP 0
#define GX_PLATFORM_TYPE_HYBRID  0
#define GX_PLATFORM_TYPE_CONSOLE 0


// =================================================================================================
// Detect compiler

#if defined(__clang__)
#undef GX_COMPILER_CLANG
#define GX_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#if defined(__clang_analyzer__)
#undef GX_COMPILER_CLANG_ANALYZER
#define GX_COMPILER_CLANG_ANALYZER 1
#endif
#elif defined(_MSC_VER)
#undef GX_COMPILER_MSVC
#define GX_COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
#undef GX_COMPILER_GCC
#define GX_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#error "Cannot detect GX_COMPILER_*"
#endif


// =================================================================================================
// Detect architecture and CPU properties

#if defined(__aarch64__) || defined(_M_ARM64)
#undef GX_CPU_ARM_64
#define GX_CPU_ARM_64 1
#undef GX_ARCH_64BIT
#define GX_ARCH_64BIT 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 64
#elif defined(__arm__) || defined(_M_ARM)
#undef GX_CPU_ARM_32
#define GX_CPU_ARM_32 1
#undef GX_ARCH_32BIT
#define GX_ARCH_32BIT 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 64
#elif defined(__x86_64__) || defined(_M_AMD64)
#undef GX_CPU_X86_64
#define GX_CPU_X86_64 1
#undef GX_ARCH_64BIT
#define GX_ARCH_64BIT 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 64
#elif defined(__i386__) || defined(_M_IX86)
#undef GX_CPU_X86_32
#define GX_CPU_X86_32 1
#undef GX_ARCH_32BIT
#define GX_ARCH_32BIT 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 64
#elif defined(__mips64)
#undef GX_CPU_MIPS_64
#define GX_CPU_MIPS_64 1
#undef GX_ARCH_64BIT
#define GX_ARCH_64BIT 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 64
#elif defined(__MIPSEL__) || defined(__mips_isa_rev)
#undef GX_CPU_MIPS_32
#define GX_CPU_MIPS_32 1
#undef GX_ARCH_32BIT
#define GX_ARCH_32BIT 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 64
#elif defined(__powerpc64__)
#undef GX_CPU_PPC_64
#define GX_CPU_PPC_64 1
#undef GX_ARCH_64BIT
#define GX_ARCH_64BIT 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 128
#elif defined(__powerpc__) || defined(_M_PPC)
#undef GX_CPU_PPC_32
#define GX_CPU_PPC_32 1
#undef GX_ARCH_32BIT
#define GX_ARCH_32BIT 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 128
#elif defined(__riscv) || defined(__riscv__) || defined(RISCVEL)
#undef GX_CPU_RISCV
#define GX_CPU_RISCV 1
#undef GX_CACHELINE_SIZE
#define GX_CACHELINE_SIZE 64
#if defined(__riscv32)
#undef GX_ARCH_32BIT
#define GX_ARCH_32BIT 1
#elif defined(__riscv64)
#undef GX_ARCH_64BIT
#define GX_ARCH_64BIT 1
#elif defined(__riscv128)
#undef GX_ARCH_128BIT
#define GX_ARCH_128BIT 1
#else
#error "Cannot determine bitness of RISCV"
#endif
#else
#error "Cannot detect CPU and architecture"
#endif


// =================================================================================================
// Detect endianess

#if GX_CPU_PPC_32 || GX_CPU_PPC_64
#if _LITTLE_ENDIAN
#undef GX_ENDIAN_LITTLE
#define GX_ENDIAN_LITTLE 1
#else
#undef GX_ENDIAN_BIG
#define GX_ENDIAN_BIG 1
#endif
#else
#undef GX_ENDIAN_LITTLE
#define GX_ENDIAN_LITTLE 1
#endif


// =================================================================================================
// Detect platform

#if defined(_WIN32) || defined(_WIN64)
// Try to include winapi family
#if defined(_MSC_VER) && (_MSC_VER >= 1700)
#include <winapifamily.h>
#endif

#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#undef GX_PLATFORM_WINDOWS
#define GX_PLATFORM_WINDOWS 1
#else
#undef GX_PLATFORM_UWP
#define GX_PLATFORM_UWP 1
#endif
#elif defined(__ANDROID__)
#undef GX_PLATFORM_ANDROID
#define GX_PLATFORM_ANDROID 1
#elif defined(__STEAMLINK__)
#undef GX_PLATFORM_STEAMLINK
#define GX_PLATFORM_STEAMLINK 1
#elif defined(__VCCOREVER__)
#undef GX_PLATFORM_RPI
#define GX_PLATFORM_RPI 1
#elif defined(__linux__)
#undef GX_PLATFORM_LINUX
#define GX_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__)
#undef GX_PLATFORM_IOS
#define GX_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#undef GX_PLATFORM_OSX
#define GX_PLATFORM_OSX __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#elif defined(__EMSCRIPTEN__)
#undef GX_PLATFORM_EMSCRIPTEN
#define GX_PLATFORM_EMSCRIPTEN 1
#elif defined(__ORBIS__)
#undef GX_PLATFORM_PS4
#define GX_PLATFORM_PS4 1
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
#undef GX_PLATFORM_BSD
#define GX_PLATFORM_BSD 1
#elif defined(__NX__)
#undef GX_PLATFORM_NX
#define GX_PLATFORM_NX 1
#elif defined(_DURANGO) || defined(_XBOX_ONE)
#undef GX_PLATFORM_XBOXONE
#define GX_PLATFORM_XBOXONE 1
#else
#error "Cannot detect platform"
#endif


// =================================================================================================
// Detect platform type.

#if GX_PLATFORM_ANDROID || GX_PLATFORM_IOS
#undef GX_PLATFORM_TYPE_MOBILE
#define GX_PLATFORM_TYPE_MOBILE 1
#endif


#if GX_PLATFORM_BSD || GX_PLATFORM_LINUX || GX_PLATFORM_OSX || GX_PLATFORM_WINDOWS
#undef GX_PLATFORM_TYPE_DESKTOP
#define GX_PLATFORM_TYPE_DESKTOP 1
#endif

#if GX_PLATFORM_EMSCRIPTEN || GX_PLATFORM_RPI || GX_PLATFORM_UWP
#undef GX_PLATFORM_TYPE_HYBRID
#define GX_PLATFORM_TYPE_HYBRID 1
#endif

#if GX_PLATFORM_NX || GX_PLATFORM_PS4 || GX_PLATFORM_STEAMLINK || GX_PLATFORM_XBOXONE
#undef GX_PLATFORM_TYPE_CONSOLE
#define GX_PLATFORM_TYPE_CONSOLE 1
#endif


// =================================================================================================
// Detect if platform is posix compatible

#define GX_PLATFORM_POSIX (0 \
                                 || GX_PLATFORM_ANDROID \
                                 || GX_PLATFORM_BSD \
                                 || GX_PLATFORM_EMSCRIPTEN \
                                 || GX_PLATFORM_IOS \
                                 || GX_PLATFORM_LINUX \
                                 || GX_PLATFORM_NX \
                                 || GX_PLATFORM_OSX \
                                 || GX_PLATFORM_PS4 \
                                 || GX_PLATFORM_RPI \
                                 || GX_PLATFORM_STEAMLINK)


// =================================================================================================
// Detect if we support pthreads

#define GX_HAVE_PTHREADS (0 \
                                || GX_PLATFORM_ANDROID \
                                || GX_PLATFORM_BSD \
                                || GX_PLATFORM_EMSCRIPTEN \
                                || GX_PLATFORM_IOS \
                                || GX_PLATFORM_LINUX \
                                || GX_PLATFORM_OSX \
                                || GX_PLATFORM_RPI \
                                || GX_PLATFORM_STEAMLINK)


// =================================================================================================
// Detect CRT

#if !GX_CRT_NONE
#if defined(__BIONIC__)
#undef GX_CRT_BIONIC
#define GX_CRT_BIONIC 1
#elif defined(_MSC_VER)
#undef GX_CRT_MSVC
#define GX_CRT_MSVC 1
#elif defined(__GLIBC__)
#undef GX_CRT_GLIBC
#define GX_CRT_GLIBC (__GLIBC__ * 10000 + __GLIBC_MINOR__ * 100)
#elif defined(__MINGW32__) || defined(__MINGW64__)
#undef GX_CRT_MINGW
#define GX_CRT_MINGW 1
#elif defined(__apple_build_version__) || defined(__ORBIS__) || defined(__EMSCRIPTEN__) || defined(__llvm__)
#undef GX_CRT_LIBCXX
#define GX_CRT_LIBCXX 1
#else
#undef GX_CRT_NONE
#define GX_CRT_NONE 1
#endif
#endif


// =================================================================================================
// Detect compiler name

#if GX_COMPILER_MSVC
#if GX_COMPILER_MSVC >= 1920 // Visual Studio 2019
#define GX_COMPILER_NAME "MSVC 16.0"
#elif GX_COMPILER_MSVC >= 1910 // Visual Studio 2017
#define GX_COMPILER_NAME "MSVC 15.0"
#elif GX_COMPILER_MSVC >= 1900 // Visual Studio 2015
#define GX_COMPILER_NAME "MSVC 14.0"
#elif GX_COMPILER_MSVC >= 1800 // Visual Studio 2013
#define GX_COMPILER_NAME "MSVC 12.0"
#elif GX_COMPILER_MSVC >= 1700 // Visual Studio 2012
#define GX_COMPILER_NAME "MSVC 11.0"
#elif GX_COMPILER_MSVC >= 1600 // Visual Studio 2010
#define GX_COMPILER_NAME "MSVC 10.0"
#elif GX_COMPILER_MSVC >= 1500 // Visual Studio 2008
#define GX_COMPILER_NAME "MSVC 9.0"
#else
#define GX_COMPILER_NAME "MSVC"
#endif
#elif GX_COMPILER_CLANG
#define GX_COMPILER_NAME "Clang " GX_STRINGIZE(__clang_major__) "." GX_STRINGIZE(__clang_minor__) "." GX_STRINGIZE(__clang_patchlevel__)
#elif GX_COMPILER_GCC
#define GX_COMPILER_NAME "GCC " GX_STRINGIZE(__GNUC__) "." GX_STRINGIZE(__GNUC_MINOR__) "." GX_STRINGIZE(__GNUC_PATCHLEVEL__)
#endif


// =================================================================================================
// Detect platform name

#if GX_PLATFORM_ANDROID
#define GX_PLATFORM_NAME "Android " GX_STRINGIZE(GX_PLATFORM_ANDROID)
#elif GX_PLATFORM_BSD
#define GX_PLATFORM_NAME "BSD"
#elif GX_PLATFORM_EMSCRIPTEN
#define GX_PLATFORM_NAME "asm.js " GX_STRINGIZE(__EMSCRIPTEN_major__) "." GX_STRINGIZE(__EMSCRIPTEN_minor__) "." GX_STRINGIZE(__EMSCRIPTEN_tiny__)
#elif GX_PLATFORM_IOS
#define GX_PLATFORM_NAME "iOS"
#elif GX_PLATFORM_LINUX
#define GX_PLATFORM_NAME "Linux"
#elif GX_PLATFORM_NX
#define GX_PLATFORM_NAME "NX"
#elif GX_PLATFORM_OSX
#define GX_PLATFORM_NAME "OSX"
#elif GX_PLATFORM_PS4
#define GX_PLATFORM_NAME "PlayStation 4"
#elif GX_PLATFORM_RPI
#define GX_PLATFORM_NAME "Raspberry PI"
#elif GX_PLATFORM_STEAMLINK
#define GX_PLATFORM_NAME "SteamLink"
#elif GX_PLATFORM_WINDOWS
#define GX_PLATFORM_NAME "Windows"
#elif GX_PLATFORM_UWP
#define GX_PLATFORM_NAME "UWP"
#elif GX_PLATFORM_XBOXONE
#define GX_PLATFORM_NAME "Xbox One"
#endif


// =================================================================================================
// Detect CPU name

#if GX_CPU_ARM_64
#define GX_CPU_NAME "ARM64"
#elif GX_CPU_ARM_32
#define GX_CPU_NAME "ARM"
#elif GX_CPU_X86_32
#define GX_CPU_NAME "X86-32"
#elif GX_CPU_X86_64
#define GX_CPU_NAME "X86-64"
#elif GX_CPU_MIPS_32
#define GX_CPU_NAME "MIPS"
#elif GX_CPU_MIPS_64
#define GX_CPU_NAME "MIPS64"
#elif GX_CPU_PPC_32
#define GX_CPU_NAME "PowerPC"
#elif GX_CPU_PPC_64
#define GX_CPU_NAME "PowerPC64"
#elif GX_CPU_RISCV_32
#define GX_CPU_NAME "RISC-V-32"
#elif GX_CPU_RISCV_64
#define GX_CPU_NAME "RISC-V-64"
#elif GX_CPU_RISCV_128
#define GX_CPU_NAME "RISC-V-128"
#endif


// =================================================================================================
// Detect bitness name

#if GX_ARCH_32BIT
#define GX_ARCH_NAME "32-bit"
#elif GX_ARCH_64BIT
#define GX_ARCH_NAME "64-bit"
#elif GX_ARCH_128BIT
#define GX_ARCH_NAME "128-bit"
#endif


// =================================================================================================
// Detect CRT name

#if GX_CRT_MSVC
#define GX_CRT_NAME "MSVC C Runtime"
#elif GX_CRT_MINGW
#define GX_CRT_NAME "MinGW C Runtime"
#elif GX_CRT_GLIBC
#define GX_CRT_NAME "GNU C Library"
#elif GX_CRT_NEWLIB
#define GX_CRT_NAME "newlib"
#elif GX_CRT_BIONIC
#define GX_CRT_NAME "Bionic libc"
#elif GX_CRT_MUSL
#define GX_CRT_NAME "musl libc"
#elif GX_CRT_LIBCXX
#define GX_CRT_NAME "Clang C library"
#elif GX_CRT_NONE
#define GX_CRT_NAME "none"
#endif


// =================================================================================================
// Detect compiler features

#if (GX_COMPILER_MSVC || GX_COMPILER_CLANG) && (GX_PLATFORM_WINDOWS || GX_PLATFORM_XBOXONE || GX_PLATFORM_UWP)
#undef GX_HAVE_VECTORCALL
#define GX_HAVE_VECTORCALL 1
#endif

#if GX_COMPILER_MSVC
#undef GX_MATH_SVML
#define GX_MATH_SVML 1
#endif

#if GX_COMPILER_MSVC && (GX_PLATFORM_WINDOWS || GX_PLATFORM_XBOXONE || GX_PLATFORM_UWP)
#define GX_PLATFORM_HAVE_SEH_EXCEPTIONS 1
#else
#define GX_PLATFORM_HAVE_SEH_EXCEPTIONS 0
#endif


// =================================================================================================
// Detect CPU properties

#if GX_CPU_ARM_64 || GX_CPU_X86_64 || GX_CPU_X86_32
#undef GX_UNALIGNED_ACCESS
#define GX_UNALIGNED_ACCESS 1
#endif

#if defined(__AVX__)
#undef GX_HW_AVX
#define GX_HW_AVX 1
#endif

#if defined(__AVX2__)
#undef GX_HW_AVX2
#define GX_HW_AVX2 1
#endif

#if defined(__SSE__) || defined(_M_X64) || (_M_IX86_FP >= 1)
#undef GX_HW_SSE
#define GX_HW_SSE 1
#endif

#if defined(__SSE2__) || defined(_M_X64) || (_M_IX86_FP >= 2)
#undef GX_HW_SSE2
#define GX_HW_SSE2 1
#endif

#if defined(__F16C__) || defined(__AVX2__)
#undef GX_HW_F16C
#define GX_HW_F16C 1
#endif

#if defined(__FMA__) || defined(__AVX2__)
#undef GX_HW_FMA3
#define GX_HW_FMA3 1
#endif

#if defined(__AESNI__) || defined(__AVX2__)
#undef GX_HW_AESNI
#define GX_HW_AESNI 1
#endif

#if defined(__SHA__) || defined(__AVX2__)
#undef GX_HW_SHA
#define GX_HW_SHA 1
#endif

#if defined(__FMA4__)
#undef GX_HW_FMA4
#define GX_HW_FMA4 1
#endif

#if defined(__ARM_NEON__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64)
#undef GX_HW_NEON
#define GX_HW_NEON 1
#endif

#if defined(__VECTOR4DOUBLE__)
#undef GX_HW_QPX
#define GX_HW_QPX 1
#endif

#if defined(__ALTIVEC__) || defined(__VEC__)
#undef GX_HW_VMX
#define GX_HW_VMX 1
#endif

#if defined(__VSX__)
#undef GX_HW_VSX
#define GX_HW_VSX 1
#endif


// =================================================================================================
// Configuration type detection.

#if !defined(GX_CONFIG_RELEASE)
#define GX_CONFIG_RELEASE 0
#endif

#if !defined(GX_CONFIG_PROFILE)
#define GX_CONFIG_PROFILE 0
#endif

#if !defined(GX_CONFIG_DEBUG)
#define GX_CONFIG_DEBUG 0
#endif

#if !defined(GX_CONFIG_CHECKED)
#define GX_CONFIG_CHECKED 0
#endif

// Validate definitions

#if (GX_CONFIG_RELEASE + GX_CONFIG_PROFILE + GX_CONFIG_DEBUG + GX_CONFIG_CHECKED) != 1
#error Invalid config specified
#endif


// =================================================================================================
// Build type

#if !defined(GX_BUILD_TYPE_DEVELOPER)
#define GX_BUILD_TYPE_DEVELOPER 0
#endif

#if !defined(GX_BUILD_TYPE_TESTING)
#define GX_BUILD_TYPE_TESTING 0
#endif

#if !defined(GX_BUILD_TYPE_RETAIL)
#define GX_BUILD_TYPE_RETAIL 0
#endif

// Validate build type

#if (GX_BUILD_TYPE_DEVELOPER + GX_BUILD_TYPE_TESTING + GX_BUILD_TYPE_RETAIL) != 1
#error Invalid build type specified
#endif


// =================================================================================================
// Asserts configuration

#if GX_BUILD_TYPE_RETAIL
#define GX_CONFIG_DO_ASSERT 0
#define GX_CONFIG_DO_VERIFY 0
#define GX_CONFIG_DO_ENSURE 0
#endif

#if !defined(GX_CONFIG_DO_ASSERT)
#define GX_CONFIG_DO_ASSERT 1
#endif

#if !defined(GX_CONFIG_DO_VERIFY)
#define GX_CONFIG_DO_VERIFY 1
#endif

#if !defined(GX_CONFIG_DO_ENSURE)
#define GX_CONFIG_DO_ENSURE 1
#endif


// =================================================================================================
// Configure build options

#if GX_BUILD_TYPE_RETAIL
#define GX_STATIC_BUILD 0 // requires more support from fastbuild right now :(
#else
#define GX_STATIC_BUILD 0
#endif

#if !defined(GX_MATH_NO_INTRINSICS)
#define GX_MATH_NO_INTRINSICS 0
#endif

#if !defined(GX_MATH_SVML)
#define GX_MATH_SVML 0
#endif

#if !defined(GX_MATH_FAST_FUNCTIONS)
#define GX_MATH_FAST_FUNCTIONS 1
#endif

#if !defined(GX_MATH_ENABLE_OPERATORS)
#define GX_MATH_ENABLE_OPERATORS 1
#endif

#if !defined(GX_PLATFORM_HAS_TOUCH_SCREEN)
#define GX_PLATFORM_HAS_TOUCH_SCREEN 0
#endif

#if !defined(GX_ENABLE_DEBUG_RENDER)
#define GX_ENABLE_DEBUG_RENDER 1
#endif


// =================================================================================================
// Stack trace support

#if GX_BUILD_TYPE_RETAIL
#define GX_ENABLE_STACKTRACE 0
#define GX_ENABLE_STACKTRACE_SYMBOLS 0
#define GX_ENABLE_STACKTRACE_FAST 0
#endif

#if !defined(GX_ENABLE_STACKTRACE)
#define GX_ENABLE_STACKTRACE 1
#endif

#if !defined(GX_ENABLE_STACKTRACE_SYMBOLS)
#define GX_ENABLE_STACKTRACE_SYMBOLS 1
#endif

#if !defined(GX_ENABLE_STACKTRACE_FAST)
#define GX_ENABLE_STACKTRACE_FAST 1
#endif


// =================================================================================================
// Profiler

#define GX_ENABLE_PROFILE 0

// Update inline depth
#if defined(_MSC_VER)
#pragma inline_depth(255)
#endif


// =================================================================================================
// Noinline attribute.

#if defined(_MSC_VER)
#define GX_NOINLINE __declspec(noinline)
#else
#define GX_NOINLINE __attribute__((__noinline__))
#endif


// =================================================================================================
// Forceinline attribute.

#if !(defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__))
#define __forceinline inline __attribute__((always_inline))
#endif


// =================================================================================================
// Unreachable declarator.

#if defined(_MSC_VER)
#define GX_DECLARE_UNREACHABLE()
#else
#define GX_DECLARE_UNREACHABLE() __builtin_unreachable()
#endif


// =================================================================================================
// Assume

#if defined(_MSC_VER)
#define GX_COMPILER_ASSUME(expression) __analysis_assume(!!(expression))
#else
#define GX_COMPILER_ASSUME(expression)
#endif


// =================================================================================================
// Debugger break.

#if defined(_MSC_VER)
#define GX_DEBUG_BREAK __debugbreak
#elif defined(__GNUC__)
#define GX_DEBUG_BREAK __builtin_trap
#else
#define GX_DEBUG_BREAK __builtin_debugtrap
#endif


// =================================================================================================
// Export / import.

#if defined(_MSC_VER)
#define GX_MODULE_EXPORT __declspec(dllexport)
#define GX_MODULE_IMPORT __declspec(dllimport)
#elif defined(__CYGWIN__) && defined(__GNUC__)
#define GX_MODULE_EXPORT __attribute__((__dllexport__))
#define GX_MODULE_IMPORT __attribute__((__dllimport__))
#else
#define GX_MODULE_EXPORT __attribute__((visibility("default")))
#define GX_MODULE_IMPORT __attribute__((visibility("default")))
#endif


// =================================================================================================
// Likely / unlikely.

#if defined(_MSC_VER)
#define GX_LIKELY(expression)   (expression)
#define GX_UNLIKELY(expression) (expression)
#else
#define GX_LIKELY(expression)   __builtin_expect(!!(expression), 1)
#define GX_UNLIKELY(expression) __builtin_expect(!!(expression), 0)
#endif

#if defined(_MSC_VER)
#define GX_PACKED __declspec(align(1))
#else
#define GX_PACKED __attribute__((__packed__))
#endif


// =================================================================================================
// Platform specific headers

#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
#include <GxBase/Platform/Impl/Headers.Windows.hxx>
#elif GX_PLATFORM_LINUX
#include <GxBase/Platform/Impl/Headers.Linux.hxx>
#elif GX_PLATFORM_ANDROID
#include <GxBase/Platform/Impl/Headers.Android.hxx>
#else
#error "Unsupported platform"
#endif


// =================================================================================================
// Disable compiler warnings

#if GX_COMPILER_MSVC
#include <GxBase/Platform/Impl/CompilerWarnings.msvc.hxx>
#elif GX_COMPILER_CLANG
#include <GxBase/Platform/Impl/CompilerWarnings.clang.hxx>
#elif GX_COMPILER_GCC
#include <GxBase/Platform/Impl/CompilerWarnings.gcc.hxx>
#endif


// =================================================================================================
// Enable / Disable optimizations macros

#if GX_COMPILER_MSVC

#define GX_OPTIMIZE_ENABLE  __pragma(optimize("", on))
#define GX_OPTIMIZE_DISABLE __pragma(optimize("", off))

#elif GX_COMPILER_CLANG

#define GX_OPTIMIZE_ENABLE  _Pragma("clang optimize on")
#define GX_OPTIMIZE_DISABLE _Pragma("clang optimize off")

#elif GX_COMPILER_GCC

#define GX_OPTIMIZE_ENABLE
#define GX_OPTIMIZE_DISABLE

#else
#error "Not supported compiler"
#endif

#if !defined(NDEBUG)
#define GX_OPTIMIZE_RESTORE GX_OPTIMIZE_DISABLE
#else
#define GX_OPTIMIZE_RESTORE GX_OPTIMIZE_ENABLE
#endif


// =================================================================================================
// Validate minimum required version

#if GX_COMPILER_MSVC
#if _MSC_VER < 1925
#error "MSVC version not supported"
#endif
#endif

#if GX_COMPILER_CLANG
#if __clang_major__ < 10
#error "Clang version not supported"
#endif
#endif


// =================================================================================================
// Enable bit operations for specified enum type.

#define GX_ENUM_CLASS_FLAGS(enum_type) \
    inline enum_type& operator|=(enum_type& lhs, const enum_type rhs) noexcept { return lhs = static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) | static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline enum_type& operator&=(enum_type& lhs, const enum_type rhs) noexcept { return lhs = static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) & static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline enum_type& operator^=(enum_type& lhs, const enum_type rhs) noexcept { return lhs = static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) & static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline constexpr enum_type operator|(const enum_type lhs, const enum_type rhs) noexcept { return static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) | static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline constexpr enum_type operator&(const enum_type lhs, const enum_type rhs) noexcept { return static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) & static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline constexpr enum_type operator^(const enum_type lhs, const enum_type rhs) noexcept { return static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) ^ static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline constexpr bool operator!(const enum_type value) noexcept { return !static_cast<std::underlying_type_t<enum_type>>(value); } \
    inline constexpr enum_type operator~(const enum_type value) noexcept { return static_cast<enum_type>(~static_cast<std::underlying_type_t<enum_type>>(value)); }


#define GX_SDKS_WITH_ZLIB 0
