#include "Platform.impl.hxx"
#include <GxBase/CommandLine.hxx>

#if GRAPHYTE_CPU_X86_32 || GRAPHYTE_CPU_X86_64
#include "Impl/ProcessorFeatures.x86.hxx"
#elif GRAPHYTE_CPU_ARM_32 || GRAPHYTE_CPU_ARM_64
#if GRAPHYTE_PLATFORM_LINUX
#include "Impl.Linux/ProcessorFeatures.arm.hxx"
#elif GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#include "Impl.Windows/ProcessorFeatures.arm.hxx"
#else
#error "Not implemented"
#endif
#else
#error "Not implemented"
#endif

namespace Graphyte::System::Impl
{
    ProcessorFeatureSet GProcessorFeatureSet{};
    PlatformFeatureSet GPlatformFeatureSet{};

    std::string GProcessorVendor{};
    std::string GProcessorBrand{};

    MemoryProperties GMemoryProperties{};

    size_t GIoWorkerThreads{ 1 };
    size_t GWorkerThreads{ 1 };
    size_t GPhysicalCores{ 1 };
    size_t GLogicalCores{ 1 };
}

GX_DEFINE_LOG_CATEGORY(LogPlatform);

namespace Graphyte::System
{
    BASE_API void Initialize() noexcept
    {
        GX_ASSERT_SINGLE_CALL();

        Impl::DetectProcessorFeatures();
        Impl::DetectPlatformFeatures();
        Impl::InitializePlatform();

#if GX_BUILD_TYPE_RETAIL
        Impl::GIsBuildMachine = Graphyte::CommandLine::Get("--build-machine").has_value();
#endif
    }

    BASE_API void Finalize() noexcept
    {
        GX_ASSERT_SINGLE_CALL();

        Impl::FinalizePlatform();
    }
}
