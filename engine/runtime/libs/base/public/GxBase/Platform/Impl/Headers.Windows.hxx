#pragma once

//
// Strip system headers from unused symbols.
//


#define NOATOM 1
//#define NOCLIPBOARD 1
//#define NOCOLOR 1
#define NOCOMM 1
//#define NOCTLMGR 1
#define NODEFERWINDOWPOS 1
#define NODRAWTEXT       1
//#define NOGDI 1
#define NOGDICAPMASKS 1
#define NOHELP        1
//#define NOICONS 1
#define NOIMAGE  1
#define NOKANJI  1
#define NOKERNEL 1
//#define NOKEYSTATES 1
//#define NOMB 1
#define NOMCX    1
#define NOMEMMGR 1
//#define NOMENUS 1
#define NOMETAFILE 1
#define NOMINMAX   1
//#define NOMSG 1
//#define NONLS 1
#define NOOPENFILE  1
#define NOPROFILER  1
#define NOPROXYSTUB 1
#define NORASTEROPS 1
#define NORPC       1
#define NOSCROLL    1
#define NOSERVICE   1
//define NOSHOWWINDOW 1
#define NOSOUND 1
//#define NOSYSCOMMANDS 1
//#define NOSYSMETRICS 1
#define NOTAPE       1
#define NOTEXTMETRIC 1
//#define NOUSER 1
//#define NOVIRTUALKEYCODES 1
#define NOWH 1
//#define NOWINMESSAGES 1
//#define NOWINOFFSETS 1
//#define NOWINSTYLES 1
#define OEMRESOURCE 1


#define WIN32_LEAN_AND_MEAN 1
#define NOMINMAX            1

#ifndef STRICT
#define STRICT 1
#endif

#if false
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
#endif

#include <crtdbg.h>

//
// Include system configurable headers.
//
#include <SDKDDKVer.h>
#include <intrin.h>

//
// Make sure that build system properly configured headers
//
#if !defined(NTDDI_VERSION)
#error "Unknown DDI version"
#endif

#if !defined(WINVER)
#error "Unknown WINVER version"
#endif

#if !defined(_WIN32_WINNT)
#error "Unknown _WIN32_WINNT version"
#endif

#if defined(_MSC_VER) && defined(NDEBUG)
#define _SECURE_SCL        0
#define _SECURE_SCL_THROWS 0
#endif

//
// Windows headers
//
#include <Windows.h>
#include <errno.h>


//
// Remove unnecessary preprocessor macros.
//
#include <GxBase/Platform/Impl/Headers.Windows.Cleanup.hxx>

//
// Exception handling
//
#include <exception>
#include <stdexcept>

//
// STL Headers.
//
#include <algorithm>
#include <array>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <codecvt>
#include <string_view>
#include <optional>
#include <atomic>
#include <charconv>
#include <functional>
#include <bit>
#include <compare>

#if __has_include(<bit>)
#include <bit>
#endif

#if __has_include(<compare>)
#include <compare>
#endif

#if __has_include(<span>)
#include <span>
#endif

#if __has_include(<concepts>)
#include <concepts>
#endif

#if __has_include(<ranges>)
#include <ranges>
#endif

#if __has_include(<coroutines>)
#include <coroutines>
#endif

//
// C Library Headers.
//
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

//
// Format library
//

#include <fmt/format.h>


//
// MSVC Runtime Debug
//
#if defined(_MSC_VER) && !defined(NDEBUG)
// Include runtime debug headers
#include <crtdbg.h>
#endif

//
// Additional intrinsics.
//
#if defined(_MSC_VER)
#pragma intrinsic(_lrotl, _lrotr, _rotl, _rotr, _strset, abs, fabs, labs, memcmp, memcpy, memset, strcat, strcmp, strcpy, strlen)
#pragma intrinsic(acos, cosh, pow, tanh, asin, fmod, sinh)
#pragma intrinsic(atan, exp, log10, sqrt, atan2, log, sin, tan, cos)
#pragma intrinsic(_rotr8, _rotr16, _rotr, _rotr64)
#pragma intrinsic(_rotl8, _rotl16, _rotl, _rotl64)

#if defined(_M_X86) || defined(_M_X64)
#pragma intrinsic(__rdtsc)
#endif
#endif

//
// SIMD support
//

#if GX_HW_AVX
// SSE
#include <xmmintrin.h>
// SSE2
#include <emmintrin.h>
// SSE3
#include <pmmintrin.h>
// SSSE3
#include <tmmintrin.h>
// SSE4.1
#include <smmintrin.h>
// SSE4.2
#include <nmmintrin.h>
// AVX
#include <immintrin.h>
#endif

#if GX_HW_AESNI
#include <wmmintrin.h>
#endif

#if GX_HW_NEON
#if GX_CPU_ARM_32
#include <arm_neon.h>
#include <armintr.h>
#elif GX_CPU_ARM_64
#include <arm64_neon.h>
#include <arm64intr.h>
#endif
#endif

#define GX_WIN32_WIDEN__(x) L##x
#define GX_WIN32_WIDEN(x) GX_WIN32_WIDEN__(x)
