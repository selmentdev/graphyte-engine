#include <GxBase/System.hxx>
#include <GxBase/String.hxx>

#include "../Platform.impl.hxx"

#include <fstream>

#include <sys/sysinfo.h>
#include <sys/resource.h>

#include <SDL2/SDL.h>

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
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::SeparateDebugOutput, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::VirtualJoystick, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::VirtualKeyboard, false);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::RequiresCookedData, true);
        Impl::g_PlatformFeatureSet.Set(PlatformFeature::RequiresUserCredenials, false);

        //
        // Gather memory properties.
        //

        {
            // clang-format off
            struct sysinfo info{};
            sysinfo(&info);
            // clang-format on

            Impl::g_MemoryProperties.TotalPhysical               = info.mem_unit * info.totalram;
            Impl::g_MemoryProperties.TotalVirtual                = info.mem_unit * info.totalswap;
            Impl::g_MemoryProperties.TotalPagefile               = info.mem_unit * info.totalswap;
            Impl::g_MemoryProperties.PageSize                    = static_cast<uint64_t>(sysconf(_SC_PAGE_SIZE));
            Impl::g_MemoryProperties.SystemAllocationGranularity = Impl::g_MemoryProperties.PageSize * 16;

            // clang-format off
            struct rlimit64 limits{};
            // clang-format on
            getrlimit64(RLIMIT_AS, &limits);
            Impl::g_MemoryProperties.AddressLimit = limits.rlim_cur;
        }


        //
        // Processor information.
        //

        {
            Impl::g_LogicalCores = static_cast<size_t>(SDL_GetCPUCount());
        }


        //
        // Compute number of physical cores.
        //

        {
            using CoreInfo = std::pair<uint32_t, uint32_t>;

            std::ifstream procinfo{ "/proc/cpuinfo" };
            std::set<CoreInfo> cores{};

            CoreInfo current{};

            std::string line{};
            while (std::getline(procinfo, line))
            {
                if (line.empty())
                {
                    continue;
                }

                auto values = Split(line, ':', false);

                if (std::size(values) != 2)
                {
                    break;
                }

                auto key   = Trim(values[0]);
                auto value = Trim(values[1]);

                if (key == "physical id")
                {
                    Converter<uint32_t>::FromString(current.first, value);
                    continue;
                }

                if (key == "core id")
                {
                    Converter<uint32_t>::FromString(current.second, value);
                    cores.insert(current);
                    continue;
                }
            }

            if (cores.empty())
            {
                Impl::g_PhysicalCores = Impl::g_LogicalCores;
            }
            else
            {
                Impl::g_PhysicalCores = std::size(cores);
            }
        }


        //
        // Set worker threads count.
        //

        Impl::g_WorkerThreads = Impl::g_LogicalCores;
    }
}
