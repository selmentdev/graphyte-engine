#include "Platform.impl.hxx"
#include <GxBase/CommandLine.hxx>

#if GX_CPU_X86_32 || GX_CPU_X86_64
#include "Impl/ProcessorFeatures.x86.hxx"
#elif GX_CPU_ARM_32 || GX_CPU_ARM_64
#if GX_PLATFORM_LINUX
#include "Impl.Linux/ProcessorFeatures.arm.hxx"
#elif GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
#include "Impl.Windows/ProcessorFeatures.arm.hxx"
#else
#error "Not implemented"
#endif
#else
#error "Not implemented"
#endif

namespace Graphyte::System::Impl
{
    ProcessorFeatureSet g_ProcessorFeatureSet{};
    PlatformFeatureSet g_PlatformFeatureSet{};

    std::string g_ProcessorVendor{};
    std::string g_ProcessorBrand{};

    MemoryProperties g_MemoryProperties{};

    size_t g_IoWorkerThreads{ 1 };
    size_t g_WorkerThreads{ 1 };
    size_t g_PhysicalCores{ 1 };
    size_t g_LogicalCores{ 1 };
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
        Impl::g_IsBuildMachine = Graphyte::CommandLine::Get("--build-machine").has_value();
#endif
    }

    BASE_API void Finalize() noexcept
    {
        GX_ASSERT_SINGLE_CALL();

        Impl::FinalizePlatform();
    }
}
