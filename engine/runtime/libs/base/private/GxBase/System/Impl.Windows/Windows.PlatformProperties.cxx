#include <GxBase/System.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System::Impl
{
    void DetectPlatformFeatures() noexcept
    {
        //
        // Specify common platform properties.
        //

        Impl::g_PlatformFeatureSet.Set(PlatformFeature::AudioStreaming, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::AudioThread, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::CallstackAssertDump, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::DeadlockWatchdog, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::DistanceFieldShadows, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::Exit, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::FastVRAMMemory, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::FramerateSmoothing, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::FullCrashDump, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::HighQualityLightmaps, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::LowQualityLightmaps, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::LocalCaching, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::Messaging, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::Minimize, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::MultipleInstances, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::Multithreading, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::RenderThread, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::ResolutionChanging, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::SystemAudioVolumeHandling, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::Tesselation, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::TextureStreaming, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::TouchInput, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::WindowedMode, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::VariableHardware, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::SeparateDebugOutput, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::VirtualJoystick, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::VirtualKeyboard, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::RequiresCookedData, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::RequiresUserCredenials, false);


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

            Impl::g_LogicalCores = si.dwNumberOfProcessors;

            Impl::g_MemoryProperties.TotalPhysical               = msex.ullTotalPhys;
            Impl::g_MemoryProperties.TotalVirtual                = msex.ullTotalVirtual;
            Impl::g_MemoryProperties.TotalPagefile               = msex.ullTotalPageFile;
            Impl::g_MemoryProperties.SystemAllocationGranularity = si.dwAllocationGranularity;
            Impl::g_MemoryProperties.PageSize                    = si.dwPageSize;
            Impl::g_MemoryProperties.AddressLimit                = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(si.lpMaximumApplicationAddress));
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

            Impl::g_PhysicalCores = cores;
        }


        //
        // Set worker threads count.
        //

        Impl::g_WorkerThreads = Impl::g_LogicalCores;
    }
}
