#include "Base.pch.hxx"
#include <Graphyte/System.hxx>
#include <Graphyte/String.hxx>

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
        Impl::GPlatformFeatureSet.Set(PlatformFeature::SeparateDebugOutput, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::VirtualJoystick, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::VirtualKeyboard, false);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::RequiresCookedData, true);
        Impl::GPlatformFeatureSet.Set(PlatformFeature::RequiresUserCredenials, false);

        //
        // Gather memory properties.
        //

        {
            struct sysinfo info {};
            sysinfo(&info);

            Impl::GMemoryProperties.TotalPhysical = info.mem_unit * info.totalram;
            Impl::GMemoryProperties.TotalVirtual = info.mem_unit * info.totalswap;
            Impl::GMemoryProperties.TotalPagefile = info.mem_unit * info.totalswap;
            Impl::GMemoryProperties.PageSize = static_cast<uint64_t>(sysconf(_SC_PAGE_SIZE));
            Impl::GMemoryProperties.SystemAllocationGranularity = Impl::GMemoryProperties.PageSize * 16;

            struct rlimit64 limits {};
            getrlimit64(RLIMIT_AS, &limits);
            Impl::GMemoryProperties.AddressLimit = limits.rlim_cur;
        }


        //
        // Processor information.
        //

        {
            Impl::GLogicalCores = static_cast<size_t>(SDL_GetCPUCount());
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

                auto key = Trim(values[0]);
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
                Impl::GPhysicalCores = Impl::GLogicalCores;
            }
            else
            {
                Impl::GPhysicalCores = std::size(cores);
            }
        }


        //
        // Set worker threads count.
        //

        Impl::GWorkerThreads = Impl::GLogicalCores;
    }
}
