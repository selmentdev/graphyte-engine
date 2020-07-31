#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/Version.hxx>
#include <GxBase/DateTime.hxx>
#include <GxBase/Diagnostics.hxx>

// =================================================================================================
//
// Platform global log category.
//

GX_DECLARE_LOG_CATEGORY(LogPlatform, Trace, Trace);

// =================================================================================================
//
// Initialization and finalization.
//

namespace Graphyte::System
{
    //! \brief Initializes platform specific engine part.
    extern BASE_API void Initialize() noexcept;

    //! \brief Finalizes platform specific engine part.
    extern BASE_API void Finalize() noexcept;
}


// =================================================================================================
//
// Common platform types and converters.
//

namespace Graphyte::System
{
    template <typename T>
    struct TypeConverter;

    struct Point final
    {
        int32_t Left;
        int32_t Top;
    };

    struct Size final
    {
        int32_t Width;
        int32_t Height;
    };

    struct Rect final
    {
        int32_t Left;
        int32_t Top;
        int32_t Width;
        int32_t Height;
    };

    struct PointF final
    {
        float Left;
        float Top;
    };

    struct SizeF final
    {
        float Width;
        float Height;
    };

    struct RectF final
    {
        float Left;
        float Top;
        float Width;
        float Height;
    };

    struct ColorF final
    {
        float R;
        float G;
        float B;
        float A;
    };
}


// =================================================================================================
//
// Memory stats, allocations and common functions.
//

namespace Graphyte::System
{
    struct MemoryUsage final
    {
        uint64_t AvailableVirtual;
        uint64_t AvailablePhysical;
        uint64_t UsedVirtual;
        uint64_t UsedPhysical;
        uint64_t PeakUsedVirtual;
        uint64_t PeakUsedPhysical;
    };

    //! \brief Gets current application memory usage.
    extern BASE_API MemoryUsage GetMemoryUsage() noexcept;

    struct MemoryProperties final
    {
        uint64_t TotalPhysical;
        uint64_t TotalVirtual;
        uint64_t TotalPagefile;
        uint64_t SystemAllocationGranularity;
        uint64_t PageSize;
        uint64_t AddressLimit;
    };

    //! \brief Gets system memory properties.
    extern BASE_API MemoryProperties GetMemoryProperties() noexcept;
}


// =================================================================================================
//
// Heap and virtual memory allocators.
//

namespace Graphyte::System
{
    extern BASE_API void* OsMalloc(
        size_t size) noexcept;

    extern BASE_API void* OsRealloc(
        void* memory,
        size_t size) noexcept;

    extern BASE_API void OsFree(
        void* memory) noexcept;

    extern BASE_API void* OsVirtualAlloc(
        size_t size) noexcept;

    extern BASE_API void OsVirtualFree(
        void* memory,
        size_t size) noexcept;

    extern BASE_API bool OsVirtualProtect(
        void* memory,
        size_t size,
        bool canRead,
        bool canWrite) noexcept;
}


// =================================================================================================
//
// Memory prefetching
//

namespace Graphyte::System
{
    inline void Prefetch(
        [[maybe_unused]] const void* memory,
        [[maybe_unused]] ptrdiff_t offset) noexcept
    {
#if GRAPHYTE_CPU_X86_32 || GRAPHYTE_CPU_X86_64
        _mm_prefetch(reinterpret_cast<const char*>(memory) + offset, _MM_HINT_T0);
#elif GRAPHYTE_CPU_ARM_32 || GRAPHYTE_CPU_ARM_64
        // http://infocenter.arm.com/help/topic/com.arm.doc.ihi0053c/IHI0053C_acle_2_0.pdf
#else
#error "Unimplemented"
#endif
    }

