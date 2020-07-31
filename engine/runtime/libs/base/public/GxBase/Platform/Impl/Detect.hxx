#pragma once

// =================================================================================================
//
// Preprocessor token concatenation
//

#define GX_TOKEN_CONCAT_IMPL(x, y) x##y
#define GX_TOKEN_CONCAT(x, y)      GX_TOKEN_CONCAT_IMPL(x, y)


// =================================================================================================
//
// Preprocessor token stringize
//

#define GX_TOKEN_STRING_IMPL(x) #x
#define GX_TOKEN_STRING(x)      GX_TOKEN_STRING_IMPL(x)


// =================================================================================================
//
// Unique name
//

#define GX_UNIQUE_NAME(prefix) GX_TOKEN_CONCAT(prefix, __LINE__)


// =================================================================================================
//
// Architecture
//

#define GRAPHYTE_ARCH_32BIT  0
#define GRAPHYTE_ARCH_64BIT  0
#define GRAPHYTE_ARCH_128BIT 0


// =================================================================================================
//
// CPU
//

#define GRAPHYTE_CPU_ARM_64    0
#define GRAPHYTE_CPU_ARM_32    0
#define GRAPHYTE_CPU_X86_64    0
#define GRAPHYTE_CPU_X86_32    0
#define GRAPHYTE_CPU_MIPS_64   0
#define GRAPHYTE_CPU_MIPS_32   0
#define GRAPHYTE_CPU_PPC_64    0
#define GRAPHYTE_CPU_PPC_32    0
#define GRAPHYTE_CPU_RISCV_128 0
#define GRAPHYTE_CPU_RISCV_64  0
#define GRAPHYTE_CPU_RISCV_32  0


// =================================================================================================
//
// Endianess
//

#define GRAPHYTE_ENDIAN_LITTLE 0
#define GRAPHYTE_ENDIAN_BIG    0


// =================================================================================================
//
// CPU properties
//

#define GRAPHYTE_CACHELINE_SIZE   0
#define GRAPHYTE_UNALIGNED_ACCESS 0


// =================================================================================================
//
// Hardware CPU extensions
//

#define GRAPHYTE_HW_AVX   0
#define GRAPHYTE_HW_AVX2  0
#define GRAPHYTE_HW_SSE   0
#define GRAPHYTE_HW_SSE2  0
#define GRAPHYTE_HW_NEON  0
#define GRAPHYTE_HW_FMA3  0
#define GRAPHYTE_HW_FMA4  0
#define GRAPHYTE_HW_F16C  0
#define GRAPHYTE_HW_AESNI 0
#define GRAPHYTE_HW_SHA   0
#define GRAPHYTE_HW_QPX   0
#define GRAPHYTE_HW_VMX   0
#define GRAPHYTE_HW_VSX   0


// =================================================================================================
//
// Compiler
//

#define GRAPHYTE_COMPILER_MSVC           0
#define GRAPHYTE_COMPILER_CLANG          0
#define GRAPHYTE_COMPILER_CLANG_ANALYZER 0
#define GRAPHYTE_COMPILER_GCC            0


// =================================================================================================
//
// Compiler traits
//

#define GRAPHYTE_HAVE_VECTORCALL 0


// =================================================================================================
//
// C Runtime Library
//

#define GRAPHYTE_CRT_MSVC   0
#define GRAPHYTE_CRT_MINGW  0
#define GRAPHYTE_CRT_GLIBC  0
#define GRAPHYTE_CRT_NEWLIB 0
#define GRAPHYTE_CRT_BIONIC 0
#define GRAPHYTE_CRT_MUSL   0
#define GRAPHYTE_CRT_LIBCXX 0
#define GRAPHYTE_CRT_NONE   0


// =================================================================================================
//
// Platform
//

#define GRAPHYTE_PLATFORM_ANDROID    0
#define GRAPHYTE_PLATFORM_BSD        0
#define GRAPHYTE_PLATFORM_EMSCRIPTEN 0
#define GRAPHYTE_PLATFORM_IOS        0
#define GRAPHYTE_PLATFORM_LINUX      0
#define GRAPHYTE_PLATFORM_NX         0
#define GRAPHYTE_PLATFORM_OSX        0
#define GRAPHYTE_PLATFORM_PS4        0
#define GRAPHYTE_PLATFORM_RPI        0
#define GRAPHYTE_PLATFORM_STEAMLINK  0
#define GRAPHYTE_PLATFORM_WINDOWS    0
#define GRAPHYTE_PLATFORM_UWP        0
#define GRAPHYTE_PLATFORM_XBOXONE    0


