#include "D3D12Viewport.hxx"
#include "D3D12RenderSystem.hxx"
#include "D3D12PixelFormat.hxx"

#if false

namespace Graphyte::Graphics::Render
{
    DXGI_MODE_DESC D3D12Viewport::GetMode() const noexcept
    {
        DXGI_MODE_DESC desc{};
        desc.Width = m_Width;
        desc.Height = m_Height;
        desc.RefreshRate.Numerator = 0;
        desc.RefreshRate.Denominator = 0;
        desc.Format = D3D12GetRenderTargetFormat(m_PixelFormat);
        desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        return desc;
    }

    DXGI_MODE_DESC D3D12Viewport::FindCompatibleMode() const noexcept
    {
        DXGI_MODE_DESC mode = GetMode();

        Microsoft::WRL::ComPtr<IDXGIOutput> output;
        D3D12Verify(m_SwapChain->GetContainingOutput(output.GetAddressOf()));

        DXGI_MODE_DESC result;
        output->FindClosestMatchingMode(&mode, &result, nullptr);
        return result;
    }

    D3D12Viewport::D3D12Viewport(D3D12RenderSystem* render_system, HWND handle, uint32_t width, uint32_t height, bool fullscreen, PixelFormat format) noexcept
        : m_RenderSystem{ render_system }
        , m_Handle{ handle }
        , m_Width{ width }
        , m_Height{ height }
        , m_Fullscreen{ fullscreen }
        , m_PixelFormat{ format }
    {
        DXGI_SWAP_CHAIN_DESC sd{};
        sd.BufferDesc = GetMode();
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
        sd.BufferCount = FramebufferCount;
        sd.OutputWindow = handle;
        sd.Windowed = fullscreen ? FALSE : TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.Flags = 0;

        Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain{};
        D3D12Verify(m_RenderSystem->m_Factory->CreateSwapChain(
            m_RenderSystem->m_CommandQueue.Get(),
            &sd,
            swapchain.GetAddressOf()
        ));

        m_SwapChain = static_cast<IDXGISwapChain3*>(swapchain.Get());

        GX_LOG(LogD3D12Render, Trace, "Created viewport\n");

        m_RenderSystem->m_Factory->MakeWindowAssociation(m_Handle, DXGI_MWA_NO_WINDOW_CHANGES);

        Resize(width, height, fullscreen);

        D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc{};
        rtv_heap_desc.NumDescriptors = 3;
        rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtv_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

        D3D12Verify(m_RenderSystem->m_Device->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(&m_RtvDescriptorHeap)));

        {
            auto rtv_descriptor_size = m_RenderSystem->m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

            CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle(m_RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

            for (UINT i = 0; i < FramebufferCount; ++i)
            {
                D3D12Verify(m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&m_RenderTargets[i])));

                m_RenderSystem->m_Device->CreateRenderTargetView(m_RenderTargets[i].Get(), nullptr, rtv_handle);
                rtv_handle.Offset(1, rtv_descriptor_size);
            }

        }
    }

    D3D12Viewport::~D3D12Viewport() noexcept
    {
        GX_ASSERT(m_SwapChain != nullptr);
        D3D12Verify(m_SwapChain->SetFullscreenState(FALSE, nullptr));
    }


    void D3D12Viewport::Resize() noexcept
    {
        //m_RenderSystem->m_
    }

    void D3D12Viewport::Resize(uint32_t width, uint32_t height, bool fullscreen) noexcept
    {
        BOOL current_fullscreen{};
        D3D12Verify(m_SwapChain->GetFullscreenState(&current_fullscreen, nullptr));
        m_Width = width;
        m_Height = height;
        m_Fullscreen = fullscreen;

        //m_IsValid = false;

        GX_LOG(LogD3D12Render, Trace, "DXGI: begin resize\n");
        if (fullscreen)
        {
            DXGI_MODE_DESC closest = FindCompatibleMode();

            m_SwapChain->SetFullscreenState(TRUE, nullptr);
            m_SwapChain->ResizeTarget(&closest);
            Resize();
        }
        else
        {
            DXGI_MODE_DESC closest = FindCompatibleMode();
            m_SwapChain->ResizeTarget(&closest);

            Resize();
            m_SwapChain->SetFullscreenState(FALSE, nullptr);
        }
        GX_LOG(LogD3D12Render, Trace, "DXGI: end resize\n");
    }

    bool D3D12Viewport::Present(int sync_interval) noexcept
    {
        (void)sync_interval;
        return true;
    }

    void* D3D12Viewport::GetWindowHandle() noexcept
    {
        return (void*)m_Handle;
    }

    void D3D12Viewport::Reset(bool ignore_focus) noexcept
    {
        (void)ignore_focus;
    }
}

#endif
