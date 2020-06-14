#include "NullGpuDevice.hxx"
#include "NullGpuShader.hxx"

namespace Graphyte::Graphics
{
    GpuShaderHandle NullGpuDevice::CreateShader(
        [[maybe_unused]] GpuShaderStage stage,
        [[maybe_unused]] GpuShaderBytecode bytecode,
        [[maybe_unused]] GpuInputLayout inputLayout) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyShader(
        [[maybe_unused]] GpuShaderHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
    }
}
