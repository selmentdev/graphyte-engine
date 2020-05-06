#include "VulkanGpuDevice.hxx"
#include "VulkanGpuShader.hxx"
#include <GxBase/Bitwise.hxx>

namespace Graphyte::Graphics
{
    GpuShaderHandle VulkanGpuDevice::CreateShader(
        [[maybe_unused]] GpuShaderStage stage,
        [[maybe_unused]] GpuShaderBytecode bytecode,
        [[maybe_unused]] GpuInputLayout inputLayout
    ) noexcept
    {
        GX_ASSERT(IsAligned(bytecode.Bytecode, std::align_val_t{ alignof(uint32_t) }));

        VkShaderModule resource{ VK_NULL_HANDLE };

        VkShaderModuleCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        ci.codeSize = bytecode.Size;
        ci.pCode = reinterpret_cast<const uint32_t*>(bytecode.Bytecode);

        GPU_VK_VALIDATE(vkCreateShaderModule(
            m_Device,
            &ci,
            nullptr,
            &resource
        ));

        auto result = new VulkanGpuShader();
        result->m_Resource = resource;
        result->m_Stage = stage;
        return result;
    }

    void VulkanGpuDevice::DestroyShader(
        [[maybe_unused]] GpuShaderHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuShader*>(handle);

        vkDestroyShaderModule(
            m_Device,
            native->m_Resource,
            nullptr
        );

        delete native;
    }
}
