#include <GxBase/Base.module.hxx>

#include <GxBase/System.hxx>

#include "../Platform.impl.hxx"

#include <sys/auxv.h>
#include <asm/hwcap.h>

namespace Graphyte::System::Impl
{
    void DetectProcessorFeatures() noexcept
    {
        uint64_t hwcap                   = getauxval(AT_HWCAP);
        [[maybe_unused]] uint64_t hwcap2 = getauxval(AT_HWCAP2);

        GX_LOG_TRACE(LogPlatform, "HWCAP: {:016x}, HWCAP2: {:016x}\n", hwcap, hwcap2);


        if ((hwcap & HWCAP_AES) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::AES, true);
        }

        if ((hwcap & HWCAP_ASIMD) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::ASIMD, true);
        }

        if ((hwcap & HWCAP_ASIMDFHM) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::ASIMDFHM, true);
        }

        if ((hwcap & HWCAP_ASIMDHP) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::ASIMDHP, true);
        }

        if ((hwcap & HWCAP_ATOMICS) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::ATOMICS, true);
        }

        if ((hwcap & HWCAP_CRC32) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::CRC32, true);
        }

        if ((hwcap & HWCAP_FP) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::FP, true);
        }

        if ((hwcap & HWCAP_FPHP) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::FPHP, true);
        }

        if ((hwcap & HWCAP_PMULL) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::PMULL, true);
        }

        if ((hwcap & HWCAP_SHA1) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA1, true);
        }

        if ((hwcap & HWCAP_SHA2) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA2, true);
        }

        if ((hwcap & HWCAP_SHA3) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA3, true);
        }

        if ((hwcap & HWCAP_SHA512) != 0)
        {
            Impl::GProcessorFeatureSet.Set(ProcessorFeature::SHA512, true);
        }
    }
}
