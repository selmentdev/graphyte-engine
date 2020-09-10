#include <GxBase/Base.module.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System::Impl
{
    void DetectProcessorFeatures() noexcept
    {
#if GX_CPU_ARM_64

        Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::ASIMD, true);
        Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::FP, true);

        if (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_AVAILABLE) != FALSE)
        {
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::AES, true);
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::SHA1, true);
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::SHA2, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_V8_CRC32_INSTRUCTIONS_AVAILABLE) != FALSE)
        {
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::CRC32, true);
        }

#elif GX_CPU_ARM_32

        Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::ARMv7, true);


        //
        // Don't know how to detect them
        //

        Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::AES, false);
        Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::CRC32, false);
        Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::SHA1, false);
        Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::SHA2, false);

        if (IsProcessorFeaturePresent(PF_ARM_VFP_32_REGISTERS_AVAILABLE) != FALSE)
        {
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::VFP_D32, true);
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::VFP_FP16, true);
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::VFPv2, true);
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::VFPv3, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_DIVIDE_INSTRUCTION_AVAILABLE) != FALSE)
        {
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::IDIV_ARM, true);
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::IDIV_THUMB2, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_NEON_INSTRUCTIONS_AVAILABLE) != FALSE)
        {
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::NEON, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_FMAC_INSTRUCTIONS_AVAILABLE) != FALSE)
        {
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::NEON_FMA, true);
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::VFP_FMA, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_64BIT_LOADSTORE_ATOMIC) != FALSE)
        {
            Impl::g_ProcessorFeatureSet.Set(ProcessorFeature::LDREX_STREX, true);
        }

#else
#error "Not supported"
#endif
    }
}