// =================================================================================================
//
// Platform type
//

#define GRAPHYTE_PLATFORM_TYPE_MOBILE  0
#define GRAPHYTE_PLATFORM_TYPE_DESKTOP 0
#define GRAPHYTE_PLATFORM_TYPE_HYBRID  0
#define GRAPHYTE_PLATFORM_TYPE_CONSOLE 0


// =================================================================================================
//
// Detect compiler
//

#if defined(__clang__)
#undef GRAPHYTE_COMPILER_CLANG
#define GRAPHYTE_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#if defined(__clang_analyzer__)
#undef GRAPHYTE_COMPILER_CLANG_ANALYZER
#define GRAPHYTE_COMPILER_CLANG_ANALYZER 1
#endif
#elif defined(_MSC_VER)
#undef GRAPHYTE_COMPILER_MSVC
#define GRAPHYTE_COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
#undef GRAPHYTE_COMPILER_GCC
#define GRAPHYTE_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#error "Cannot detect GRAPHYTE_COMPILER_*"
#endif


// =================================================================================================
//
// Detect architecture and CPU properties
//

#if defined(__aarch64__) || defined(_M_ARM64)
#undef GRAPHYTE_CPU_ARM_64
#define GRAPHYTE_CPU_ARM_64 1
#undef GRAPHYTE_ARCH_64BIT
#define GRAPHYTE_ARCH_64BIT 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 64
#elif defined(__arm__) || defined(_M_ARM)
#undef GRAPHYTE_CPU_ARM_32
#define GRAPHYTE_CPU_ARM_32 1
#undef GRAPHYTE_ARCH_32BIT
#define GRAPHYTE_ARCH_32BIT 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 64
#elif defined(__x86_64__) || defined(_M_AMD64)
#undef GRAPHYTE_CPU_X86_64
#define GRAPHYTE_CPU_X86_64 1
#undef GRAPHYTE_ARCH_64BIT
#define GRAPHYTE_ARCH_64BIT 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 64
#elif defined(__i386__) || defined(_M_IX86)
#undef GRAPHYTE_CPU_X86_32
#define GRAPHYTE_CPU_X86_32 1
#undef GRAPHYTE_ARCH_32BIT
#define GRAPHYTE_ARCH_32BIT 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 64
#elif defined(__mips64)
#undef GRAPHYTE_CPU_MIPS_64
#define GRAPHYTE_CPU_MIPS_64 1
#undef GRAPHYTE_ARCH_64BIT
#define GRAPHYTE_ARCH_64BIT 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 64
#elif defined(__MIPSEL__) || defined(__mips_isa_rev)
#undef GRAPHYTE_CPU_MIPS_32
#define GRAPHYTE_CPU_MIPS_32 1
#undef GRAPHYTE_ARCH_32BIT
#define GRAPHYTE_ARCH_32BIT 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 64
#elif defined(__powerpc64__)
#undef GRAPHYTE_CPU_PPC_64
#define GRAPHYTE_CPU_PPC_64 1
#undef GRAPHYTE_ARCH_64BIT
#define GRAPHYTE_ARCH_64BIT 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 128
#elif defined(__powerpc__) || defined(_M_PPC)
#undef GRAPHYTE_CPU_PPC_32
#define GRAPHYTE_CPU_PPC_32 1
#undef GRAPHYTE_ARCH_32BIT
#define GRAPHYTE_ARCH_32BIT 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 128
#elif defined(__riscv) || defined(__riscv__) || defined(RISCVEL)
#undef GRAPHYTE_CPU_RISCV
#define GRAPHYTE_CPU_RISCV 1
#undef GRAPHYTE_CACHELINE_SIZE
#define GRAPHYTE_CACHELINE_SIZE 64
#if defined(__riscv32)
#undef GRAPHYTE_ARCH_32BIT
#define GRAPHYTE_ARCH_32BIT 1
#elif defined(__riscv64)
#undef GRAPHYTE_ARCH_64BIT
#define GRAPHYTE_ARCH_64BIT 1
#elif defined(__riscv128)
#undef GRAPHYTE_ARCH_128BIT
#define GRAPHYTE_ARCH_128BIT 1
#else
#error "Cannot determine bitness of RISCV"
#endif
#else
#error "Cannot detect CPU and architecture"
#endif