    inline void PrefetchBlock(
        [[maybe_unused]] const void* memory,
        [[maybe_unused]] size_t size) noexcept
    {
#if GRAPHYTE_CPU_X86_32 || GRAPHYTE_CPU_X86_64
        size_t const cacheline_size = GRAPHYTE_CACHELINE_SIZE;
        std::byte const* it         = reinterpret_cast<std::byte const*>(memory);

        for (size_t lines = (size + cacheline_size - 1) / cacheline_size; lines != 0; --lines)
        {
            _mm_prefetch(reinterpret_cast<const char*>(it), _MM_HINT_T0);
            it += cacheline_size;
        }
#elif GRAPHYTE_CPU_ARM_32 || GRAPHYTE_CPU_ARM_64
        // http://infocenter.arm.com/help/topic/com.arm.doc.ihi0053c/IHI0053C_acle_2_0.pdf
#else
#error "Unimplemented"
#endif
    }
}


// =================================================================================================
//
// Common memory operations.
//

namespace Graphyte::System
{
    inline void SecureMemoryZero(
        void* destination,
        size_t size) noexcept
    {
        volatile char* it = reinterpret_cast<volatile char*>(destination);
        for (; size != 0; --size, ++it)
        {
#if GRAPHYTE_COMPILER_MSVC && (GRAPHYTE_CPU_ARM_32 || GRAPHYTE_CPU_ARM_64)
            __iso_volatile_store8(it, 0);
#else
            (*it) = 0;
#endif
        }
    }

    inline void* MemoryMove(
        void* destination,
        const void* source,
        size_t size) noexcept
    {
        return memmove(destination, source, size);
    }

    inline void* MemoryCopy(
        void* destination,
        const void* source,
        size_t size) noexcept
    {
        return memcpy(destination, source, size);
    }

    inline void* MemoryCopyBlock(
        void* destination,
        const void* source,
        size_t size) noexcept
    {
        return memcpy(destination, source, size);
    }

    inline void* MemoryCopyStreaming(
        void* destination,
        const void* source,
        size_t size) noexcept
    {
        return memcpy(destination, source, size);
    }

    inline int MemoryCompare(
        const void* buffer1,
        const void* buffer2,
        size_t size) noexcept
    {
        return memcmp(buffer1, buffer2, size);
    }

    inline void* MemorySet(
        void* destination,
        uint8_t value,
        size_t size) noexcept
    {
        return memset(destination, value, size);
    }

    inline void* MemoryZero(
        void* destination,
        size_t size) noexcept
    {
        return memset(destination, 0, size);
    }
}


// =================================================================================================
//
// System information.
//

namespace Graphyte::System
{
    //! \brief Gets user directory.
    extern BASE_API std::string GetUserDirectory() noexcept;

    //! \brief Gets user documents directory.
    extern BASE_API std::string GetUserDocumentsDirectory() noexcept;

    //! \brief Gets user temp directory.
    extern BASE_API std::string GetUserTemporaryDirectory() noexcept;

    //! \brief Gets user settings directory.
    extern BASE_API std::string GetUserSettingsDirectory() noexcept;

    //! \brief Gets directory for application common data.
    extern BASE_API std::string GetApplicationCommonDataDirectory() noexcept;

    //! \brief Gets user domain name.
    extern BASE_API std::string GetUserDomain() noexcept;

    //! \brief Gets user name.
    extern BASE_API std::string GetUserName() noexcept;

    //! \brief Gets system version.
    extern BASE_API std::string GetSystemVersion() noexcept;

    //! \brief Gets system identifier.
    extern BASE_API std::string GetSystemId() noexcept;

    //! \brief Gets default locale name.
    extern BASE_API std::string GetDefaultLocale() noexcept;

    //! \brief Gets default language.
    extern BASE_API std::string GetDefaultLanguage() noexcept;

    //! \brief Gets local currency code.
    extern BASE_API std::string GetLocalCurrencyCode() noexcept;

    //! \brief Gets local currency symbol.
    extern BASE_API std::string GetLocalCurrencySymbol() noexcept;

    //! \brief Checks whether WIFI connection is active.
    extern BASE_API bool HasActiveWifiConnection() noexcept;

