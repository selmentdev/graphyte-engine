#include "D3D11GpuViewport.hxx"
#include "D3D11GpuPixelFormat.hxx"
#include "D3D11GpuDevice.hxx"

namespace Graphyte::Graphics
{
    namespace Impl
    {
        DXGI_SAMPLE_DESC ExtractMsaaQuality(
            GpuMsaaQuality msaa) noexcept
        {
            DXGI_SAMPLE_DESC result{};

            switch (msaa)
            {
                case GpuMsaaQuality::Disabled:
                {
                    result = {
                        .Count   = 1,
                        .Quality = 0,
                    };

                    break;
                }
                case GpuMsaaQuality::X2:
                {
                    result = {
                        .Count   = 2,
                        .Quality = 0,
                    };

                    break;
                }
                case GpuMsaaQuality::X4:
                {
                    result = {
                        .Count   = 4,
                        .Quality = 0,
                    };

                    break;
                }
                case GpuMsaaQuality::X8:
                {
                    result = {
                        .Count   = 8,
                        .Quality = 0,
                    };

                    break;
                }
                case GpuMsaaQuality::X16:
                {
                    result = {
                        .Count   = 16,
                        .Quality = 0,
                    };

                    break;
                }
            }

            return result;
        }
    }

    DXGI_MODE_DESC D3D11GpuViewport::GetCompatibleMode() const noexcept
    {
        Microsoft::WRL::ComPtr<IDXGIOutput> output{};

        GPU_DX_VALIDATE(m_SwapChain->GetContainingOutput(
            output.GetAddressOf()));

        DXGI_MODE_DESC mode{
            .Width       = m_Width,
            .Height      = m_Height,
            .RefreshRate = {
                .Numerator   = 0,
                .Denominator = 0,
            },
            .Format           = D3D11GpuGetRenderTargetFormat(m_ColorFormat),
            .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
            .Scaling          = DXGI_MODE_SCALING_UNSPECIFIED,
        };

        DXGI_MODE_DESC result;

        HRESULT hr = output->FindClosestMatchingMode(
            &mode,
            &result,
            nullptr);

        if (hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE)
        {
            result = mode;
        }
        else
        {
            GPU_DX_VALIDATE(hr);
        }

        return result;
    }

    void D3D11GpuViewport::Reset(
        bool force) noexcept
    {
        if (!m_Valid)
        {
#if GRAPHYTE_PLATFORM_WINDOWS
            HWND focused            = GetFocus();
            bool const is_focused   = (focused == m_Handle);
            bool const is_minimized = !!IsIconic(m_Handle);
#else
            bool const is_focused   = true;
            bool const is_minimized = false;
#endif

            if (force || (is_focused && !is_minimized))
            {
                bool const use_forced_display = m_Fullscreen && (m_ColorFormat == PixelFormat::R32G32B32A32_FLOAT || m_FullscreenOutput != nullptr);

                HRESULT result = m_SwapChain->SetFullscreenState(
                    m_Fullscreen
                        ? TRUE
                        : FALSE,
                    use_forced_display
                        ? m_FullscreenOutput
                        : nullptr);

                GX_LOG(LogD3D11Render, Info, "SetFullscreenState: {:08x}({})\n", result, m_Fullscreen);

                if (SUCCEEDED(result))
                {
                    m_Valid = true;
                }
                else
                {
                    GX_LOG(LogD3D11Render, Info, "DXGISwapChain::SetFullscreenState ({:08x}). Retrying next frame.\n", result);
                }
            }
        }
    }

