#pragma once

//
// POSIX
//
#include <unistd.h>
#include <sys/endian.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <errno.h>
#include <semaphore.h>
#include <netdb.h>

//
// NEON Support for ARM.
//
#if defined(__ARM_NEON__) || defined(__aarch64__)
#include <arm_neon.h> // For all ARMS but not for TEGRA/ATOM
#else
#include <xmmintrin.h>
#include <mmintrin.h>
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
#include <optional>
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