    //! \brief Gets value indicating whether process is running on 64-bit operating system.
    extern BASE_API bool Is64BitOperatingSystem() noexcept;

    //! \brief Gets value indicating whether current process is 64-bit.
    extern BASE_API bool Is64BitProcess() noexcept;

    //! \brief Gets value indicating whether mouse HID is present.
    extern BASE_API bool IsMousePresent() noexcept;

    //! \brief Gets value indicating whether mouse has wheel.
    extern BASE_API bool IsMouseWheelPresent() noexcept;

    //! \brief Gets value indicating whether platform is little endian.
    extern BASE_API bool IsLittleEndian() noexcept;

    //! \brief Gets platform specific hardware window.
    extern BASE_API void* GetHardwareWindow() noexcept;

    //! \brief Restores system UI.
    //!
    //! \remarks Releases mouse capture and clipping for UI purposes
    extern BASE_API void RestoreSystemUI() noexcept;
}


// =================================================================================================
//
// Build info.
//

namespace Graphyte::System
{
    enum struct BuildKind : uint32_t
    {
        Debug,
        Checked,
        Profile,
        Release,
    };

    //! \brief Gets kind of build.
    extern BASE_API BuildKind GetBuildKind() noexcept;

    // clang-format off
#if GX_CONFIG_RELEASE
    inline constexpr const BuildKind CurrentBuildKind = BuildKind::Release;
#elif GX_CONFIG_PROFILE
    inline constexpr const BuildKind CurrentBuildKind = BuildKind::Profile;
#elif GX_CONFIG_DEBUG
    inline constexpr const BuildKind CurrentBuildKind = BuildKind::Debug;
#elif GX_CONFIG_CHECKED
    inline constexpr const BuildKind CurrentBuildKind = BuildKind::Checked;
#endif
    // clang-format on

    enum struct BuildType : uint32_t
    {
        Developer,
        Testing,
        Retail,
    };

    // clang-format off
#if GX_BUILD_TYPE_DEVELOPER
    inline constexpr const BuildType CurrentBuildType = BuildType::Developer;
#elif GX_BUILD_TYPE_TESTING
    inline constexpr const BuildType CurrentBuildType = BuildType::Testing;
#elif GX_BUILD_TYPE_RETAIL
    inline constexpr const BuildType CurrentBuildType = BuildType::Retail;
#endif
    // clang-format on

    //! \brief Gets build type.
    extern BASE_API BuildType GetBuildType() noexcept;

    //! \brief Checks whether current process runs on build machine.
    extern BASE_API bool IsBuildMachine() noexcept;

    //! \brief Gets unique build ID.
    extern BASE_API std::string_view GetBuildId() noexcept;

    //! \brief Gets source code build branch.
    extern BASE_API std::string_view GetBuildBranch() noexcept;

    //! \brief Gets source code build commit.
    extern BASE_API std::string_view GetBuildCommit() noexcept;

    //! \brief Gets source code build version.
    extern BASE_API Version GetBuildVersion() noexcept;

    //! \brief Gets builder machine host system name.
    extern BASE_API std::string_view GetBuildHostSystem() noexcept;

    //! \brief Gets builder machine host system version.
    extern BASE_API std::string_view GetBuildHostVersion() noexcept;

    //! \brief Gets build timestamp.
    extern BASE_API std::string_view GetBuildTimestamp() noexcept;

    //! \brief Gets build compiler name.
    extern BASE_API std::string_view GetCompilerName() noexcept;
}


// =================================================================================================
//
// Platform info.
//

namespace Graphyte::System
{
    enum struct PlatformKind : uint32_t
    {
        Desktop,
        Console,
        Mobile,
        Hybrid,
    };

