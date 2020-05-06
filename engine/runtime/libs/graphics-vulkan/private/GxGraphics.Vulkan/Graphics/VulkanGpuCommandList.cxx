#include "VulkanGpuDevice.hxx"
#include "VulkanGpuCommandList.hxx"
#include "VulkanGpuGraphicsPipelineState.hxx"
#include "VulkanGpuVertexBuffer.hxx"
#include "VulkanGpuIndexBuffer.hxx"
#include "VulkanGpuViewport.hxx"

namespace Graphyte::Graphics
{
    GpuCommandListHandle VulkanGpuDevice::GetIntermediateCommandList() const noexcept
    {
        return m_CommandList;
    }

    GpuCommandListHandle VulkanGpuDevice::CreateCommandList() noexcept
    {
        return m_CommandList;
    }

    void VulkanGpuDevice::DestroyCommandList(GpuCommandListHandle handle) noexcept
    {
        (void)handle;
    }

    void VulkanGpuDevice::PlayCommandList(GpuCommandListHandle handle) const noexcept
    {
        (void)handle;
    }
}

namespace Graphyte::Graphics
{
    void VulkanGpuCommandList::BindRenderTarget(
        GpuRenderTargetHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        //auto native = static_cast<VulkanGpuViewport*>(handle);

        VkRenderPassBeginInfo desc{
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .pNext = nullptr,
            .renderPass = VK_NULL_HANDLE,
            .framebuffer = VK_NULL_HANDLE,
            .renderArea = {
                .offset = {
                    .x = 0,
                    .y = 0,
                },
                .extent = {
                    .width = 0,
                    .height = 0,
                }
            },
            .clearValueCount = 0,
            .pClearValues = nullptr
        };

        vkCmdBeginRenderPass(
            m_CommandBuffer,
            &desc,
            VK_SUBPASS_CONTENTS_INLINE
        );
    }

    void VulkanGpuCommandList::BindGraphicsPipelineState(
        GpuGraphicsPipelineStateHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<VulkanGpuGraphicsPipelineState*>(handle);

        vkCmdBindPipeline(
            m_CommandBuffer,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            native->m_Pipeline
        );
    }

    void VulkanGpuCommandList::BindVertexBuffer(
        GpuVertexBufferHandle handle,
        uint32_t slot,
        [[maybe_unused]] uint32_t stride,
        uint32_t offset
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<VulkanGpuVertexBuffer*>(handle);

        VkDeviceSize vk_offsets{ offset };

        vkCmdBindVertexBuffers(
            m_CommandBuffer,
            slot,
            1,
            &native->m_Resource,
            &vk_offsets
        );
    }

    void VulkanGpuCommandList::BindIndexBuffer(
        GpuIndexBufferHandle handle,
        uint32_t offset,
        bool short_indices
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<VulkanGpuIndexBuffer*>(handle);

        vkCmdBindIndexBuffer(
            m_CommandBuffer,
            native->m_Resource,
            VkDeviceSize{ offset },
            short_indices
                ? VK_INDEX_TYPE_UINT16
                : VK_INDEX_TYPE_UINT32
        );
    }

    void VulkanGpuCommandList::Draw(
        uint32_t vertex_count,
        uint32_t start_vertex_location
    ) noexcept
    {
        vkCmdDraw(
            m_CommandBuffer,
            vertex_count,
            1,
            start_vertex_location,
            0
        );
    }

    void VulkanGpuCommandList::DrawIndexed(
        uint32_t index_count,
        uint32_t start_index_location,
        int32_t base_vertex_location
    ) noexcept
    {
        vkCmdDrawIndexed(
            m_CommandBuffer,
            index_count,
            1,
            start_index_location,
            base_vertex_location,
            0
        );
    }

    void VulkanGpuCommandList::DrawInstanced(
        uint32_t vertex_count_per_instance,
        uint32_t instance_count,
        uint32_t start_vertex_location,
        uint32_t start_instance_location
    ) noexcept
    {
        vkCmdDraw(
            m_CommandBuffer,
            vertex_count_per_instance,
            instance_count,
            start_vertex_location,
            start_instance_location
        );
    }

    void VulkanGpuCommandList::DrawIndexedInstanced(
        uint32_t index_count_per_instance,
        uint32_t instance_count,
        uint32_t start_index_location,
        int32_t base_vertex_location,
        uint32_t start_instance_location
    ) noexcept
    {
        vkCmdDrawIndexed(
            m_CommandBuffer,
            index_count_per_instance,
            instance_count,
            start_index_location,
            base_vertex_location,
            start_instance_location
        );
    }

    void VulkanGpuCommandList::DispatchCompute(
        uint32_t threadGroupCountX,
        uint32_t threadGroupCountY,
        uint32_t threadGroupCountZ
    ) noexcept
    {
        vkCmdDispatch(
            m_CommandBuffer,
            threadGroupCountX,
            threadGroupCountY,
            threadGroupCountZ
        );
    }
}
