#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/CommandLine.hxx>
#include <Graphyte/Threading/TaskDispatcher.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Application.hxx>
#include <Graphyte/Diagnostics/Profiler.hxx>
#include <Graphyte/Modules.hxx>
#include <Graphyte/Network.hxx>
#include <Graphyte/System/Process.hxx>
#include <Graphyte/Graphics.hxx>
#include <Graphyte/Flags.hxx>
#include <Graphyte/Console.hxx>
#include <Graphyte/String.hxx>

GX_DECLARE_LOG_CATEGORY(LogInit, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogInit);

namespace Graphyte::Launch
{
    extern void InitializeErrorHandling() noexcept;

    static void ValidateRequirements() noexcept
    {
#if !GRAPHYTE_MATH_NO_INTRINSICS

#   if GRAPHYTE_HW_AVX2 && !GRAPHYTE_HW_AVX
#       error "AVX must be enabled with AVX2"
#   endif

        using Graphyte::System::ProcessorFeature;
        using Graphyte::Flags;

#   if GRAPHYTE_HW_SSE2
        GX_ABORT_UNLESS(
            System::HasProcessorFeature(System::ProcessorFeature::SSE2),
            "Support for SSE2 is required"
        );
#   endif

#   if GRAPHYTE_HW_AVX
        GX_ABORT_UNLESS(
            System::HasProcessorFeature(System::ProcessorFeature::SSE3),
            "Support for SSE3 is required"
        );
        GX_ABORT_UNLESS(
            System::HasProcessorFeature(System::ProcessorFeature::SSE41),
            "Support for SSE4.1 is required"
        );
        GX_ABORT_UNLESS(
            System::HasProcessorFeature(System::ProcessorFeature::AVX),
            "Support for AVX is required"
        );
#   endif

#   if GRAPHYTE_HW_AVX2
        GX_ABORT_UNLESS(
            System::HasProcessorFeature(System::ProcessorFeature::AVX2),
            "Support for AVX2 is required"
        );
#   endif

#   if GRAPHYTE_HW_AVX2 || GRAPHYTE_HW_FMA3
        GX_ABORT_UNLESS(
            System::HasProcessorFeature(System::ProcessorFeature::FMA3),
            "Support for FMA3 is required"
        );
#   endif

#   if GRAPHYTE_HW_AVX2 || GRAPHYTE_HW_F16C
        GX_ABORT_UNLESS(
            System::HasProcessorFeature(System::ProcessorFeature::F16C),
            "Support for F16C is required"
        );
#   endif

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

#if GRAPHYTE_CPU_X86_64 || GRAPHYTE_CPU_X86_32

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

#elif GRAPHYTE_CPU_ARM_32

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

#elif GRAPHYTE_CPU_ARM_64

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
        std::string engine_version{};
        Converter<Version>::ToString(engine_version, System::GetBuildVersion());

        GX_LOG(LogInit, Info, "Engine version: {}\n", engine_version);
        GX_LOG(LogInit, Info, "Build-ID: {}-{}\n",
            System::GetBuildBranch(),
            System::GetBuildCommit()
        );
        GX_LOG(LogInit, Info, "System version: {}\n", System::GetSystemVersion());
        GX_LOG(LogInit, Info, "Process ID: {}\n", Graphyte::System::Process::GetCurrent());

        std::string linktime{};
        ToString(linktime, Graphyte::System::Process::GetLinkTime());

        GX_LOG(LogInit, Info, "Link time: {}\n", linktime);

        std::string launchtime{};
        ToString(launchtime, Graphyte::DateTime::Now());
        GX_LOG(LogInit, Info, "Launch time: {}\n", launchtime);


        auto const& memory_properties = System::GetMemoryProperties();
        GX_LOG(LogInit, Info, "Memory (virtual: {} MiB, physical: {} MiB, pagefile: {} MiB, pagesize: {})\n",
            memory_properties.TotalVirtual >> 20,
            memory_properties.TotalPhysical >> 20,
            memory_properties.TotalPagefile >> 20,
            memory_properties.PageSize
        );

        GX_LOG(LogInit, Info, "CPU: {} {}\n",
            System::GetProcessorVendor(),
            System::GetProcessorBrand()
        );

        GX_LOG(LogInit, Info, "CPU Cores (logical: {}, physical: {})\n",
            System::GetLogicalCores(),
            System::GetPhysicalCores()
        );

        GX_LOG(LogInit, Info, "CPU Features: {}\n", GetProcessorFeaturesAsString());

        System::DisplayMetrics metrics{};
        if (System::GetDisplayMetrics(metrics) == Status::Success)
        {
            GX_LOG(LogInit, Info, "Display: [{}, {}, {}, {}]\n",
                metrics.VirtualDisplayRect.Left,
                metrics.VirtualDisplayRect.Top,
                metrics.VirtualDisplayRect.Width,
                metrics.VirtualDisplayRect.Height
            );

            for (size_t i = 0; i < metrics.Displays.size(); ++i)
            {
                auto const& display = metrics.Displays[i];
                GX_LOG(LogInit, Info, " - {} - {} {} [{}, {}, {}, {}]\n",
                    i,
                    display.Name,
                    display.Primary ? "primary" : "secondary",
                    display.DisplayRect.Left,
                    display.DisplayRect.Top,
                    display.DisplayRect.Width,
                    display.DisplayRect.Height
                );
            }
        }
    }

    static void Initialize(int argc, char** argv) noexcept
    {
        GX_ASSERT_SINGLE_CALL();

        InitializeErrorHandling();


        //
        // Try to initialize current directory as early as possible - any other thread spawned from
        // main thread will inherit that directory.
        //

        {
            [[maybe_unused]] Status status = System::SetCurrentDirectory(System::GetBaseDirectory());
            GX_ABORT_UNLESS(status == Status::Success, "Cannot set current directory");
        }

        CommandLine::Initialize(argc, const_cast<const char**>(argv));

        Diagnostics::Initialize();

        System::Initialize();

        Diagnostics::Profiler::Initialize();

        Application::Initialize();

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

        Application::Finalize();

        System::Finalize();

        Diagnostics::Profiler::Finalize();
        Diagnostics::Finalize();

        CommandLine::Finalize();
    }

    static void LoadModules() noexcept
    {
        Graphyte::ModuleManager::LoadChecked("com.graphyte.base");
        //Graphyte::ModuleManager::LoadChecked("com.graphyte.framework");
        //Graphyte::ModuleManager::LoadChecked("com.graphyte.ai");
        //Graphyte::ModuleManager::LoadChecked("com.graphyte.entities");
    }
}


// =================================================================================================
//
// Main function defined in application project.
//

extern int GraphyteMain(int argc, char** argv) noexcept;


// =================================================================================================
//
// Common engine initialization and finalization.
//

namespace Graphyte::Launch
{
    int MainWrapper(int argc, char** argv) noexcept
    {
        Initialize(argc, argv);

        LoadModules();

        int result = GraphyteMain(argc, argv);

        Finalize();

        return result;
    }
}
