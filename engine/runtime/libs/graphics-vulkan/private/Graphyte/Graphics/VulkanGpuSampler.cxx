#include "VulkanGpuSampler.hxx"
#include "VulkanGpuDevice.hxx"
#include "VulkanGpuTypeMapping.hxx"

namespace Graphyte::Graphics
{
    GpuSamplerHandle VulkanGpuDevice::CreateSampler(
        const GpuSamplerCreateArgs& args
    ) noexcept
    {

        VkSamplerCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        ci.magFilter = VK_FILTER_LINEAR;
        ci.minFilter = VK_FILTER_LINEAR;
        ci.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        ci.addressModeU = VulkanGpuTypeMapping::TextureAddressMode(args.AddressU);
        ci.addressModeV = VulkanGpuTypeMapping::TextureAddressMode(args.AddressV);
        ci.addressModeW = VulkanGpuTypeMapping::TextureAddressMode(args.AddressW);
        ci.mipLodBias = args.MipLodBias;
        ci.anisotropyEnable = args.MaxAnisotropy > 0.0F ? VK_TRUE : VK_FALSE;
        ci.maxAnisotropy = static_cast<float>(args.MaxAnisotropy);
        ci.compareEnable = args.CompareOp != GpuCompareOperation::Never ? VK_TRUE : VK_FALSE;
        ci.compareOp = VulkanGpuTypeMapping::ComparizonFunction(args.CompareOp);
        ci.minLod = args.MinLod;
        ci.maxLod = args.MaxLod;
        ci.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
        ci.unnormalizedCoordinates = VK_FALSE;

        VkSampler resource{ VK_NULL_HANDLE };

        GPU_VK_VALIDATE(vkCreateSampler(
            m_Device,
            &ci,
            nullptr,
            &resource
        ));

        auto native = new VulkanGpuSampler();
        native->m_Resource = resource;
        return native;
    }

    void VulkanGpuDevice::DestroySampler(
        GpuSamplerHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<VulkanGpuSampler*>(handle);
        vkDestroySampler(
            m_Device,
            native->m_Resource,
            nullptr
        );
        delete native;
    }
}