// =================================================================================================
//
// Detect endianess
//

#if GRAPHYTE_CPU_PPC_32 || GRAPHYTE_CPU_PPC_64
#if _LITTLE_ENDIAN
#undef GRAPHYTE_ENDIAN_LITTLE
#define GRAPHYTE_ENDIAN_LITTLE 1
#else
#undef GRAPHYTE_ENDIAN_BIG
#define GRAPHYTE_ENDIAN_BIG 1
#endif
#else
#undef GRAPHYTE_ENDIAN_LITTLE
#define GRAPHYTE_ENDIAN_LITTLE 1
#endif


// =================================================================================================
//
// Detect platform
//


#if defined(_WIN32) || defined(_WIN64)
// Try to include winapi family
#if defined(_MSC_VER) && (_MSC_VER >= 1700)
#include <winapifamily.h>
#endif

#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#undef GRAPHYTE_PLATFORM_WINDOWS
#define GRAPHYTE_PLATFORM_WINDOWS 1
#else
#undef GRAPHYTE_PLATFORM_UWP
#define GRAPHYTE_PLATFORM_UWP 1
#endif
#elif defined(__ANDROID__)
#undef GRAPHYTE_PLATFORM_ANDROID
#define GRAPHYTE_PLATFORM_ANDROID 1
#elif defined(__STEAMLINK__)
#undef GRAPHYTE_PLATFORM_STEAMLINK
#define GRAPHYTE_PLATFORM_STEAMLINK 1
#elif defined(__VCCOREVER__)
#undef GRAPHYTE_PLATFORM_RPI
#define GRAPHYTE_PLATFORM_RPI 1
#elif defined(__linux__)
#undef GRAPHYTE_PLATFORM_LINUX
#define GRAPHYTE_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__)
#undef GRAPHYTE_PLATFORM_IOS
#define GRAPHYTE_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#undef GRAPHYTE_PLATFORM_OSX
#define GRAPHYTE_PLATFORM_OSX __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#elif defined(__EMSCRIPTEN__)
#undef GRAPHYTE_PLATFORM_EMSCRIPTEN
#define GRAPHYTE_PLATFORM_EMSCRIPTEN 1
#elif defined(__ORBIS__)
#undef GRAPHYTE_PLATFORM_PS4
#define GRAPHYTE_PLATFORM_PS4 1
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
#undef GRAPHYTE_PLATFORM_BSD
#define GRAPHYTE_PLATFORM_BSD 1
#elif defined(__NX__)
#undef GRAPHYTE_PLATFORM_NX
#define GRAPHYTE_PLATFORM_NX 1
#elif defined(_DURANGO) || defined(_XBOX_ONE)
#undef GRAPHYTE_PLATFORM_XBOXONE
#define GRAPHYTE_PLATFORM_XBOXONE 1
#else
#error "Cannot detect platform"
#endif


// =================================================================================================
//
// Detect platform type.
//

#if GRAPHYTE_PLATFORM_ANDROID || GRAPHYTE_PLATFORM_IOS
#undef GRAPHYTE_PLATFORM_TYPE_MOBILE
#define GRAPHYTE_PLATFORM_TYPE_MOBILE 1
#endif


#if GRAPHYTE_PLATFORM_BSD || GRAPHYTE_PLATFORM_LINUX || GRAPHYTE_PLATFORM_OSX || GRAPHYTE_PLATFORM_WINDOWS
#undef GRAPHYTE_PLATFORM_TYPE_DESKTOP
#define GRAPHYTE_PLATFORM_TYPE_DESKTOP 1
#endif

#if GRAPHYTE_PLATFORM_EMSCRIPTEN || GRAPHYTE_PLATFORM_RPI || GRAPHYTE_PLATFORM_UWP
#undef GRAPHYTE_PLATFORM_TYPE_HYBRID
#define GRAPHYTE_PLATFORM_TYPE_HYBRID 1
#endif

