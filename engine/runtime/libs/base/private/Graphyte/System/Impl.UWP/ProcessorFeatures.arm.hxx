#include <Graphyte/Base.module.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System::Impl
{
    void DetectProcessorFeatures() noexcept
    {
#if GRAPHYTE_CPU_ARM_64

        Impl::GProcessorFeatureSet.Set(ProcessorFeature::ASIMD, true);
        Impl::GProcessorFeatureSet.Set(ProcessorFeature::FP, true);

        if (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_AVAILABLE) != FALSE)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AES, true);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA1, true);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA2, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_V8_CRC32_INSTRUCTIONS_AVAILABLE) != FALSE)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::CRC32, true);
        }

#elif GRAPHYTE_CPU_ARM_32

        Impl::GProcessorFeatureSet.Set(ProcessorFeature::ARMv7, true);


        //
        // Don't know how to detect them
        //

        Impl::GProcessorFeatureSet.Set(ProcessorFeature::AES, false);
        Impl::GProcessorFeatureSet.Set(ProcessorFeature::CRC32, false);
        Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA1, false);
        Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA2, false);

        if (IsProcessorFeaturePresent(PF_ARM_VFP_32_REGISTERS_AVAILABLE) != FALSE)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::VFP_D32, true);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::VFP_FP16, true);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::VFPv2, true);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::VFPv3, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_DIVIDE_INSTRUCTION_AVAILABLE) != FALSE)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::IDIV_ARM, true);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::IDIV_THUMB2, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_NEON_INSTRUCTIONS_AVAILABLE) != FALSE)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::NEON, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_FMAC_INSTRUCTIONS_AVAILABLE) != FALSE)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::NEON_FMA, true);
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::VFP_FMA, true);
        }

        if (IsProcessorFeaturePresent(PF_ARM_64BIT_LOADSTORE_ATOMIC) != FALSE)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::LDREX_STREX, true);
        }

#else
#   error "Not supported"
#endif
    }
}