    // clang-format off
#if GRAPHYTE_PLATFORM_TYPE_MOBILE
    inline constexpr const PlatformKind CurrentPlatformKind = PlatformKind::Mobile;
#elif GRAPHYTE_PLATFORM_TYPE_DESKTOP
    inline constexpr const PlatformKind CurrentPlatformKind = PlatformKind::Desktop;
#elif GRAPHYTE_PLATFORM_TYPE_HYBRID
    inline constexpr const PlatformKind CurrentPlatformKind = PlatformKind::Hybrid;
#elif GRAPHYTE_PLATFORM_TYPE_CONSOLE
    inline constexpr const PlatformKind CurrentPlatformKind = PlatformKind::Console;
#endif
    // clang-format on

    //! \brief Gets platform kind.
    extern BASE_API PlatformKind GetPlatformKind() noexcept;

    enum struct PlatformType : uint32_t
    {
        Android,
        BSD,
        Emscripten,
        IOS,
        Linux,
        NX,
        OSX,
        PS4,
        RaspberryPI,
        SteamLink,
        Windows,
        UWP,
        XBoxOne,
    };

    // clang-format off
#if GRAPHYTE_PLATFORM_ANDROID
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::Android;
#elif GRAPHYTE_PLATFORM_BSD
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::BSD;
#elif GRAPHYTE_PLATFORM_EMSCRIPTEN
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::Emscripten;
#elif GRAPHYTE_PLATFORM_IOS
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::IOS;
#elif GRAPHYTE_PLATFORM_LINUX
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::Linux;
#elif GRAPHYTE_PLATFORM_NX
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::NX;
#elif GRAPHYTE_PLATFORM_OSX
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::OSX;
#elif GRAPHYTE_PLATFORM_PS4
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::PS4;
#elif GRAPHYTE_PLATFORM_RPI
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::RaspberryPI;
#elif GRAPHYTE_PLATFORM_STEAMLINK
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::SteamLink;
#elif GRAPHYTE_PLATFORM_WINDOWS
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::Windows;
#elif GRAPHYTE_PLATFORM_UWP
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::UWP;
#elif GRAPHYTE_PLATFORM_XBOXONE
    inline constexpr const PlatformType CurrentPlatformType = PlatformType::XBoxOne;
#endif
    // clang-format on


    //! \brief Gets platform type.
    extern BASE_API PlatformType GetPlatformType() noexcept;

    //! \brief Gets platform name.
    extern BASE_API std::string_view GetPlatformName() noexcept;

    enum struct PlatformFeature : uint32_t
    {
        AudioStreaming,
        AudioThread,
        CallstackAssertDump,
        DeadlockWatchdog,
        DistanceFieldShadows,
        Exit,
        FastVRAMMemory,
        FramerateSmoothing,
        FullCrashDump,
        HighQualityLightmaps,
        LowQualityLightmaps,
        LocalCaching,
        Messaging,
        Minimize,
        MultipleInstances,
        Multithreading,
        RenderThread,
        ResolutionChanging,
        SystemAudioVolumeHandling,
        Tesselation,
        TextureStreaming,
        TouchInput,
        WindowedMode,
        VariableHardware,
        SeparateDebugOutput,
        VirtualJoystick,
        VirtualKeyboard,
        RequiresCookedData,
        RequiresUserCredenials,
    };

    //! \brief Checks whether specific platform feature is supported.
    extern BASE_API bool HasPlatformFeature(
        PlatformFeature feature) noexcept;

    //! \brief Gets name of file manager.
    extern BASE_API std::string_view GetFileManagerName() noexcept;

    //! \brief Gets platform specific module extension.
    extern BASE_API std::string_view GetModuleExtension() noexcept;

    //! \brief Gets platform specific module prefix.
    extern BASE_API std::string_view GetModulePrefix() noexcept;

    //! \brief Gets platform specific executable extension.
    extern BASE_API std::string_view GetExecutableExtension() noexcept;
}


// =================================================================================================
//
// Environment.
//

namespace Graphyte::System
{
    //! \brief Gets content of clipboard.
    //!
    //! \param content Returns current content of clipboard.
    //!
    //! \return The status code.
    extern BASE_API Status GetClipboardContent(
        std::string& content) noexcept;


