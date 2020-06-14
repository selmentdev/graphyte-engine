#pragma once
#include <GxGraphics/Graphics/Gpu/GpuCommandList.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuCommandList : public GpuCommandList
    {
    public:
        NullGpuCommandList() noexcept = default;

        virtual ~NullGpuCommandList() noexcept = default;

    public:
        virtual void BindRenderTarget(
            GpuRenderTargetHandle handle) noexcept override;

    public:
        virtual void BindGraphicsPipelineState(
            GpuGraphicsPipelineStateHandle handle) noexcept override;

        virtual void BindResourceSet(
            GpuResourceSetHandle handle) noexcept override;

    public:
        virtual void BindVertexBuffer(
            GpuVertexBufferHandle handle,
            uint32_t slot,
            uint32_t stride,
            uint32_t offset) noexcept override;

        virtual void BindIndexBuffer(
            GpuIndexBufferHandle handle,
            uint32_t offset,
            bool short_indices) noexcept override;


    public:
        virtual void Draw(
            uint32_t vertex_count,
            uint32_t start_vertex_location) noexcept override;

        virtual void DrawIndexed(
            uint32_t index_count,
            uint32_t start_index_location,
            int32_t base_vertex_location) noexcept override;

        virtual void DrawInstanced(
            uint32_t vertex_count_per_instance,
            uint32_t instance_count,
            uint32_t start_vertex_location,
            uint32_t start_instance_location) noexcept override;

        virtual void DrawIndexedInstanced(
            uint32_t index_count_per_instance,
            uint32_t instance_count,
            uint32_t start_index_location,
            int32_t base_vertex_location,
            uint32_t start_instance_location) noexcept override;

    public:
        virtual void BeginOcclusionQuery(
            GpuOcclusionQueryHandle handle) noexcept override
        {
            (void)handle;
        }

        virtual void EndOcclusionQuery(
            GpuOcclusionQueryHandle handle) noexcept override
        {
            (void)handle;
        }

        virtual bool GetOcclusionQueryResult(
            GpuOcclusionQueryHandle handle,
            uint64_t& result,
            bool wait = true) noexcept override
        {
            (void)handle;
            (void)result;
            (void)wait;
            return false;
        }

    public:
        virtual void DispatchCompute(
            uint32_t threadGroupCountX,
            uint32_t threadGroupCountY,
            uint32_t threadGroupCountZ) noexcept override;
    };
}
