#include <GxBase/System.hxx>
#include "../Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API MemoryUsage GetMemoryUsage() noexcept
    {
        MEMORYSTATUSEX msex{
            .dwLength = sizeof(msex),
        };

        GlobalMemoryStatusEx(&msex);


        PROCESS_MEMORY_COUNTERS pmc{
            .cb = sizeof(pmc),
        };

        GetProcessMemoryInfo(
            GetCurrentProcess(),
            &pmc,
            sizeof(pmc));

        MemoryUsage result{
            .AvailableVirtual  = static_cast<uint64_t>(msex.ullAvailVirtual),
            .AvailablePhysical = static_cast<uint64_t>(msex.ullAvailPhys),
            .UsedVirtual       = static_cast<uint64_t>(pmc.PagefileUsage),
            .UsedPhysical      = static_cast<uint64_t>(pmc.WorkingSetSize),
            .PeakUsedVirtual   = static_cast<uint64_t>(pmc.PeakPagefileUsage),
            .PeakUsedPhysical  = static_cast<uint64_t>(pmc.PeakWorkingSetSize),
        };

        return result;
    }

    BASE_API MemoryProperties GetMemoryProperties() noexcept
    {
        return Impl::GMemoryProperties;
    }
}

namespace Graphyte::System
{
    BASE_API void* OsMalloc(
        size_t size) noexcept
    {
        return malloc(size);
    }

    BASE_API void* OsRealloc(
        void* memory,
        size_t size) noexcept
    {
        return realloc(memory, size);
    }

    BASE_API void OsFree(
        void* memory) noexcept
    {
        free(memory);
    }

    BASE_API void* OsVirtualAlloc(
        size_t size) noexcept
    {
        //Platform::MemoryTracker::Track(Platform::MemoryPoolTag::Virtual, size);
        return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    }

    BASE_API void OsVirtualFree(
        void* memory,
        [[maybe_unused]] size_t size) noexcept
    {
        //Platform::MemoryTracker::Untrack(Platform::MemoryPoolTag::Virtual, size);
        if (VirtualFree(memory, 0, MEM_RELEASE) == FALSE)
        {
            GX_ASSERTF(false, "Failed to free virtual memory (pointer: {}, size: {})", memory, size);
        }
    }

    BASE_API bool OsVirtualProtect(
        void* memory,
        size_t size,
        bool canRead,
        bool canWrite) noexcept
    {
        DWORD dwNewProtect = 0;

        if (canRead && canWrite)
        {
            dwNewProtect = PAGE_READWRITE;
        }
        else if (canWrite)
        {
            dwNewProtect = PAGE_READWRITE;
        }
        else if (canRead)
        {
            dwNewProtect = PAGE_READONLY;
        }
        else
        {
            dwNewProtect = PAGE_NOACCESS;
        }

        [[maybe_unused]] DWORD dwOldProtect = 0;

        return VirtualProtect(memory, size, dwNewProtect, &dwOldProtect) != 0;
    }
}
