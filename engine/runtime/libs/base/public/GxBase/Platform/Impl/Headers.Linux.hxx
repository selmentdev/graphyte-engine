#pragma once

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif

//
// POSIX
//
#include <arpa/inet.h>
#include <endian.h>
#include <errno.h>
#include <execinfo.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/user.h>
#include <ucontext.h>
#include <unistd.h>
#include <utime.h>


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
#include <string_view>
#include <atomic>
#include <charconv>
#include <functional>

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
// SIMD support
//

#if GRAPHYTE_HW_AVX
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

#if GRAPHYTE_HW_AESNI
#include <wmmintrin.h>
#endif

#if GRAPHYTE_HW_NEON
#include <arm_neon.h>
#endif


#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
