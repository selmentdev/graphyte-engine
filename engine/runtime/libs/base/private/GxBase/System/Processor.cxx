#include "Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API ProcessorArchitecture GetProcessorArchitecture() noexcept
    {
        return System::CurrentArchitecture;
    }

    BASE_API bool HasProcessorFeature(ProcessorFeature feature) noexcept
    {
        return Impl::GProcessorFeatureSet.Has(feature);
    }

    BASE_API size_t GetIoWorkerThreads() noexcept
    {
        return Impl::GIoWorkerThreads;
    }

    BASE_API size_t GetWorkerThreads() noexcept
    {
        return Impl::GWorkerThreads;
    }

    BASE_API size_t GetPhysicalCores() noexcept
    {
        return Impl::GPhysicalCores;
    }

    BASE_API size_t GetLogicalCores() noexcept
    {
        return Impl::GLogicalCores;
    }

    BASE_API size_t GetProcessorCachelineSize() noexcept
    {
        //
        // Note:
        //      Some platforms may have CPUs with multiple CPUs with different cache line sizes.
        //
        //      This value should be validated at initialization.
        //

        return GRAPHYTE_CACHELINE_SIZE;
    }

    BASE_API std::string_view GetProcessorVendor() noexcept
    {
        return Impl::GProcessorVendor;
    }

    BASE_API std::string_view GetProcessorBrand() noexcept
    {
        return Impl::GProcessorBrand;
    }
}
