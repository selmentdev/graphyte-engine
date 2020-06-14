#include "D3D11GpuCommandList.hxx"
#include "D3D11GpuDevice.hxx"
#include "D3D11GpuRenderTarget.hxx"
#include "D3D11GpuGraphicsPipelineState.hxx"
#include "D3D11GpuVertexBuffer.hxx"
#include "D3D11GpuIndexBuffer.hxx"
#include "D3D11GpuSampler.hxx"
#include "D3D11GpuUniformBuffer.hxx"
#include "D3D11GpuTexture.hxx"
#include "D3D11GpuResourceSet.hxx"
#include "D3D11GpuRenderTarget.hxx"

namespace Graphyte::Graphics
{
    GpuCommandListHandle D3D11GpuDevice::GetIntermediateCommandList() const noexcept
    {
        return m_ImmediateCommandList;
    }

    GpuCommandListHandle D3D11GpuDevice::CreateCommandList() noexcept
    {
        return nullptr;
    }

    void D3D11GpuDevice::DestroyCommandList(
        GpuCommandListHandle handle) noexcept
    {
        (void)handle;
    }

    void D3D11GpuDevice::PlayCommandList(
        GpuCommandListHandle handle) const noexcept
    {
        (void)handle;
    }
}

namespace Graphyte::Graphics
{
    void D3D11GpuCommandList::BindRenderTarget(
        GpuRenderTargetHandle handle) noexcept
    {
        m_CurrentRenderTarget = handle;

        auto native = static_cast<D3D11GpuRenderTarget*>(handle);

        m_Context->OMSetRenderTargets(
            native->m_Colors,
            native->m_Color,
            native->m_Depth);

        m_Context->ClearDepthStencilView(
            native->m_Depth,
            D3D11_CLEAR_DEPTH,
            1.0F,
            0);

        D3D11_VIEWPORT viewport{
            .TopLeftX = 0.0F,
            .TopLeftY = 0.0F,
            .Width    = static_cast<float>(native->m_Width),
            .Height   = static_cast<float>(native->m_Height),
            .MinDepth = 0.0F,
            .MaxDepth = 1.0F,
        };

        m_Context->RSSetViewports(1, &viewport);
        m_Context->RSSetScissorRects(0, nullptr);
    }

    void D3D11GpuCommandList::BindGraphicsPipelineState(
        GpuGraphicsPipelineStateHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuGraphicsPipelineState*>(handle);

        m_Context->RSSetState(native->m_RasterizerState);

        m_Context->OMSetBlendState(
            native->m_BlendState,
            reinterpret_cast<const float*>(&native->m_BlendState_BlendFactors),
            native->m_BlendState_SampleMask);

        m_Context->OMSetDepthStencilState(native->m_DepthStencilState, 0);
        m_Context->IASetInputLayout(native->m_InputLayout);

        m_Context->VSSetShader(native->m_VS, nullptr, 0);
        m_Context->PSSetShader(native->m_PS, nullptr, 0);
        m_Context->GSSetShader(native->m_GS, nullptr, 0);
        m_Context->DSSetShader(native->m_DS, nullptr, 0);
        m_Context->HSSetShader(native->m_HS, nullptr, 0);

        m_Context->IASetPrimitiveTopology(native->m_PrimitiveTopology);
    }

    void D3D11GpuCommandList::BindVertexBuffer(
        GpuVertexBufferHandle handle,
        uint32_t slot,
        uint32_t stride,
        uint32_t offset) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuVertexBuffer*>(handle);

        UINT strides[] = { stride };
        UINT offsets[] = { offset };

        m_Context->IASetVertexBuffers(
            slot,
            1,
            &native->m_Resource,
            strides,
            offsets);
    }

    void D3D11GpuCommandList::BindIndexBuffer(
        GpuIndexBufferHandle handle,
        uint32_t offset,
        bool short_indices) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuIndexBuffer*>(handle);

        DXGI_FORMAT format = short_indices
                                 ? DXGI_FORMAT_R16_UINT
                                 : DXGI_FORMAT_R32_UINT;

        m_Context->IASetIndexBuffer(
            native->m_Resource,
            format,
            offset);
    }

    void D3D11GpuCommandList::Draw(
        uint32_t vertex_count,
        uint32_t start_vertex_location) noexcept
    {
        m_Context->Draw(
            vertex_count,
            start_vertex_location);
    }

    void D3D11GpuCommandList::DrawIndexed(
        uint32_t index_count,
        uint32_t start_index_location,
        int32_t base_vertex_location) noexcept
    {
        m_Context->DrawIndexed(
            index_count,
            start_index_location,
            base_vertex_location);
    }

    void D3D11GpuCommandList::DrawInstanced(
        uint32_t vertex_count_per_instance,
        uint32_t instance_count,
        uint32_t start_vertex_location,
        uint32_t start_instance_location) noexcept
    {
        m_Context->DrawInstanced(
            vertex_count_per_instance,
            instance_count,
            start_vertex_location,
            start_instance_location);
    }

    void D3D11GpuCommandList::DrawIndexedInstanced(
        uint32_t index_count_per_instance,
        uint32_t instance_count,
        uint32_t start_index_location,
        int32_t base_vertex_location,
        uint32_t start_instance_location) noexcept
    {
        m_Context->DrawIndexedInstanced(
            index_count_per_instance,
            instance_count,
            start_index_location,
            base_vertex_location,
            start_instance_location);
    }

    void D3D11GpuCommandList::DispatchCompute(
        uint32_t threadGroupCountX,
        uint32_t threadGroupCountY,
        uint32_t threadGroupCountZ) noexcept
    {
        m_Context->Dispatch(
            threadGroupCountX,
            threadGroupCountY,
            threadGroupCountZ);
    }
}