    //! \brief Sets content of clipboard.
    //!
    //! \param content Provides new content of clipboard.
    //!
    //! \return The status code.
    extern BASE_API Status SetClipboardContent(
        std::string_view content) noexcept;

    //! \brief Gets content of environment variable.
    //!
    //! \param result Returns content of variable.
    //! \param name   Provides name of variable.
    //!
    //! \return The status code.
    extern BASE_API Status GetEnvironmentVariable(
        std::string& result,
        const char* name) noexcept;

    //! \brief Sets content of environment variable.
    //!
    //! \param name  Provides name of variable.
    //! \param value Provides content of variable.
    //!
    //! \return The status code.
    extern BASE_API Status SetEnvironmentVariable(
        const char* name,
        const char* value) noexcept;

    //! \brief Removes environment variable.
    //!
    //! \param name Provides name of variable to remove.
    //!
    //! \return The status code.
    extern BASE_API Status RemoveEnvironmentVariable(
        const char* name) noexcept;

    //! \brief Sets current thread current directory.
    //!
    //! \param value Provides new path for directory.
    //!
    //! \return The status code.
    extern BASE_API Status SetCurrentDirectory(
        const std::string& value) noexcept;

    //! \brief Gets current thread current directory.
    //!
    //! \param result Returns current directory.
    //!
    //! \return The status code.
    extern BASE_API Status GetCurrentDirectory(
        std::string& result) noexcept;

    //! \brief Gets full path to currently running application executable.
    extern BASE_API std::string GetExecutablePath() noexcept;

    //! \brief Gets name of currently running application executable.
    extern BASE_API std::string GetExecutableName() noexcept;

    //! \brief Gets base directory of currently runnning application executable.
    extern BASE_API std::string GetBaseDirectory() noexcept;

    //! \brief Executes system process command.
    //!
    //! \param type    Provides type of action to execute.
    //! \param command Provides command to execute.
    //! \param params  Provides params string.
    //!
    //! \return The status code.
    [[deprecated("this API is not portable")]] extern BASE_API Status Execute(
        const char* type,
        const char* command,
        const char* params) noexcept;

    //! \brief Opens system specific file manager.
    //!
    //! \param path Provides path to open.
    //!
    //! \return The status code.
    extern BASE_API Status Explore(
        const char* path) noexcept;
}


// =================================================================================================
//
// Power management.
//

namespace Graphyte::System
{
    struct ProcessorUsageState final
    {
        int64_t UserTime;
        int64_t KernelTime;
        int64_t IdleTime;
    };

    enum class BatteryState
    {
        Unknown,
        Charging,
        Disacharging,
        NoBattery,
        Charged,
    };

    //! \brief Gets battery state.
    //!
    //! \param state    Returns current battery state.
    //! \param level    Returns current battery level in percents.
    //! \param lifetime Returns expected battery lifetime.
    //!
    //! \return The status code.
    extern BASE_API Status GetBatteryState(
        BatteryState& state,
        int& level,
        int& lifetime) noexcept;
}


// =================================================================================================
//
// Processor information.
//

namespace Graphyte::System
{
    enum class ProcessorArchitecture
    {
        X86,
        X64,
        Arm32,
        Arm64,
        Mips32,
        Mips64,
        PowerPC32,
        PowerPC64,
        RiscV128,
        RiscV64,
        RiscV32,
    };

#if GRAPHYTE_CPU_ARM_64
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::Arm64;
#elif GRAPHYTE_CPU_ARM_32
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::Arm32;
#elif GRAPHYTE_CPU_X86_64
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::X64;
#elif GRAPHYTE_CPU_X86_32
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::X86;
#elif GRAPHYTE_CPU_MIPS_64
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::Mips64;
#elif GRAPHYTE_CPU_MIPS_32
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::Mips32;
#elif GRAPHYTE_CPU_PPC_64
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::PowerPC64;
#elif GRAPHYTE_CPU_PPC_32
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::PowerPC32;
#elif GRAPHYTE_CPU_RISCV_128
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::RiscV128;
#elif GRAPHYTE_CPU_RISCV_64
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::RiscV64;
#elif GRAPHYTE_CPU_RISCV_32
    inline constexpr const ProcessorArchitecture CurrentArchitecture = ProcessorArchitecture::RiscV32;
#endif


