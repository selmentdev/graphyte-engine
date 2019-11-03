#pragma once
//#include <Graphyte/Graphics/Render/RenderSystem.hxx>
//#include <Graphyte/Graphics/Render/Resource.hxx>

#include "D3D12Common.hxx"

namespace Graphyte::Graphics::Render
{
    //class D3D12RenderSystem final : public RenderSystem
    //{
    //    friend class D3D12Viewport;
    //private:
    //    Microsoft::WRL::ComPtr<IDXGIFactory4> m_Factory;
    //    Microsoft::WRL::ComPtr<IDXGIAdapter1> m_Adapter;
    //    Microsoft::WRL::ComPtr<ID3D12Device> m_Device;
    //    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueue;
    //
    //    D3D_FEATURE_LEVEL m_FeatureLevel;
    //
    //private:
    //    void InitializeD3D12() noexcept;
    //
    //public:
    //    D3D12RenderSystem() noexcept;
    //    virtual ~D3D12RenderSystem() noexcept;
    //
    //    //
    //    // Viewport support.
    //    //
    //public:
    //    ViewportRef MakeViewport(void* window_handle, uint32_t width, uint32_t height, bool fullscreen, PixelFormat format) noexcept override;
    //    void ResizeViewport(const ViewportRef& viewport, uint32_t width, uint32_t height, bool fullscreen) noexcept override;
    //    void BeginDrawViewport(const ViewportRef& viewport) noexcept override;
    //    void EndRawViewport(const ViewportRef& viewport, bool present, int interval) noexcept override;
    //
    //public:
    //    void FlushLogs() noexcept;
    //};
}