    GpuViewportHandle D3D11GpuDevice::CreateViewport(
        void* native_handle,
        uint32_t width,
        uint32_t height,
        bool fullscreen,
        PixelFormat color_format,
        PixelFormat depth_format,
        GpuMsaaQuality msaa) noexcept
    {
        HWND window_handle = static_cast<HWND>(native_handle);

        DXGI_SWAP_CHAIN_DESC sd{
            .BufferDesc = {
                .Width       = width,
                .Height      = height,
                .RefreshRate = {
                    .Numerator   = 0,
                    .Denominator = 0,
                },
                .Format           = D3D11GpuGetRenderTargetFormat(color_format),
                .ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
                .Scaling          = DXGI_MODE_SCALING_UNSPECIFIED,
            },
            .SampleDesc   = Impl::ExtractMsaaQuality(msaa),
            .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
            .BufferCount  = 1,
            .OutputWindow = window_handle,
            .Windowed     = fullscreen ? FALSE : TRUE,
            .SwapEffect   = DXGI_SWAP_EFFECT_DISCARD,
            .Flags        = 0,
        };

        {
            UINT max_quality{ 0 };

            if (FAILED(m_Device->CheckMultisampleQualityLevels(
                    sd.BufferDesc.Format,
                    sd.SampleDesc.Count,
                    &max_quality)))
            {
                //
                // Default sample quality if not supported.
                //

                sd.SampleDesc = {
                    .Count   = 1,
                    .Quality = 0,
                };
            }
            else
            {
                sd.SampleDesc.Quality = std::min(
                    sd.SampleDesc.Quality,
                    max_quality - 1);
            }
        }

        Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain{};
        IDXGISwapChain1* swap_chain1{};

        GPU_DX_VALIDATE(m_Factory->CreateSwapChain(
            m_Device.Get(),
            &sd,
            &swap_chain));

        GPU_DX_VALIDATE(swap_chain->QueryInterface(
            &swap_chain1));

        GX_LOG(LogD3D11Render, Trace, "Create viewport\n");

        GPU_DX_VALIDATE(m_Factory->MakeWindowAssociation(
            window_handle,
            DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER));

        auto result         = new D3D11GpuViewport();
        result->m_SwapChain = swap_chain1;

        result->m_Handle      = window_handle;
        result->m_Width       = width;
        result->m_Height      = height;
        result->m_ColorFormat = color_format;
        result->m_DepthFormat = depth_format;
        result->m_Fullscreen  = fullscreen;
        result->m_Valid       = true;
        result->m_MsaaQuality = msaa;

        this->ResizeViewport(
            result,
            width,
            height,
            fullscreen,
            result->m_ColorFormat);

        return result;
    }

    void D3D11GpuDevice::DestroyViewport(
        GpuViewportHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<D3D11GpuViewport*>(handle);
        GX_ASSERT(native->m_SwapChain != nullptr);

        GPU_DX_VALIDATE(native->m_SwapChain->SetFullscreenState(
            FALSE,
            nullptr));

        if (native->m_DepthStencilView != nullptr)
        {
            native->m_DepthStencilView->Release();
        }

        if (native->m_DepthStencil != nullptr)
        {
            native->m_DepthStencil->Release();
        }

        if (native->m_RenderTargetView != nullptr)
        {
            native->m_RenderTargetView->Release();
        }

        if (native->m_FullscreenOutput != nullptr)
        {
            native->m_FullscreenOutput->Release();
        }

        native->m_SwapChain->Release();


        delete native;
    }