    //! \brief Gets current processor architecture.
    extern BASE_API ProcessorArchitecture GetProcessorArchitecture() noexcept;

    // https://github.com/dotnet/coreclr/blob/master/src/pal/src/misc/jitsupport.cpp on ARMs; use cpuid on x86
    // https://github.com/dotnet/coreclr/pull/15447/commits/39bd7fa5fcd5a2cd2d36b38bcbe17d33cb25db4e
    // https://github.com/weidai11/cryptopp/issues/213
    enum class ProcessorFeature : uint32_t
    {
#if GRAPHYTE_CPU_X86_64 || GRAPHYTE_CPU_X86_32

        AES,
        AVX,
        AVX2,
        AVX512BITALG,
        AVX512BW,
        AVX512CD,
        AVX512DQ,
        AVX512ER,
        AVX512F,
        AVX512IFMA,
        AVX512PF,
        AVX512QFMA,
        AVX512QVNNIW,
        AVX512VBMI,
        AVX512VBMI2,
        AVX512VL,
        AVX512VNNI,
        AVX512VP,
        BMI1,
        BMI2,
        CLMUL,
        CRC32,
        F16C,
        FMA3,
        FMA4,
        HTT,
        MOVBE,
        OSXSAVE,
        POPCNT,
        RDRAND,
        RDSEED,
        SHA,
        SSE,
        SSE2,
        SSE3,
        SSE41,
        SSE42,
        SSE4A,
        SSSE3,
        VAES,
        VPCL,

#elif GRAPHYTE_CPU_ARM_32

        AES,
        ARMv7, // this maybe required
        CRC32,
        IDIV_ARM,
        IDIV_THUMB2,
        LDREX_STREX,
        NEON_FMA,
        NEON,
        PMULL,
        SHA1,
        SHA2,
        VFP_D32,
        VFP_FMA,
        VFP_FP16,
        VFPv2,
        VFPv3,

#elif GRAPHYTE_CPU_ARM_64

        AES,
        ASIMD,
        ASIMDFHM,
        ASIMDHP,
        ATOMICS,
        CRC32,
        FP,
        FPHP,
        PMULL,
        SHA1,
        SHA2,
        SHA3,
        SHA512,

#else
#error "Unsupported processor architecture"
#endif
    };

    //! \brief Determines whether processor supports specific feature.
    //!
    //! \param feature Provides CPU feature to check.
    //!
    //! \return The value indicating whether feature is supported.
    extern BASE_API bool HasProcessorFeature(
        ProcessorFeature feature) noexcept;

    //! \brief Gets number of available I/O worker threads.
    extern BASE_API size_t GetIoWorkerThreads() noexcept;

    //! \brief Gets number of worker threads.
    extern BASE_API size_t GetWorkerThreads() noexcept;

    //! \brief Gets number of physical cores.
    extern BASE_API size_t GetPhysicalCores() noexcept;

    //! \brief Gets number of logical cores.
    extern BASE_API size_t GetLogicalCores() noexcept;

    //! \brief Gets size of cacheline.
    extern BASE_API size_t GetProcessorCachelineSize() noexcept;

    //! \brief Gets processor vendor.
    extern BASE_API std::string_view GetProcessorVendor() noexcept;

    //! \brief Gets brand of processor.
    extern BASE_API std::string_view GetProcessorBrand() noexcept;
}


// =================================================================================================
//
// Display metrics.
//

namespace Graphyte::System
{
    struct DisplayInfo final
    {
    public:
        std::string Name;
        std::string Id;
        Rect DisplayRect;
        Rect WorkAreaRect;
        bool Primary;
    };