#if GRAPHYTE_PLATFORM_NX || GRAPHYTE_PLATFORM_PS4 || GRAPHYTE_PLATFORM_STEAMLINK || GRAPHYTE_PLATFORM_XBOXONE
#undef GRAPHYTE_PLATFORM_TYPE_CONSOLE
#define GRAPHYTE_PLATFORM_TYPE_CONSOLE 1
#endif


// =================================================================================================
//
// Detect if platform is posix compatible
//

#define GRAPHYTE_PLATFORM_POSIX (0 \
                                 || GRAPHYTE_PLATFORM_ANDROID \
                                 || GRAPHYTE_PLATFORM_BSD \
                                 || GRAPHYTE_PLATFORM_EMSCRIPTEN \
                                 || GRAPHYTE_PLATFORM_IOS \
                                 || GRAPHYTE_PLATFORM_LINUX \
                                 || GRAPHYTE_PLATFORM_NX \
                                 || GRAPHYTE_PLATFORM_OSX \
                                 || GRAPHYTE_PLATFORM_PS4 \
                                 || GRAPHYTE_PLATFORM_RPI \
                                 || GRAPHYTE_PLATFORM_STEAMLINK)


// =================================================================================================
//
// Detect if we support pthreads
//

#define GRAPHYTE_HAVE_PTHREADS (0 \
                                || GRAPHYTE_PLATFORM_ANDROID \
                                || GRAPHYTE_PLATFORM_BSD \
                                || GRAPHYTE_PLATFORM_EMSCRIPTEN \
                                || GRAPHYTE_PLATFORM_IOS \
                                || GRAPHYTE_PLATFORM_LINUX \
                                || GRAPHYTE_PLATFORM_OSX \
                                || GRAPHYTE_PLATFORM_RPI \
                                || GRAPHYTE_PLATFORM_STEAMLINK)


// =================================================================================================
//
// Detect CRT
//

#if !GRAPHYTE_CRT_NONE
#if defined(__BIONIC__)
#undef GRAPHYTE_CRT_BIONIC
#define GRAPHYTE_CRT_BIONIC 1
#elif defined(_MSC_VER)
#undef GRAPHYTE_CRT_MSVC
#define GRAPHYTE_CRT_MSVC 1
#elif defined(__GLIBC__)
#undef GRAPHYTE_CRT_GLIBC
#define GRAPHYTE_CRT_GLIBC (__GLIBC__ * 10000 + __GLIBC_MINOR__ * 100)
#elif defined(__MINGW32__) || defined(__MINGW64__)
#undef GRAPHYTE_CRT_MINGW
#define GRAPHYTE_CRT_MINGW 1
#elif defined(__apple_build_version__) || defined(__ORBIS__) || defined(__EMSCRIPTEN__) || defined(__llvm__)
#undef GRAPHYTE_CRT_LIBCXX
#define GRAPHYTE_CRT_LIBCXX 1
#else
#undef GRAPHYTE_CRT_NONE
#define GRAPHYTE_CRT_NONE 1
#endif
#endif


// =================================================================================================
//
// Detect compiler name
//

#if GRAPHYTE_COMPILER_MSVC
#if GRAPHYTE_COMPILER_MSVC >= 1920 // Visual Studio 2019
#define GRAPHYTE_COMPILER_NAME "MSVC 16.0"
#elif GRAPHYTE_COMPILER_MSVC >= 1910 // Visual Studio 2017
#define GRAPHYTE_COMPILER_NAME "MSVC 15.0"
#elif GRAPHYTE_COMPILER_MSVC >= 1900 // Visual Studio 2015
#define GRAPHYTE_COMPILER_NAME "MSVC 14.0"
#elif GRAPHYTE_COMPILER_MSVC >= 1800 // Visual Studio 2013
#define GRAPHYTE_COMPILER_NAME "MSVC 12.0"
#elif GRAPHYTE_COMPILER_MSVC >= 1700 // Visual Studio 2012
#define GRAPHYTE_COMPILER_NAME "MSVC 11.0"
#elif GRAPHYTE_COMPILER_MSVC >= 1600 // Visual Studio 2010
#define GRAPHYTE_COMPILER_NAME "MSVC 10.0"
#elif GRAPHYTE_COMPILER_MSVC >= 1500 // Visual Studio 2008
#define GRAPHYTE_COMPILER_NAME "MSVC 9.0"
#else
#define GRAPHYTE_COMPILER_NAME "MSVC"
#endif
#elif GRAPHYTE_COMPILER_CLANG
#define GRAPHYTE_COMPILER_NAME "Clang " GX_TOKEN_STRING(__clang_major__) "." GX_TOKEN_STRING(__clang_minor__) "." GX_TOKEN_STRING(__clang_patchlevel__)
#elif GRAPHYTE_COMPILER_GCC
#define GRAPHYTE_COMPILER_NAME "GCC " GX_TOKEN_STRING(__GNUC__) "." GX_TOKEN_STRING(__GNUC_MINOR__) "." GX_TOKEN_STRING(__GNUC_PATCHLEVEL__)
#endif


