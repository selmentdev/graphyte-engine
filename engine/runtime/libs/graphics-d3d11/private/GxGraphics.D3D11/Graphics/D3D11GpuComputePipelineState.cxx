#include "D3D11GpuComputePipelineState.hxx"
#include "D3D11GpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuComputePipelineStateHandle D3D11GpuDevice::CreateComputePipelineState(
        const GpuComputePipelineStateCreateArgs& args,
        const GpuResourceSetDesc& layout
    ) noexcept
    {
        (void)args;
        (void)layout;
        return new D3D11GpuComputePipelineState();
    }

    void D3D11GpuDevice::DestroyComputePipelineState(
        GpuComputePipelineStateHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuComputePipelineState*>(handle);
        delete native;
    }
}
