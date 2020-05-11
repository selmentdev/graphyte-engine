#pragma once
//#include <GxGraphics/Graphics/Render/Viewport.hxx>
#include <GxGraphics/Graphics/PixelFormat.hxx>
#include "D3D12Common.hxx"

namespace Graphyte::Graphics::Render
{
    //class D3D12Viewport : public Viewport
    //{
    //    friend class D3D12RenderSystem;
    //private:
    //    class D3D12RenderSystem* m_RenderSystem;
    //    HWND m_Handle;
    //    uint32_t m_Width;
    //    uint32_t m_Height;
    //    bool m_Fullscreen;
    //    PixelFormat m_PixelFormat;
    //
    //    static constexpr const UINT FramebufferCount = 3;
    //
    //
    //    Microsoft::WRL::ComPtr<ID3D12Resource> m_RenderTargets[FramebufferCount];
    //    Microsoft::WRL::ComPtr<IDXGISwapChain3> m_SwapChain;
    //    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_RtvDescriptorHeap;
    //
    //private:
    //    DXGI_MODE_DESC GetMode() const noexcept;
    //    DXGI_MODE_DESC FindCompatibleMode() const noexcept;
    //
    //public:
    //    D3D12Viewport(class D3D12RenderSystem* render_system, HWND handle, uint32_t width, uint32_t height, bool fullscreen, PixelFormat format) noexcept;
    //    virtual ~D3D12Viewport() noexcept;
    //
    //public:
    //    void Resize() noexcept override;
    //    void Resize(uint32_t width, uint32_t height, bool fullscreen) noexcept override;
    //    bool Present(int sync_interval) noexcept override;
    //    void* GetWindowHandle() noexcept override;
    //    void Reset(bool ignore_focus) noexcept override;
    //};
}