// =================================================================================================
//
// Detect platform name
//

#if GRAPHYTE_PLATFORM_ANDROID
#define GRAPHYTE_PLATFORM_NAME "Android " GX_TOKEN_STRING(GRAPHYTE_PLATFORM_ANDROID)
#elif GRAPHYTE_PLATFORM_BSD
#define GRAPHYTE_PLATFORM_NAME "BSD"
#elif GRAPHYTE_PLATFORM_EMSCRIPTEN
#define GRAPHYTE_PLATFORM_NAME "asm.js " GX_TOKEN_STRING(__EMSCRIPTEN_major__) "." GX_TOKEN_STRING(__EMSCRIPTEN_minor__) "." GX_TOKEN_STRING(__EMSCRIPTEN_tiny__)
#elif GRAPHYTE_PLATFORM_IOS
#define GRAPHYTE_PLATFORM_NAME "iOS"
#elif GRAPHYTE_PLATFORM_LINUX
#define GRAPHYTE_PLATFORM_NAME "Linux"
#elif GRAPHYTE_PLATFORM_NX
#define GRAPHYTE_PLATFORM_NAME "NX"
#elif GRAPHYTE_PLATFORM_OSX
#define GRAPHYTE_PLATFORM_NAME "OSX"
#elif GRAPHYTE_PLATFORM_PS4
#define GRAPHYTE_PLATFORM_NAME "PlayStation 4"
#elif GRAPHYTE_PLATFORM_RPI
#define GRAPHYTE_PLATFORM_NAME "Raspberry PI"
#elif GRAPHYTE_PLATFORM_STEAMLINK
#define GRAPHYTE_PLATFORM_NAME "SteamLink"
#elif GRAPHYTE_PLATFORM_WINDOWS
#define GRAPHYTE_PLATFORM_NAME "Windows"
#elif GRAPHYTE_PLATFORM_UWP
#define GRAPHYTE_PLATFORM_NAME "UWP"
#elif GRAPHYTE_PLATFORM_XBOXONE
#define GRAPHYTE_PLATFORM_NAME "Xbox One"
#endif


// =================================================================================================
//
// Detect CPU name
//

#if GRAPHYTE_CPU_ARM_64
#define GRAPHYTE_CPU_NAME "ARM64"
#elif GRAPHYTE_CPU_ARM_32
#define GRAPHYTE_CPU_NAME "ARM"
#elif GRAPHYTE_CPU_X86_32
#define GRAPHYTE_CPU_NAME "X86-32"
#elif GRAPHYTE_CPU_X86_64
#define GRAPHYTE_CPU_NAME "X86-64"
#elif GRAPHYTE_CPU_MIPS_32
#define GRAPHYTE_CPU_NAME "MIPS"
#elif GRAPHYTE_CPU_MIPS_64
#define GRAPHYTE_CPU_NAME "MIPS64"
#elif GRAPHYTE_CPU_PPC_32
#define GRAPHYTE_CPU_NAME "PowerPC"
#elif GRAPHYTE_CPU_PPC_64
#define GRAPHYTE_CPU_NAME "PowerPC64"
#elif GRAPHYTE_CPU_RISCV_32
#define GRAPHYTE_CPU_NAME "RISC-V-32"
#elif GRAPHYTE_CPU_RISCV_64
#define GRAPHYTE_CPU_NAME "RISC-V-64"
#elif GRAPHYTE_CPU_RISCV_128
#define GRAPHYTE_CPU_NAME "RISC-V-128"
#endif


