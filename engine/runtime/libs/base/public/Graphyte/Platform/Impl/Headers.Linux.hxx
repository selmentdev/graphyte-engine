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
// NEON Support for ARM.
//
#if defined(__aarch64__) || defined(__arm__)

#include <arm_neon.h> // For all ARMS but not for TEGRA/ATOM

#elif defined(__x86_64__) || defined(__i386__)

#include <immintrin.h>
#include <mmintrin.h>
#include <smmintrin.h>
#include <x86intrin.h>
#include <xmmintrin.h>

#else

#error Unknown target architecture.

#endif

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

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
