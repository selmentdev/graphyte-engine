#pragma once
#include <GxGraphics/Graphics.module.hxx>
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>

namespace Graphyte::Graphics
{
    class GRAPHICS_API GpuCommandList
    {
    public:
        GpuCommandList() noexcept;

        virtual ~GpuCommandList() noexcept;

    public:
        virtual void BindRenderTarget(
            GpuRenderTargetHandle handle) noexcept = 0;

    public:
        virtual void BindGraphicsPipelineState(
            GpuGraphicsPipelineStateHandle handle) noexcept = 0;

        virtual void BindResourceSet(
            GpuResourceSetHandle handle) noexcept = 0;

    public:
        virtual void BindVertexBuffer(
            GpuVertexBufferHandle handle,
            uint32_t slot,
            uint32_t stride,
            uint32_t offset) noexcept = 0;

        virtual void BindIndexBuffer(
            GpuIndexBufferHandle handle,
            uint32_t offset,
            bool short_indices) noexcept = 0;

    public:
        virtual void Draw(
            uint32_t vertex_count,
            uint32_t start_vertex_location) noexcept = 0;

        virtual void DrawIndexed(
            uint32_t index_count,
            uint32_t start_index_location,
            int32_t base_vertex_location) noexcept = 0;

        virtual void DrawInstanced(
            uint32_t vertex_count_per_instance,
            uint32_t instance_count,
            uint32_t start_vertex_location,
            uint32_t start_instance_location) noexcept = 0;

        virtual void DrawIndexedInstanced(
            uint32_t index_count_per_instance,
            uint32_t instance_count,
            uint32_t start_index_location,
            int32_t base_vertex_location,
            uint32_t start_instance_location) noexcept = 0;

    public:
        virtual void DispatchCompute(
            uint32_t threadGroupCountX,
            uint32_t threadGroupCountY,
            uint32_t threadGroupCountZ) noexcept = 0;

    public:
        virtual void BeginOcclusionQuery(
            GpuOcclusionQueryHandle handle) noexcept = 0;

        virtual void EndOcclusionQuery(
            GpuOcclusionQueryHandle handle) noexcept = 0;

        virtual bool GetOcclusionQueryResult(
            GpuOcclusionQueryHandle handle,
            uint64_t& result,
            bool wait) noexcept = 0;
    };
}
