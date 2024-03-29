#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/System.hxx>

namespace Graphyte::System::Impl
{
    template <typename T, size_t TBits>
    struct FeatureSet final
    {
        static constexpr size_t Bits        = TBits;
        static constexpr size_t BitsPerItem = sizeof(uint64_t) * CHAR_BIT;
        static constexpr size_t Elements    = Bits / BitsPerItem;

        std::array<uint64_t, Elements> Data{};

        void Set(T feature, bool value) noexcept
        {
            size_t const bit = static_cast<size_t>(feature);
            GX_ASSERT(bit < Bits);

            size_t const index  = bit / BitsPerItem;
            size_t const offset = bit % BitsPerItem;
            uint64_t const mask = uint64_t{ 1 } << offset;

            if (value)
            {
                this->Data[index] |= mask;
            }
            else
            {
                this->Data[index] &= ~mask;
            }
        }

        bool Has(T feature) const noexcept
        {
            size_t const bit = static_cast<size_t>(feature);
            GX_ASSERT(bit < Bits);

            size_t const index  = bit / BitsPerItem;
            size_t const offset = bit % BitsPerItem;
            uint64_t const mask = uint64_t{ 1 } << offset;

            return (this->Data[index] & mask) != 0;
        }
    };

    using PlatformFeatureSet  = FeatureSet<PlatformFeature, 128>;
    using ProcessorFeatureSet = FeatureSet<ProcessorFeature, 128>;
}

namespace Graphyte::System::Impl
{
    extern std::string g_ProcessorVendor;
    extern std::string g_ProcessorBrand;

    extern ProcessorFeatureSet g_ProcessorFeatureSet;
    extern PlatformFeatureSet g_PlatformFeatureSet;

    extern MemoryProperties g_MemoryProperties;
    extern bool g_IsBuildMachine;

    extern size_t g_IoWorkerThreads;
    extern size_t g_WorkerThreads;
    extern size_t g_PhysicalCores;
    extern size_t g_LogicalCores;

    extern void DetectPlatformFeatures() noexcept;
    extern void InitializePlatform() noexcept;
    extern void FinalizePlatform() noexcept;
}
