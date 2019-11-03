#include "Graphics.pch.hxx"
#include "NullGpuGraphicsPipelineState.hxx"
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuGraphicsPipelineStateHandle NullGpuDevice::CreateGraphicsPipelineState(
        [[maybe_unused]] const GpuGraphicsPipelineStateCreateArgs& args,
        [[maybe_unused]] const GpuResourceSetDesc& layout
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyGraphicsPipelineState(
        [[maybe_unused]] GpuGraphicsPipelineStateHandle handle
    ) noexcept
    {
        (void)handle;
    }
}
