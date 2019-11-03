#include "Base.pch.hxx"
#include <Graphyte/System.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System::Impl
{
    void DetectPlatformFeatures() noexcept
    {
        //
        // Specify common platform properties.
        //

        Impl::GPlatformFeatureSet.Set(PlatformFeature::AudioStreaming, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::AudioThread, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::CallstackAssertDump, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::DeadlockWatchdog, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::DistanceFieldShadows, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::Exit, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::FastVRAMMemory, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::FramerateSmoothing, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::FullCrashDump, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::HighQualityLightmaps, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::LowQualityLightmaps, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::LocalCaching, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::Messaging, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::Minimize, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::MultipleInstances, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::Multithreading, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::RenderThread, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::ResolutionChanging, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::SystemAudioVolumeHandling, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::Tesselation, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::TextureStreaming, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::TouchInput, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::WindowedMode, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::VariableHardware, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::SeparateDebugOutput, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::VirtualJoystick, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::VirtualKeyboard, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::RequiresCookedData, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::RequiresUserCredenials, false);


        //
        // Get memory properties.
        //
        //

        {
            MEMORYSTATUSEX msex{
                .dwLength = sizeof(msex),
            };

            GlobalMemoryStatusEx(&msex);

            SYSTEM_INFO si{};

            if (Graphyte::System::Is64BitOperatingSystem())
            {
                GetNativeSystemInfo(&si);
            }
            else
            {
                GetSystemInfo(&si);
            }

            Impl::GLogicalCores = si.dwNumberOfProcessors;

            Impl::GMemoryProperties.TotalPhysical = msex.ullTotalPhys;
            Impl::GMemoryProperties.TotalVirtual = msex.ullTotalVirtual;
            Impl::GMemoryProperties.TotalPagefile = msex.ullTotalPageFile;
            Impl::GMemoryProperties.SystemAllocationGranularity = si.dwAllocationGranularity;
            Impl::GMemoryProperties.PageSize = si.dwPageSize;
            Impl::GMemoryProperties.AddressLimit = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(si.lpMaximumApplicationAddress));
        }


        //
        // Get physical cores info.
        //

        {
            size_t cores{};
            DWORD dwSize{};


            //
            // Get how much data is required to be allocated.
            //

            if (GetLogicalProcessorInformation(nullptr, &dwSize) != FALSE)
            {
                GX_ASSERTF(false, "Cannot acquire logical CPU information");
            }

            GX_ASSERT(GetLastError() == ERROR_INSUFFICIENT_BUFFER);


            //
            // Allocate that data.
            //

            auto* data = reinterpret_cast<SYSTEM_LOGICAL_PROCESSOR_INFORMATION*>(System::OsMalloc(dwSize));

            GX_ASSERT(data != nullptr);


            //
            // Get actual data.
            //

            if (GetLogicalProcessorInformation(data, &dwSize) == FALSE)
            {
                GX_ASSERTF(false, "Cannot acquire logical CPU information");
            }

            size_t const count = dwSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);

            for (size_t i = 0; i < count; ++i)
            {
                auto* current = &data[i];

                if (current->Relationship == RelationProcessorCore)
                {
                    ++cores;
                }
            }

            System::OsFree(data);

            Impl::GPhysicalCores = cores;
        }


        //
        // Set worker threads count.
        //

        Impl::GWorkerThreads = Impl::GLogicalCores;
    }
}