    void D3D11GpuDevice::ResizeViewport(
        GpuViewportHandle handle,
        uint32_t width,
        uint32_t height,
        bool fullscreen,
        PixelFormat format) noexcept
    {

        (void)format;

        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuViewport*>(handle);

        //
        // Get fullscreen state.
        //
        BOOL current_fullscreen{};
        GPU_DX_VALIDATE(native->m_SwapChain->GetFullscreenState(
            &current_fullscreen,
            nullptr));

        native->m_Width      = width;
        native->m_Height     = height;
        native->m_Fullscreen = fullscreen;
        native->m_Valid      = false;

        GX_LOG(LogD3D11Render, Trace, "DXGI: begin resize\n");

        //
        // Get closest mode.
        //
        DXGI_MODE_DESC closest = native->GetCompatibleMode();

        //
        // Switch to request fullscreen state.
        //
        if (fullscreen)
        {
            GPU_DX_VALIDATE(native->m_SwapChain->SetFullscreenState(
                TRUE,
                nullptr));
        }

        //
        // Flush context state.
        //
        if (native->m_RenderTargetView != nullptr)
        {
            native->m_RenderTargetView->Release();
            native->m_RenderTargetView = nullptr;
        }

        m_Context->OMSetRenderTargets(0, nullptr, nullptr);
        m_Context->ClearState();
        m_Context->Flush();

        GPU_DX_VALIDATE(native->m_SwapChain->ResizeTarget(
            &closest));

        GPU_DX_VALIDATE(native->m_SwapChain->ResizeBuffers(
            0,
            0,
            0,
            DXGI_FORMAT_UNKNOWN,
            DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

        Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer{};

        GPU_DX_VALIDATE(native->m_SwapChain->GetBuffer(
            0,
            IID_PPV_ARGS(back_buffer.GetAddressOf())));

#if false
        {
            D3D11_TEXTURE2D_DESC desc{};
            back_buffer->GetDesc(&desc);
            GX_LOG(LogD3D11Render, Trace, "DXGI: {}x{} backbuffer\n", desc.Width, desc.Height);
        }
#endif

        //
        // Restore valid fullscreen state.
        //
        if (!fullscreen)
        {
            GPU_DX_VALIDATE(native->m_SwapChain->SetFullscreenState(
                FALSE,
                nullptr));
        }

        //
        // Create render target view.
        //
        D3D11_RENDER_TARGET_VIEW_DESC rtv{
            .Format        = DXGI_FORMAT_UNKNOWN,
            .ViewDimension = (native->m_MsaaQuality == GpuMsaaQuality::Disabled)
                                 ? D3D11_RTV_DIMENSION_TEXTURE2D
                                 : D3D11_RTV_DIMENSION_TEXTURE2DMS,
            .Texture2D = {
                .MipSlice = 0,
            },
        };

        GPU_DX_VALIDATE(m_Device->CreateRenderTargetView(
            back_buffer.Get(),
            &rtv,
            &native->m_RenderTargetView));

        //back_buffer.Reset();

        //
        // Depth stencil handling.
        //
        if (native->m_DepthFormat != PixelFormat::UNKNOWN)
        {
            if (native->m_DepthStencilView != nullptr)
            {
                native->m_DepthStencilView->Release();
                native->m_DepthStencilView = nullptr;
            }

            if (native->m_DepthStencil != nullptr)
            {
                native->m_DepthStencil->Release();
                native->m_DepthStencil = nullptr;
            }

            //
            // Create depth stencil attachment.
            //
            D3D11_TEXTURE2D_DESC desc{
                .Width          = width,
                .Height         = height,
                .MipLevels      = 1,
                .ArraySize      = 1,
                .Format         = D3D11GpuGetPixelFormat(native->m_DepthFormat),
                .SampleDesc     = Impl::ExtractMsaaQuality(native->m_MsaaQuality),
                .Usage          = D3D11_USAGE_DEFAULT,
                .BindFlags      = D3D11_BIND_DEPTH_STENCIL,
                .CPUAccessFlags = 0,
                .MiscFlags      = 0,
            };

            GPU_DX_VALIDATE(m_Device->CreateTexture2D(
                &desc,
                nullptr,
                &native->m_DepthStencil));

            GPU_DX_VALIDATE(m_Device->CreateDepthStencilView(
                native->m_DepthStencil,
                nullptr,
                &native->m_DepthStencilView));
        }

        GX_LOG(LogD3D11Render, Trace, "DXGI: end resize\n");
    }

    void D3D11GpuDevice::BeginDrawViewport(
        GpuViewportHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<D3D11GpuViewport*>(handle);

        D3D11_VIEWPORT desc{
            .TopLeftX = 0.0F,
            .TopLeftY = 0.0F,
            .Width    = static_cast<float>(native->m_Width),
            .Height   = static_cast<float>(native->m_Height),
            .MinDepth = 0.0F,
            .MaxDepth = 1.0F,
        };

        m_Context->RSSetViewports(
            1,
            &desc);

        m_Context->OMSetRenderTargets(
            1,
            &native->m_RenderTargetView,
            native->m_DepthStencilView);

        float color[]{ 0.0F, 0.0F, 0.0F, 0.0F };

        m_Context->ClearRenderTargetView(
            native->m_RenderTargetView,
            color);

        m_Context->ClearDepthStencilView(
            native->m_DepthStencilView,
            D3D11_CLEAR_DEPTH,
            1.0F,
            0);
    }

    void D3D11GpuDevice::EndDrawViewport(
        GpuViewportHandle handle,
        bool present,
        int interval) noexcept
    {
        (void)interval;
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<D3D11GpuViewport*>(handle);

        GX_ASSERT(native->m_SwapChain != nullptr);

        if (present)
        {
            GPU_DX_VALIDATE_DEVICE(this->m_Device.Get(), native->m_SwapChain->Present(static_cast<UINT>(interval), 0));
        }

        FlushLogs();
    }
}
