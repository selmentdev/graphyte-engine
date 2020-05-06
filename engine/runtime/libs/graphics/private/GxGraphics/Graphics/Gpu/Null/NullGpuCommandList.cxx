#include "NullGpuCommandList.hxx"
#include "NullGpuDevice.hxx"
#include "NullGpuRenderTarget.hxx"
#include "NullGpuGraphicsPipelineState.hxx"
#include "NullGpuVertexBuffer.hxx"
#include "NullGpuIndexBuffer.hxx"
#include "NullGpuSampler.hxx"
#include "NullGpuUniformBuffer.hxx"
#include "NullGpuTexture.hxx"
#include "NullGpuResourceSet.hxx"
#include "NullGpuRenderTarget.hxx"

namespace Graphyte::Graphics
{
    GpuCommandListHandle NullGpuDevice::GetIntermediateCommandList() const noexcept
    {
        return m_ImmediateCommandList;
    }

    GpuCommandListHandle NullGpuDevice::CreateCommandList() noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyCommandList(
        [[maybe_unused]] GpuCommandListHandle handle
    ) noexcept
    {
    }

    void NullGpuDevice::PlayCommandList(
        [[maybe_unused]] GpuCommandListHandle handle
    ) const noexcept
    {
    }
}

namespace Graphyte::Graphics
{
    void NullGpuCommandList::BindRenderTarget(
        [[maybe_unused]] GpuRenderTargetHandle handle
    ) noexcept
    {
    }

    void NullGpuCommandList::BindGraphicsPipelineState(
        [[maybe_unused]] GpuGraphicsPipelineStateHandle handle
    ) noexcept
    {
    }

    void NullGpuCommandList::BindVertexBuffer(
        [[maybe_unused]] GpuVertexBufferHandle handle,
        [[maybe_unused]] uint32_t slot,
        [[maybe_unused]] uint32_t stride,
        [[maybe_unused]] uint32_t offset
    ) noexcept
    {
    }

    void NullGpuCommandList::BindIndexBuffer(
        [[maybe_unused]] GpuIndexBufferHandle handle,
        [[maybe_unused]] uint32_t offset,
        [[maybe_unused]] bool short_indices
    ) noexcept
    {
    }

    void NullGpuCommandList::Draw(
        [[maybe_unused]] uint32_t vertex_count,
        [[maybe_unused]] uint32_t start_vertex_location
    ) noexcept
    {
    }
    
    void NullGpuCommandList::DrawIndexed(
        [[maybe_unused]] uint32_t index_count,
        [[maybe_unused]] uint32_t start_index_location,
        [[maybe_unused]] int32_t base_vertex_location
    ) noexcept
    {
    }

    void NullGpuCommandList::DrawInstanced(
        [[maybe_unused]] uint32_t vertex_count_per_instance,
        [[maybe_unused]] uint32_t instance_count,
        [[maybe_unused]] uint32_t start_vertex_location,
        [[maybe_unused]] uint32_t start_instance_location
    ) noexcept
    {
    }

    void NullGpuCommandList::DrawIndexedInstanced(
        [[maybe_unused]] uint32_t index_count_per_instance,
        [[maybe_unused]] uint32_t instance_count,
        [[maybe_unused]] uint32_t start_index_location,
        [[maybe_unused]] int32_t base_vertex_location,
        [[maybe_unused]] uint32_t start_instance_location
    ) noexcept
    {
    }

    void NullGpuCommandList::DispatchCompute(
        [[maybe_unused]] uint32_t threadGroupCountX,
        [[maybe_unused]] uint32_t threadGroupCountY,
        [[maybe_unused]] uint32_t threadGroupCountZ
    ) noexcept
    {
    }
}