    struct DisplayMetrics final
    {
    public:
        std::vector<DisplayInfo> Displays;
        Rect VirtualDisplayRect;
        Rect PrimaryDisplayWorkArea;
        Size PrimaryDisplaySize;
    };

    //! \brief Gets display metrics.
    //!
    //! \param result Returns current display metrics.
    //!
    //! \return The status code.
    extern BASE_API Status GetDisplayMetrics(
        DisplayMetrics& result) noexcept;

    enum class DeviceScreenOrientation
    {
        //! Cannot determine current screen orientation.
        None,

        //! Landscape.
        Landscape,

        //! Landscape turned 180 degrees.
        LandscapeFlipped,

        //! Portrait.
        Portrait,

        //! Portrait turned 180 degrees.
        PortraitFlipped,
    };

    //! \brief Gets screen orientation.
    extern BASE_API DeviceScreenOrientation GetScreenOrientation() noexcept;

    //! \brief Gets color of pixel on screen.
    //!
    //! \param position Provides pixel position.
    //! \param gamma    Provides gamma factor.
    //!
    //! \return The color on screen. Returns (0, 0, 0) for invalid position / when not supported.
    extern BASE_API ColorF GetScreenPixel(
        Point position,
        float gamma) noexcept;

    //! \brief Enables or disables screen saver.
    //!
    //! \param enable Specifies whether to enable or disable screen saver.
    //!
    //! \return The status code.
    extern BASE_API Status ControlScreensaver(
        bool enable) noexcept;

    //! \brief Prevents screen saver.
    extern BASE_API void PreventScreensaver() noexcept;
}


// =================================================================================================
//
// Time functions.
//

namespace Graphyte::System
{
    static constexpr const uint64_t GSecondsToMicroseconds = 1000000;

    static constexpr const uint64_t GSecondsToNanoseconds = 1000000000;

    static constexpr const uint64_t GSystemClockTimeFrequency = UINT64_C(10000000);

    extern BASE_API double GSecondsPerCycle;

    //! \brief Gets UTC system time as calendar time.
    //!
    //! \param time Returns system time.
    extern BASE_API void GetSystemTime(
        CalendarTime& time) noexcept;

    //! \brief Gets local time as calendar time.
    //!
    //! \param time Returns local time.
    extern BASE_API void GetLocalTime(
        CalendarTime& time) noexcept;

    extern BASE_API uint64_t GetSystemTime() noexcept;

    extern BASE_API uint64_t GetLocalTime() noexcept;

    extern BASE_API uint64_t GetTimestampResolution() noexcept;

    extern BASE_API uint64_t GetTimestamp() noexcept;

    extern BASE_API uint64_t GetMonotonic() noexcept;

    extern BASE_API double GetSeconds() noexcept;
}


// =================================================================================================
//
// System message dialog API.
//

namespace Graphyte::System
{
    //! \brief Represents available message dialog types.
    enum class MessageDialogType
    {
        Ok,
        OkCancel,
        YesNo,
        YesNoCancel,
        CancelTryContinue,
    };


    //! \brief Represents possible message dialog results.
    enum struct MessageDialogResult
    {
        None,
        Ok,
        Yes,
        No,
        Cancel,
        Try,
        Continue,
    };


    //! \brief Represents available message dialog images.
    enum struct MessageDialogImage
    {
        None,
        Error,
        Warning,
        Information,
    };


    //! \brief Shows native message dialog
    //!
    //! \param title   Provides title of message dialog.
    //! \param message Provides message of message dialog.
    //! \param type    Provides type of message dialog
    //! \param image   Provides image type.
    //!
    //! \return  The message dialog result.
    BASE_API MessageDialogResult ShowMessageDialog(
        std::string_view title,
        std::string_view message,
        MessageDialogType type   = MessageDialogType::Ok,
        MessageDialogImage image = MessageDialogImage::None) noexcept;
}
