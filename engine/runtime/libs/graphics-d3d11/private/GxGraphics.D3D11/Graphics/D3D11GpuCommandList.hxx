#pragma once
#include <GxGraphics/Graphics/Gpu/GpuCommandList.hxx>
#include "D3D11GpuCommon.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuCommandList : public GpuCommandList
    {
    public:
        ID3D11DeviceContext* m_Context;
        ID3D11Device* m_Device;

        GpuRenderTargetHandle m_CurrentRenderTarget;

    public:
        D3D11GpuCommandList() noexcept
            : m_Context{}
            , m_Device{}
            , m_CurrentRenderTarget{}
        {
        }

    public:
        void BindRenderTarget(
            GpuRenderTargetHandle handle) noexcept final;

    public:
        void BindGraphicsPipelineState(
            GpuGraphicsPipelineStateHandle handle) noexcept final;

        void BindResourceSet(
            GpuResourceSetHandle handle) noexcept final;

    public:
        void BindVertexBuffer(
            GpuVertexBufferHandle handle,
            uint32_t slot,
            uint32_t stride,
            uint32_t offset) noexcept final;

        void BindIndexBuffer(
            GpuIndexBufferHandle handle,
            uint32_t offset,
            bool short_indices) noexcept final;

    public:
        void Draw(
            uint32_t vertex_count,
            uint32_t start_vertex_location) noexcept final;

        void DrawIndexed(
            uint32_t index_count,
            uint32_t start_index_location,
            int32_t base_vertex_location) noexcept final;

        void DrawInstanced(
            uint32_t vertex_count_per_instance,
            uint32_t instance_count,
            uint32_t start_vertex_location,
            uint32_t start_instance_location) noexcept final;

        void DrawIndexedInstanced(
            uint32_t index_count_per_instance,
            uint32_t instance_count,
            uint32_t start_index_location,
            int32_t base_vertex_location,
            uint32_t start_instance_location) noexcept final;

    public:
        void DispatchCompute(
            uint32_t threadGroupCountX,
            uint32_t threadGroupCountY,
            uint32_t threadGroupCountZ) noexcept override;

    public:
        void BeginOcclusionQuery(
            GpuOcclusionQueryHandle handle) noexcept final;

        void EndOcclusionQuery(
            GpuOcclusionQueryHandle handle) noexcept final;

        bool GetOcclusionQueryResult(
            GpuOcclusionQueryHandle handle,
            uint64_t& result,
            bool wait = true) noexcept final;
    };
}