// =================================================================================================
//
// Detect bitness name
//

#if GRAPHYTE_ARCH_32BIT
#define GRAPHYTE_ARCH_NAME "32-bit"
#elif GRAPHYTE_ARCH_64BIT
#define GRAPHYTE_ARCH_NAME "64-bit"
#elif GRAPHYTE_ARCH_128BIT
#define GRAPHYTE_ARCH_NAME "128-bit"
#endif


// =================================================================================================
//
// Detect CRT name
//

#if GRAPHYTE_CRT_MSVC
#define GRAPHYTE_CRT_NAME "MSVC C Runtime"
#elif GRAPHYTE_CRT_MINGW
#define GRAPHYTE_CRT_NAME "MinGW C Runtime"
#elif GRAPHYTE_CRT_GLIBC
#define GRAPHYTE_CRT_NAME "GNU C Library"
#elif GRAPHYTE_CRT_NEWLIB
#define GRAPHYTE_CRT_NAME "newlib"
#elif GRAPHYTE_CRT_BIONIC
#define GRAPHYTE_CRT_NAME "Bionic libc"
#elif GRAPHYTE_CRT_MUSL
#define GRAPHYTE_CRT_NAME "musl libc"
#elif GRAPHYTE_CRT_LIBCXX
#define GRAPHYTE_CRT_NAME "Clang C library"
#elif GRAPHYTE_CRT_NONE
#define GRAPHYTE_CRT_NAME "none"
#endif


// =================================================================================================
//
// Detect compiler features
//

#if (GRAPHYTE_COMPILER_MSVC || GRAPHYTE_COMPILER_CLANG) && (GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_XBOXONE || GRAPHYTE_PLATFORM_UWP)
#undef GRAPHYTE_HAVE_VECTORCALL
#define GRAPHYTE_HAVE_VECTORCALL 1
#endif

#if GRAPHYTE_COMPILER_MSVC
#undef GRAPHYTE_MATH_SVML
#define GRAPHYTE_MATH_SVML 1
#endif

#if GRAPHYTE_COMPILER_MSVC && (GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_XBOXONE || GRAPHYTE_PLATFORM_UWP)
#define GRAPHYTE_PLATFORM_HAVE_SEH_EXCEPTIONS 1
#else
#define GRAPHYTE_PLATFORM_HAVE_SEH_EXCEPTIONS 0
#endif


// =================================================================================================
//
// Detect CPU properties
//

#if GRAPHYTE_CPU_ARM_64 || GRAPHYTE_CPU_X86_64 || GRAPHYTE_CPU_X86_32
#undef GRAPHYTE_UNALIGNED_ACCESS
#define GRAPHYTE_UNALIGNED_ACCESS 1
#endif

#if defined(__AVX__)
#undef GRAPHYTE_HW_AVX
#define GRAPHYTE_HW_AVX 1
#endif

#if defined(__AVX2__)
#undef GRAPHYTE_HW_AVX2
#define GRAPHYTE_HW_AVX2 1
#endif

#if defined(__SSE__) || defined(_M_X64) || (_M_IX86_FP >= 1)
#undef GRAPHYTE_HW_SSE
#define GRAPHYTE_HW_SSE 1
#endif

#if defined(__SSE2__) || defined(_M_X64) || (_M_IX86_FP >= 2)
#undef GRAPHYTE_HW_SSE2
#define GRAPHYTE_HW_SSE2 1
#endif

#if defined(__F16C__) || defined(__AVX2__)
#undef GRAPHYTE_HW_F16C
#define GRAPHYTE_HW_F16C 1
#endif

#if defined(__FMA__) || defined(__AVX2__)
#undef GRAPHYTE_HW_FMA3
#define GRAPHYTE_HW_FMA3 1
#endif

#if defined(__AESNI__) || defined(__AVX2__)
#undef GRAPHYTE_HW_AESNI
#define GRAPHYTE_HW_AESNI 1
#endif

#if defined(__SHA__) || defined(__AVX2__)
#undef GRAPHYTE_HW_SHA
#define GRAPHYTE_HW_SHA 1
#endif

