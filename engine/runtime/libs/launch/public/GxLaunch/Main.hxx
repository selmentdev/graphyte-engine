#include <GxBase/App.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/CommandLine.hxx>
#include <GxBase/Threading/TaskDispatcher.hxx>
#include <GxBase/System.hxx>
#include <GxBase/App.hxx>
#include <GxBase/Diagnostics/Profiler.hxx>
#include <GxBase/Modules.hxx>
#include <GxBase/Network.hxx>
#include <GxBase/System/Process.hxx>
#include <GxGraphics/Graphics.hxx>
#include <GxBase/Flags.hxx>
#include <GxBase/Console.hxx>
#include <GxBase/String.hxx>

GX_DECLARE_LOG_CATEGORY(LogInit, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogInit);

//
// Available features:
//  `#define GX_LAUNCH_SINGLE_INSTANCE "<instance-marker>"
//      Enables single instance checking
//

// =================================================================================================
// GPU Driver Markers

extern "C"
{
    // https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
    GX_MODULE_EXPORT uint32_t NvOptimusEnablement = 1;

    // https://gpuopen.com/amdpowerxpressrequesthighperformance/
    GX_MODULE_EXPORT uint32_t AmdPowerXpressRequestHighPerformance = 1;
}


// =================================================================================================
// Executable engine entry point

extern int GraphyteMain(int argc, char** argv) noexcept;


// =================================================================================================
// Initalization phase

namespace Graphyte::Launch
{
    static void ValidateRequirements() noexcept
    {
#if !GX_MATH_NO_INTRINSICS

#if GX_HW_AVX2 && !GX_HW_AVX
#error "AVX must be enabled with AVX2"
#endif

        using Graphyte::Flags;
        using namespace Graphyte::System;

#if GX_HW_SSE2
        bool const supports_sse2 = HasProcessorFeature(ProcessorFeature::SSE)
                                   && HasProcessorFeature(ProcessorFeature::SSE2);

        GX_ABORT_UNLESS(supports_sse2, "Support for SSE2 is required");
#endif

#if GX_HW_AVX
        bool const supports_avx = HasProcessorFeature(ProcessorFeature::SSE3)
                                  && HasProcessorFeature(ProcessorFeature::SSE41)
                                  && HasProcessorFeature(ProcessorFeature::OSXSAVE)
                                  && HasProcessorFeature(ProcessorFeature::AVX);

        GX_ABORT_UNLESS(supports_avx, "Support for AVX is required");
#endif

#if !GX_HW_AVX2
        bool const supports_avx2 = HasProcessorFeature(ProcessorFeature::SSE3)
                                   && HasProcessorFeature(ProcessorFeature::FMA3)
                                   && HasProcessorFeature(ProcessorFeature::SSE41)
                                   && HasProcessorFeature(ProcessorFeature::OSXSAVE)
                                   && HasProcessorFeature(ProcessorFeature::AVX)
                                   && HasProcessorFeature(ProcessorFeature::F16C)
                                   && HasProcessorFeature(ProcessorFeature::AVX2);
        GX_ABORT_UNLESS(supports_avx2, "Support for AVX is required");
#endif

#endif
    }

