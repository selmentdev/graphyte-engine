#include "D3D11GpuOcclusionQuery.hxx"
#include "D3D11GpuDevice.hxx"
#include "D3D11GpuCommandList.hxx"

namespace Graphyte::Graphics
{
    void D3D11GpuCommandList::BeginOcclusionQuery(
        GpuOcclusionQueryHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuOcclusionQuery*>(handle);
        GX_ASSERT(native->m_Query != nullptr);

        m_Context->Begin(native->m_Query);
    }

    void D3D11GpuCommandList::EndOcclusionQuery(
        GpuOcclusionQueryHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuOcclusionQuery*>(handle);
        GX_ASSERT(native->m_Query != nullptr);

        m_Context->End(native->m_Query);
    }

    bool D3D11GpuCommandList::GetOcclusionQueryResult(
        GpuOcclusionQueryHandle handle,
        uint64_t& result,
        bool wait) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuOcclusionQuery*>(handle);
        GX_ASSERT(native->m_Query != nullptr);

        HRESULT hr;

        do
        {
            hr = m_Context->GetData(
                native->m_Query,
                &result,
                sizeof(result),
                0);
        } while (hr == S_FALSE && wait);

        return SUCCEEDED(hr);
    }
}

namespace Graphyte::Graphics
{
    GpuOcclusionQueryHandle D3D11GpuDevice::CreateOcclusionQuery() noexcept
    {
        auto native = new D3D11GpuOcclusionQuery();

        D3D11_QUERY_DESC desc{
            .Query     = D3D11_QUERY_OCCLUSION,
            .MiscFlags = 0,
        };

        GPU_DX_VALIDATE(m_Device->CreateQuery(&desc, &native->m_Query));

        return native;
    }

    void D3D11GpuDevice::DestroyOcclusionQuery(
        GpuOcclusionQueryHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuOcclusionQuery*>(handle);
        GX_ASSERT(native->m_Query != nullptr);

        this->DeferResourceRelease(native->m_Query);
        delete native;
    }
}