#if defined(__FMA4__)
#undef GRAPHYTE_HW_FMA4
#define GRAPHYTE_HW_FMA4 1
#endif

#if defined(__ARM_NEON__) || defined(__aarch64__) || defined(_M_ARM) || defined(_M_ARM64)
#undef GRAPHYTE_HW_NEON
#define GRAPHYTE_HW_NEON 1
#endif

#if defined(__VECTOR4DOUBLE__)
#undef GRAPHYTE_HW_QPX
#define GRAPHYTE_HW_QPX 1
#endif

#if defined(__ALTIVEC__) || defined(__VEC__)
#undef GRAPHYTE_HW_VMX
#define GRAPHYTE_HW_VMX 1
#endif

#if defined(__VSX__)
#undef GRAPHYTE_HW_VSX
#define GRAPHYTE_HW_VSX 1
#endif


// =================================================================================================
//
// Configuration type detection.
//

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
//
// Build type
//

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
//
// Asserts configuration
//

#if GX_BUILD_TYPE_RETAIL
#define GRAPHYTE_CONFIG_DO_ASSERT 0
#define GRAPHYTE_CONFIG_DO_VERIFY 0
#define GRAPHYTE_CONFIG_DO_ENSURE 0
#endif

#if !defined(GRAPHYTE_CONFIG_DO_ASSERT)
#define GRAPHYTE_CONFIG_DO_ASSERT 1
#endif

#if !defined(GRAPHYTE_CONFIG_DO_VERIFY)
#define GRAPHYTE_CONFIG_DO_VERIFY 1
#endif

#if !defined(GRAPHYTE_CONFIG_DO_ENSURE)
#define GRAPHYTE_CONFIG_DO_ENSURE 1
#endif


// =================================================================================================
//
// Configure build options
//

#if GX_BUILD_TYPE_RETAIL
#define GX_STATIC_BUILD 0 // requires more support from fastbuild right now :(
#else
#define GX_STATIC_BUILD 0
#endif

#if !defined(GRAPHYTE_MATH_NO_INTRINSICS)
#define GRAPHYTE_MATH_NO_INTRINSICS 0
#endif

#if !defined(GRAPHYTE_MATH_SVML)
#define GRAPHYTE_MATH_SVML 0
#endif

#if !defined(GRAPHYTE_MATH_FAST_FUNCTIONS)
#define GRAPHYTE_MATH_FAST_FUNCTIONS 1
#endif

#if !defined(GRAPHYTE_MATH_ENABLE_OPERATORS)
#define GRAPHYTE_MATH_ENABLE_OPERATORS 1
#endif

#if !defined(GRAPHYTE_PLATFORM_HAS_TOUCH_SCREEN)
#define GRAPHYTE_PLATFORM_HAS_TOUCH_SCREEN 0
#endif

#if !defined(GRAPHYTE_ENABLE_DEBUG_RENDER)
#define GRAPHYTE_ENABLE_DEBUG_RENDER 1
#endif

#if !defined(GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS)
#define GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS 1
#endif

#if !defined(GRAPHYTE_ENABLE_STACKTRACE_FAST)
#define GRAPHYTE_ENABLE_STACKTRACE_FAST 1
#endif


// =================================================================================================
//
// Profiler
//

#define GRAPHYTE_ENABLE_PROFILE 0

// Update inline depth
#if defined(_MSC_VER)
#pragma inline_depth(255)
#endif


// =================================================================================================
//
// Noinline attribute.
//

#if defined(_MSC_VER)
#define GX_NOINLINE __declspec(noinline)
#else
#define GX_NOINLINE __attribute__((__noinline__))
#endif


// =================================================================================================
//
// Forceinline attribute.
//

#if !(defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__))
#define __forceinline inline __attribute__((always_inline))
#endif


// =================================================================================================
//
// Unreachable declarator.
//

#if defined(_MSC_VER)
#define GX_DECLARE_UNREACHABLE()
#else
#define GX_DECLARE_UNREACHABLE() __builtin_unreachable()
#endif


// =================================================================================================
//
// Assume
//

