#include "NullGpuComputePipelineState.hxx"
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuComputePipelineStateHandle NullGpuDevice::CreateComputePipelineState(
        [[maybe_unused]] const GpuComputePipelineStateCreateArgs& args,
        [[maybe_unused]] const GpuResourceSetDesc& layout) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyComputePipelineState(
        [[maybe_unused]] GpuComputePipelineStateHandle handle) noexcept
    {
    }
}