    static std::string GetProcessorFeaturesAsString() noexcept
    {
        std::vector<std::string> features{};

#define CHECK_FEATURE(x) \
    if (Graphyte::System::HasProcessorFeature(Graphyte::System::ProcessorFeature::x)) \
    { \
        features.push_back(#x); \
    }

#if GX_CPU_X86_64 || GX_CPU_X86_32

        CHECK_FEATURE(AES);
        CHECK_FEATURE(AVX);
        CHECK_FEATURE(AVX2);
        CHECK_FEATURE(AVX512BITALG);
        CHECK_FEATURE(AVX512BW);
        CHECK_FEATURE(AVX512CD);
        CHECK_FEATURE(AVX512DQ);
        CHECK_FEATURE(AVX512ER);
        CHECK_FEATURE(AVX512F);
        CHECK_FEATURE(AVX512IFMA);
        CHECK_FEATURE(AVX512PF);
        CHECK_FEATURE(AVX512QFMA);
        CHECK_FEATURE(AVX512QVNNIW);
        CHECK_FEATURE(AVX512VBMI);
        CHECK_FEATURE(AVX512VBMI2);
        CHECK_FEATURE(AVX512VL);
        CHECK_FEATURE(AVX512VNNI);
        CHECK_FEATURE(AVX512VP);
        CHECK_FEATURE(BMI1);
        CHECK_FEATURE(BMI2);
        CHECK_FEATURE(CLMUL);
        CHECK_FEATURE(CRC32);
        CHECK_FEATURE(F16C);
        CHECK_FEATURE(FMA3);
        CHECK_FEATURE(FMA4);
        CHECK_FEATURE(HTT);
        CHECK_FEATURE(MOVBE);
        CHECK_FEATURE(OSXSAVE);
        CHECK_FEATURE(POPCNT);
        CHECK_FEATURE(RDRAND);
        CHECK_FEATURE(RDSEED);
        CHECK_FEATURE(SHA);
        CHECK_FEATURE(SSE);
        CHECK_FEATURE(SSE2);
        CHECK_FEATURE(SSE3);
        CHECK_FEATURE(SSE41);
        CHECK_FEATURE(SSE42);
        CHECK_FEATURE(SSE4A);
        CHECK_FEATURE(SSSE3);
        CHECK_FEATURE(VAES);
        CHECK_FEATURE(VPCL);

#elif GX_CPU_ARM_32

        CHECK_FEATURE(AES);
        CHECK_FEATURE(ARMv7);
        CHECK_FEATURE(CRC32);
        CHECK_FEATURE(IDIV_ARM);
        CHECK_FEATURE(IDIV_THUMB2);
        CHECK_FEATURE(LDREX_STREX);
        CHECK_FEATURE(NEON_FMA);
        CHECK_FEATURE(NEON);
        CHECK_FEATURE(PMULL);
        CHECK_FEATURE(SHA1);
        CHECK_FEATURE(SHA2);
        CHECK_FEATURE(VFP_D32);
        CHECK_FEATURE(VFP_FMA);
        CHECK_FEATURE(VFP_FP16);
        CHECK_FEATURE(VFPv2);
        CHECK_FEATURE(VFPv3);

#elif GX_CPU_ARM_64

        CHECK_FEATURE(AES);
        CHECK_FEATURE(ASIMD);
        CHECK_FEATURE(ASIMDFHM);
        CHECK_FEATURE(ASIMDHP);
        CHECK_FEATURE(ATOMICS);
        CHECK_FEATURE(CRC32);
        CHECK_FEATURE(FP);
        CHECK_FEATURE(FPHP);
        CHECK_FEATURE(PMULL);
        CHECK_FEATURE(SHA1);
        CHECK_FEATURE(SHA2);
        CHECK_FEATURE(SHA3);
        CHECK_FEATURE(SHA512);

#else
#error "Unsupported processor architecture"
#endif

        return Graphyte::Join(features, ", ");
    }

    static void LogBanner() noexcept
    {
        GX_LOG_INFO(LogInit, "Engine version: {}\n", System::GetBuildVersion());
        GX_LOG_INFO(LogInit, "Build-ID: {}-{}\n",
            System::GetBuildBranch(),
            System::GetBuildCommit());
        GX_LOG_INFO(LogInit, "System version: {}\n", System::GetSystemVersion());
        GX_LOG_INFO(LogInit, "Process ID: {}\n", Graphyte::System::Process::GetCurrent());

        std::string linktime{};
        ToString(linktime, Graphyte::System::Process::GetLinkTime());

        GX_LOG_INFO(LogInit, "Link time: {}\n", linktime);

        std::string launchtime{};
        ToString(launchtime, Graphyte::DateTime::Now());
        GX_LOG_INFO(LogInit, "Launch time: {}\n", launchtime);


        auto const& memory_properties = System::GetMemoryProperties();
        GX_LOG_INFO(LogInit, "Memory (virtual: {} MiB, physical: {} MiB, pagefile: {} MiB, pagesize: {})\n",
            memory_properties.TotalVirtual >> 20,
            memory_properties.TotalPhysical >> 20,
            memory_properties.TotalPagefile >> 20,
            memory_properties.PageSize);

        GX_LOG_INFO(LogInit, "CPU: {} {}\n",
            System::GetProcessorVendor(),
            System::GetProcessorBrand());

        GX_LOG_INFO(LogInit, "CPU Cores (logical: {}, physical: {})\n",
            System::GetLogicalCores(),
            System::GetPhysicalCores());

        GX_LOG_INFO(LogInit, "CPU Features: {}\n", GetProcessorFeaturesAsString());

        System::DisplayMetrics metrics{};
        if (System::GetDisplayMetrics(metrics) == Status::Success)
        {
            GX_LOG_INFO(LogInit, "Display: [{}, {}, {}, {}]\n",
                metrics.VirtualDisplayRect.Left,
                metrics.VirtualDisplayRect.Top,
                metrics.VirtualDisplayRect.Width,
                metrics.VirtualDisplayRect.Height);

            for (size_t i = 0; i < metrics.Displays.size(); ++i)
            {
                auto const& display = metrics.Displays[i];
                GX_LOG_INFO(LogInit, " - {} - {} {} [{}, {}, {}, {}]\n",
                    i,
                    display.Name,
                    display.Primary ? "primary" : "secondary",
                    display.DisplayRect.Left,
                    display.DisplayRect.Top,
                    display.DisplayRect.Width,
                    display.DisplayRect.Height);
            }
        }
    }

    static void Initialize(int argc, char** argv) noexcept
    {
        GX_ASSERT_SINGLE_CALL();


        //
        // Try to initialize current directory as early as possible - any other thread spawned from
        // main thread will inherit that directory.
        //

        {
            [[maybe_unused]] Status status = System::SetCurrentDirectory(System::GetBaseDirectory());
            GX_ABORT_UNLESS(status == Status::Success, "Cannot set current directory");
        }

        CommandLine::Initialize(
            static_cast<size_t>(argc),
            const_cast<const char**>(argv));

        Diagnostics::Initialize();

        System::Initialize();

        Diagnostics::Profiler::Initialize();

        App::Initialize();

        ModuleManager::Initialize();

        Network::Initialize();

        Threading::TaskDispatcher::Initialize();

        ValidateRequirements();

        LogBanner();

        Graphics::Initialize();

        Console::Initialize();
    }

    static void Finalize() noexcept
    {
        GX_ASSERT_SINGLE_CALL();

        Console::Finalize();

        Graphics::Finalize();

        Threading::TaskDispatcher::Finalize();

        Network::Finalize();

        ModuleManager::Finalize();

        App::Finalize();

        System::Finalize();

        Diagnostics::Profiler::Finalize();
        Diagnostics::Finalize();

        CommandLine::Finalize();
    }

    static void LoadModules()
    {
        //Graphyte::ModuleManager::LoadChecked("GxBase");
        //Graphyte::ModuleManager::LoadChecked("GxFramework");
        //Graphyte::ModuleManager::LoadChecked("GxAI");
        //Graphyte::ModuleManager::LoadChecked("GxEntities");
    }
}

// =================================================================================================
// Entry point

namespace Graphyte::Launch
{
    int MainWrapper(int argc, char** argv) noexcept
    {
        Initialize(argc, argv);

        LoadModules();

        int const result = GraphyteMain(argc, argv);

        Finalize();

        return result;
    }
}

// =================================================================================================
// Per-platform initialization

#if GX_PLATFORM_WINDOWS
#include <GxLaunch/Impl.Windows/ErrorHandling.hxx>
#include <GxLaunch/Impl.Windows/SingleInstance.hxx>
#elif GX_PLATFORM_LINUX
#include <GxLaunch/Impl.Linux/ErrorHandling.hxx>
#include <GxLaunch/Impl.Linux/SingleInstance.hxx>
#else
#error Not supported
#endif

// =================================================================================================
// Initialization

#include <GxLaunch/Impl/Init.hxx>

// common main function
int main(int argc, char** argv)
{
    return Graphyte::Launch::Main(argc, argv);
}

// Windows specific entry point
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
INT
#if !defined(_MAC)
#if defined(_M_CEE_PURE)
    __clrcall
#else
    WINAPI
#endif
#else
    CALLBACK
#endif
    WinMain(
        [[maybe_unused]] _In_ HINSTANCE hInstance,
        [[maybe_unused]] _In_opt_ HINSTANCE hPrevInstance,
        [[maybe_unused]] _In_ LPSTR lpCmdLine,
        [[maybe_unused]] _In_ INT nShowCmd)
{
    return Graphyte::Launch::Main(__argc, __argv);
}

#endif
