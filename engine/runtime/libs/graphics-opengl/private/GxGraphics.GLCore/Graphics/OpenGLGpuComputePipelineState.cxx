#include "OpenGLGpuComputePipelineState.hxx"
#include "OpenGLGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuComputePipelineStateHandle OpenGLGpuDevice::CreateComputePipelineState(
        const GpuComputePipelineStateCreateArgs& args,
        const GpuResourceSetDesc& layout) noexcept
    {
        (void)args;
        (void)layout;
        return nullptr;
    }

    void OpenGLGpuDevice::DestroyComputePipelineState(
        GpuComputePipelineStateHandle handle) noexcept
    {
        (void)handle;
    }
}
