#include "NullGpuResourceSet.hxx"
#include "NullGpuCommandList.hxx"
#include "NullGpuDevice.hxx"
#include "NullGpuUniformBuffer.hxx"
#include "NullGpuSampler.hxx"
#include "NullGpuTexture.hxx"

namespace Graphyte::Graphics
{
    void NullGpuCommandList::BindResourceSet(
        [[maybe_unused]] GpuResourceSetHandle handle) noexcept
    {
    }
}

namespace Graphyte::Graphics
{
    GpuResourceSetHandle NullGpuDevice::CreateResourceSet(
        [[maybe_unused]] const GpuResourceSetDesc& desc) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyResourceSet(
        [[maybe_unused]] GpuResourceSetHandle handle) noexcept
    {
    }

    void NullGpuDevice::UpdateResourceSet(
        [[maybe_unused]] GpuResourceSetHandle handle,
        [[maybe_unused]] const GpuResourceSetDesc& desc) noexcept
    {
    }
}
