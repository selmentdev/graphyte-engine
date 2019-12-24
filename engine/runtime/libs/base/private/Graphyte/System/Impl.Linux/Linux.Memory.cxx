#include "Base.pch.hxx"
#include <Graphyte/System.hxx>
#include "../Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API MemoryUsage GetMemoryUsage() noexcept
    {
        MemoryUsage result{};

        char path[32];
        sprintf(path, "/proc/%u/status", static_cast<uint32_t>(getpid()));

        if (FILE* f = fopen(path, "r"); f != nullptr)
        {
            char line[256];
            unsigned long value{};

            while (fgets(line, sizeof(line), f))
            {
                if (sscanf(line, "VmHWM: %lu", &value) == 1)
                {
                    result.PeakUsedPhysical = static_cast<uint64_t>(value * 1024);
                }
                else if (sscanf(line, "VmRSS: %lu", &value) == 1)
                {
                    result.UsedPhysical = static_cast<uint64_t>(value * 1024);
                }
                else if (sscanf(line, "RssAnon: %lu", &value) == 1)
                {
                    result.UsedVirtual += static_cast<uint64_t>(value * 1024);
                }
                else if (sscanf(line, "VmSwap: %lu", &value) == 1)
                {
                    result.UsedVirtual += static_cast<uint64_t>(value * 1024);
                }
            }

            result.PeakUsedVirtual = result.UsedVirtual;

            fclose(f);
        }

        if (FILE* f = fopen("/proc/meminfo", "r"); f != nullptr)
        {
            char line[256];
            unsigned long value{};

            while (fgets(line, sizeof(line), f))
            {
                if (sscanf(line, "MemFree: %lu", &value) == 1)
                {
                    result.AvailablePhysical = static_cast<uint64_t>(value * 1024);
                }
                else if (sscanf(line, "Buffers: %lu", &value) == 1)
                {
                    result.AvailablePhysical += static_cast<uint64_t>(value * 1024);
                }
                else if (sscanf(line, "Cached: %lu", &value) == 1)
                {
                    result.AvailablePhysical += static_cast<uint64_t>(value * 1024);
                }
            }

            fclose(f);
        }

        result.AvailableVirtual = (~static_cast<uintptr_t>(0)) - result.UsedVirtual;


        return result;
    }

    BASE_API MemoryProperties GetMemoryProperties() noexcept
    {
        return Impl::GMemoryProperties;
    }
}

namespace Graphyte::Platform
{
    BASE_API void* OsMalloc(
        size_t size
    ) noexcept
    {
        return malloc(size);
    }

    BASE_API void* OsRealloc(
        void* memory,
        size_t size
    ) noexcept
    {
        return realloc(memory, size);
    }

    BASE_API void OsFree(
        void* memory
    ) noexcept
    {
        free(memory);
    }

    BASE_API void* OsVirtualAlloc(
        size_t size
    ) noexcept
    {
        auto memory = mmap(
            nullptr,
            size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS,
            -1,
            0
        );

        return memory;
    }

    BASE_API void OsVirtualFree(
        void* memory,
        size_t size
    ) noexcept
    {
        if (memory != nullptr && munmap(memory, size) != 0)
        {
            [[maybe_unused]] const auto error = errno;

            GX_LOG(LogPlatform, Error,
                "munmap(address = {}, size = {}) failed with errno {} ({})",
                memory,
                size,
                error,
                strerror(error)
            );
        }
    }

    BASE_API bool OsVirtualProtect(
        void* memory,
        size_t size,
        bool canRead,
        bool canWrite
    ) noexcept
    {
        int protectMode = PROT_NONE;

        if (canRead && canWrite)
        {
            protectMode = PROT_READ | PROT_WRITE;
        }
        else if (canRead)
        {
            protectMode = PROT_READ;
        }
        else if (canWrite)
        {
            protectMode = PROT_WRITE;
        }

        return mprotect(memory, size, protectMode) == 0;
    }
}
