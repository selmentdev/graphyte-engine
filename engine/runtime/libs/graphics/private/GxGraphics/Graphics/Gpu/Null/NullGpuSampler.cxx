#include "NullGpuSampler.hxx"
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuSamplerHandle NullGpuDevice::CreateSampler(
        const GpuSamplerCreateArgs& args) noexcept
    {
        (void)args;
        return nullptr;
    }

    void NullGpuDevice::DestroySampler(
        GpuSamplerHandle handle) noexcept
    {
        (void)handle;
    }
}
