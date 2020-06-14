#include <GxBase/Base.module.hxx>

#include "../Platform.impl.hxx"

#if GRAPHYTE_PLATFORM_LINUX && (GRAPHYTE_CPU_X86_64 || GRAPHYTE_CPU_X86_32)
#include <cpuid.h>
#endif

namespace Graphyte::System::Impl
{
    struct CpuidInfo final
    {
        union
        {
            uint32_t as_uint32[4];
            int as_int[4];
            char string[16];
            struct
            {
                uint32_t rax;
                uint32_t rbx;
                uint32_t rcx;
                uint32_t rdx;
            } regs;
        };

        CpuidInfo(uint32_t leaf, uint32_t subleaf) noexcept
        {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
            __cpuidex(as_int, static_cast<int>(leaf), static_cast<int>(subleaf));
#elif GRAPHYTE_PLATFORM_LINUX
            __cpuid_count(leaf, subleaf, as_int[0], as_int[1], as_int[2], as_int[3]);
#endif
        }
    };

    void DetectProcessorFeatures() noexcept
    {
        //
        // Get brand and max CPUID.
        //

        CpuidInfo max_cpuid_std{ 0x0000'0000, 0 };

        Impl::GProcessorVendor.assign(&max_cpuid_std.string[4], 4);
        Impl::GProcessorVendor.append(&max_cpuid_std.string[12], 4);
        Impl::GProcessorVendor.append(&max_cpuid_std.string[8], 4);


        //
        // Get max extended CPUID.
        //

        CpuidInfo max_cpuid_ext{ 0x8000'0000, 0 };


        //
        // Get CPU Brand.
        //

        if (max_cpuid_ext.regs.rax >= 0x8000'0004)
        {
            CpuidInfo brand1{ 0x8000'0002, 0 };
            CpuidInfo brand2{ 0x8000'0003, 0 };
            CpuidInfo brand3{ 0x8000'0004, 0 };

            Impl::GProcessorBrand.assign(&brand1.string[0], strnlen(&brand1.string[0], 16));
            Impl::GProcessorBrand.append(&brand2.string[0], strnlen(&brand2.string[0], 16));
            Impl::GProcessorBrand.append(&brand3.string[0], strnlen(&brand3.string[0], 16));
        }

        uint32_t apic{ 0 };

        if (max_cpuid_std.regs.rax >= 0x0000'0001)
        {
            CpuidInfo std_features{ 0x0000'0001, 0 };

            uint32_t stepping = std_features.regs.rax & 0xF;
            uint32_t fbase    = (std_features.regs.rax >> 8) & 0xF;
            uint32_t mbase    = (std_features.regs.rax >> 4) & 0xF;
            uint32_t family   = ((fbase == 0xF) || (fbase == 0)) ? fbase + (std_features.regs.rax >> 20) & 0xFF : fbase;
            uint32_t model    = ((fbase == 0xF) || (fbase == 6 /*&& cf.probablyIntel*/)) ? mbase + ((std_features.regs.rax >> 12) & 0xF0) : mbase;

            (void)stepping;
            (void)family;
            (void)model;

            apic = std_features.regs.rbx;

            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SSE3, (std_features.regs.rcx & (1U << 0)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SSSE3, (std_features.regs.rcx & (1U << 9)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::FMA3, (std_features.regs.rcx & (1U << 12)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SSE41, (std_features.regs.rcx & (1U << 19)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SSE42, (std_features.regs.rcx & (1U << 20)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::CRC32, (std_features.regs.rcx & (1U << 20)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::MOVBE, (std_features.regs.rcx & (1U << 22)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::POPCNT, (std_features.regs.rcx & (1U << 23)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AES, (std_features.regs.rcx & (1U << 25)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::OSXSAVE, (std_features.regs.rcx & (1U << 27)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX, (std_features.regs.rcx & (1U << 28)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::F16C, (std_features.regs.rcx & (1U << 29)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::RDRAND, (std_features.regs.rcx & (1U << 30)) != 0);

            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SSE, (std_features.regs.rdx & (1U << 25)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SSE2, (std_features.regs.rdx & (1U << 26)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::HTT, (std_features.regs.rdx & (1U << 28)) != 0);
        }

        if (max_cpuid_std.regs.rax >= 0x0000'0007)
        {
            CpuidInfo ext_features{ 7, 0 };

            Impl::GProcessorFeatureSet.Set(ProcessorFeature::BMI1, (ext_features.regs.rbx & (1U << 3)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX2, (ext_features.regs.rbx & (1U << 5)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::BMI2, (ext_features.regs.rbx & (1U << 8)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512F, (ext_features.regs.rbx & (1U << 16)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512DQ, (ext_features.regs.rbx & (1U << 17)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::RDSEED, (ext_features.regs.rbx & (1U << 18)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512IFMA, (ext_features.regs.rbx & (1U << 21)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512PF, (ext_features.regs.rbx & (1U << 26)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512ER, (ext_features.regs.rbx & (1U << 27)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512CD, (ext_features.regs.rbx & (1U << 28)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA, (ext_features.regs.rbx & (1U << 29)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512BW, (ext_features.regs.rbx & (1U << 30)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512VL, (ext_features.regs.rbx & (1U << 31)) != 0);

            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512VBMI, (ext_features.regs.rcx & (1U << 1)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512VBMI2, (ext_features.regs.rcx & (1U << 6)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::VAES, (ext_features.regs.rcx & (1U << 9)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::CLMUL, (ext_features.regs.rcx & (1U << 10)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512VNNI, (ext_features.regs.rcx & (1U << 11)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512BITALG, (ext_features.regs.rcx & (1U << 12)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512VP, (ext_features.regs.rcx & (1U << 14)) != 0);

            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512QVNNIW, (ext_features.regs.rdx & (1U << 2)) != 0);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AVX512QFMA, (ext_features.regs.rdx & (1U << 3)) != 0);
        }

        [[maybe_unused]] uint32_t max_threads      = 0;
        [[maybe_unused]] uint32_t max_cores        = 0;
        [[maybe_unused]] uint32_t threads_per_core = 0;

        if (max_cpuid_std.regs.rax >= 0x0000'000BU)
        {
            uint32_t a{};
            uint32_t b{};
            uint32_t level{};

            do
            {
                CpuidInfo cores_info{ 0x0000'000B, level };

                a = cores_info.regs.rax;
                b = cores_info.regs.rbx;

                if (b != 0)
                {
                    if (level == 0)
                    {
                        threads_per_core = b & 0xFFFF;
                    }
                    else if (level == 1)
                    {
                        max_threads = b & 0xFFFF;
                        max_cores   = max_threads / threads_per_core;
                    }
                }

                ++level;
            } while (a != 0 || b != 0);
        }
        else
        {
            max_threads = (apic >> 16) & 0xff;
        }

        // ProcessorFeature::FMA4,
        // ProcessorFeature::SSE4A,


        //
        // Setup support for denormals.
        //

        _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    }
}