#if defined(_MSC_VER)
#define GX_COMPILER_ASSUME(expression) __analysis_assume(!!(expression))
#else
#define GX_COMPILER_ASSUME(expression)
#endif


// =================================================================================================
//
// Debugger break.
//

#if defined(_MSC_VER)
#define GX_DEBUG_BREAK __debugbreak
#elif defined(__GNUC__)
#define GX_DEBUG_BREAK __builtin_trap
#else
#define GX_DEBUG_BREAK __builtin_debugtrap
#endif


// =================================================================================================
//
// Export / import.
//

#if defined(_MSC_VER)
#define GX_LIB_EXPORT __declspec(dllexport)
#define GX_LIB_IMPORT __declspec(dllimport)
#elif defined(__CYGWIN__) && defined(__GNUC__)
#define GX_LIB_EXPORT __attribute__((__dllexport__))
#define GX_LIB_IMPORT __attribute__((__dllimport__))
#else
#define GX_LIB_EXPORT __attribute__((visibility("default")))
#define GX_LIB_IMPORT __attribute__((visibility("default")))
#endif


// =================================================================================================
//
// Likely / unlikely.
//

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
//
// Platform specific headers
//

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#include <GxBase/Platform/Impl/Headers.Windows.hxx>
#elif GRAPHYTE_PLATFORM_LINUX
#include <GxBase/Platform/Impl/Headers.Linux.hxx>
#elif GRAPHYTE_PLATFORM_ANDROID
#include <GxBase/Platform/Impl/Headers.Android.hxx>
#else
#error "Unsupported platform"
#endif


// =================================================================================================
//
// Disable compiler warnings
//

#if GRAPHYTE_COMPILER_MSVC
#include <GxBase/Platform/Impl/CompilerWarnings.msvc.hxx>
#elif GRAPHYTE_COMPILER_CLANG
#include <GxBase/Platform/Impl/CompilerWarnings.clang.hxx>
#elif GRAPHYTE_COMPILER_GCC
#include <GxBase/Platform/Impl/CompilerWarnings.gcc.hxx>
#endif


// =================================================================================================
//
// Enable / Disable optimizations macros
//

#if GRAPHYTE_COMPILER_MSVC

#define GX_OPTIMIZE_ENABLE  __pragma(optimize("", on))
#define GX_OPTIMIZE_DISABLE __pragma(optimize("", off))

#elif GRAPHYTE_COMPILER_CLANG

#define GX_OPTIMIZE_ENABLE  _Pragma("clang optimize on")
#define GX_OPTIMIZE_DISABLE _Pragma("clang optimize off")

#elif GRAPHYTE_COMPILER_GCC

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
//
// Validate minimum required version
//

#if GRAPHYTE_COMPILER_MSVC
#if _MSC_VER < 1925
#error "MSVC version not supported"
#endif
#endif

#if GRAPHYTE_COMPILER_CLANG
#if __clang_major__ < 10
#error "Clang version not supported"
#endif
#endif


// =================================================================================================
//
// Enable bit operations for specified enum type.
//

#define GX_ENUM_CLASS_FLAGS(enum_type) \
    inline enum_type& operator|=(enum_type& lhs, const enum_type rhs) noexcept { return lhs = static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) | static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline enum_type& operator&=(enum_type& lhs, const enum_type rhs) noexcept { return lhs = static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) & static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline enum_type& operator^=(enum_type& lhs, const enum_type rhs) noexcept { return lhs = static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) & static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline constexpr enum_type operator|(const enum_type lhs, const enum_type rhs) noexcept { return static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) | static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline constexpr enum_type operator&(const enum_type lhs, const enum_type rhs) noexcept { return static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) & static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline constexpr enum_type operator^(const enum_type lhs, const enum_type rhs) noexcept { return static_cast<enum_type>(static_cast<std::underlying_type_t<enum_type>>(lhs) ^ static_cast<std::underlying_type_t<enum_type>>(rhs)); } \
    inline constexpr bool operator!(const enum_type value) noexcept { return !static_cast<std::underlying_type_t<enum_type>>(value); } \
    inline constexpr enum_type operator~(const enum_type value) noexcept { return static_cast<enum_type>(~static_cast<std::underlying_type_t<enum_type>>(value)); }


#define GRAPHYTE_SDKS_WITH_ZLIB 0
