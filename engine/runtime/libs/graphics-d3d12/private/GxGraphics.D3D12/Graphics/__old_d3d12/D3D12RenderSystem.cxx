#include "D3D12RenderSystem.hxx"
#include "D3D12Viewport.hxx"
#include <Graphyte/Unicode.hxx>

#if false

namespace Graphyte::Graphics::Render
{
    void D3D12RenderSystem::InitializeD3D12() noexcept
    {
        //
        // Enable debug interface.
        //
#if GRAPHYTE_BUILD_TYPE_DEBUG
        {
            Microsoft::WRL::ComPtr<ID3D12Debug> debug{};
            if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug))))
            {
                debug->EnableDebugLayer();
            }
        }
#endif

        //
        // Create DXGI factory.
        //
        D3D12Verify(CreateDXGIFactory1(IID_PPV_ARGS(&m_Factory)));


        for (UINT adapter = 0; DXGI_ERROR_NOT_FOUND != m_Factory->EnumAdapters1(adapter, &m_Adapter); ++adapter)
        {
            DXGI_ADAPTER_DESC1 desc{};

            HRESULT hr = m_Adapter->GetDesc1(&desc);
            if (FAILED(hr))
            {
                continue;
            }

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                continue;
            }

            if (SUCCEEDED(D3D12CreateDevice(m_Adapter.Get(), D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), nullptr)))
            {
                GX_LOG_INFO(LogD3D12Render, "Adapter: (device: {:04x}, vendor: {:04x}, subsys: {:04x})\n",
                    desc.DeviceId,
                    desc.VendorId,
                    desc.SubSysId
                );


                std::string description{};
                GX_VERIFY(Text::ConvertString(desc.Description, description, Text::ConversionType::Strict) == Text::ConversionResult::Success);

                GX_LOG_INFO(LogD3D12Render, "Adapter: `{}`\n", description);

                GX_LOG_INFO(LogD3D12Render, "Adapter: SystemMemory: {}, VideoMemory: {}, SharedMemory: {}\n",
                    static_cast<uint64_t>(desc.DedicatedSystemMemory) >> 20,
                    static_cast<uint64_t>(desc.DedicatedVideoMemory) >> 20,
                    static_cast<uint64_t>(desc.SharedSystemMemory) >> 20
                );

                break;
            }
        }

#if GRAPHYTE_BUILD_TYPE_DEBUG
        if (m_Adapter == nullptr)
        {
            if (FAILED(m_Factory->EnumWarpAdapter(IID_PPV_ARGS(&m_Adapter))))
            {
                m_Adapter.Reset();
            }
        }
#endif

        D3D12Verify(D3D12CreateDevice(
            m_Adapter.Get(),
            D3D_FEATURE_LEVEL_12_0,
            IID_PPV_ARGS(&m_Device)
        ));

        static const D3D_FEATURE_LEVEL feature_levels[] =
        {
            D3D_FEATURE_LEVEL_12_1,
            D3D_FEATURE_LEVEL_12_0,
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
        };

        D3D12_FEATURE_DATA_FEATURE_LEVELS feature_level_data =
        {
            (UINT)std::size(feature_levels),
            feature_levels,
            D3D_FEATURE_LEVEL_12_0,
        };

        m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

        if (SUCCEEDED(m_Device->CheckFeatureSupport(
            D3D12_FEATURE_FEATURE_LEVELS,
            &feature_level_data,
            sizeof(feature_level_data))))
        {
            m_FeatureLevel = feature_level_data.MaxSupportedFeatureLevel;
        }

        GX_LOG_TRACE(LogD3D12Render, "Initialized at feature level: {:04x}\n", static_cast<uint32_t>(m_FeatureLevel));

        D3D12_COMMAND_QUEUE_DESC cq_desc{};
        cq_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        cq_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

        D3D12Verify(m_Device->CreateCommandQueue(&cq_desc, IID_PPV_ARGS(&m_CommandQueue)));
    }

    D3D12RenderSystem::D3D12RenderSystem() noexcept
    {
        InitializeD3D12();
    }

    D3D12RenderSystem::~D3D12RenderSystem() noexcept
    {
    }

    ViewportRef D3D12RenderSystem::MakeViewport(void* window_handle, uint32_t width, uint32_t height, bool fullscreen, PixelFormat format) noexcept
    {
        return MakeRef<D3D12Viewport>(this, reinterpret_cast<HWND>(window_handle), width, height, fullscreen, format);
    }

    void D3D12RenderSystem::ResizeViewport(const ViewportRef& viewport, uint32_t width, uint32_t height, bool fullscreen) noexcept
    {
        D3D12Viewport* native = static_cast<D3D12Viewport*>(viewport.Get());
        native->Resize(width, height, fullscreen);
    }

    void D3D12RenderSystem::BeginDrawViewport(const ViewportRef& viewport) noexcept
    {
        D3D12Viewport* native = static_cast<D3D12Viewport*>(viewport.Get());

        D3D12_VIEWPORT desc{};
        desc.TopLeftX = 0.0F;
        desc.TopLeftY = 0.0F;
        desc.Width = static_cast<float>(native->m_Width);
        desc.Height = static_cast<float>(native->m_Height);
        desc.MinDepth = 0.0F;
        desc.MaxDepth = 1.0F;

        //m_Context->RSSetViewports(1, &desc);

        //m_Context->OMSetRenderTargets(1, native->m_RenderTargetView.GetAddressOf(), native->m_DepthStencilView.Get());

        //static uint8_t d = 0;
        //d++;

        //float color[]{ 0.0F, d * (1.0F / 255.0F), 0.0F, 0.0F };

        //m_Context->ClearRenderTargetView(native->m_RenderTargetView.Get(), color);
        //m_Context->ClearDepthStencilView(native->m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0F, 0);
    }

    void D3D12RenderSystem::EndRawViewport(const ViewportRef& viewport, bool present, int interval) noexcept
    {
        D3D12Viewport* native = static_cast<D3D12Viewport*>(viewport.Get());

        if (present)
        {
            native->Present(interval);
        }

        FlushLogs();
    }

    void D3D12RenderSystem::FlushLogs() noexcept
    {
        //Microsoft::WRL::ComPtr<ID3D11InfoQueue> info{};
        //D3D11Ensure(m_Device->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)info.GetAddressOf()));
        //
        //if (info != nullptr)
        //{
        //    UINT64 messages = info->GetNumStoredMessagesAllowedByRetrievalFilter();
        //    for (UINT64 i = 0; i < messages; ++i)
        //    {
        //        size_t length = 0;
        //        if (SUCCEEDED(info->GetMessage(i, nullptr, &length)))
        //        {
        //            std::vector<uint8_t> data(length);
        //
        //            D3D11_MESSAGE* m = reinterpret_cast<D3D11_MESSAGE*>(data.data());
        //            if (SUCCEEDED(info->GetMessage(i, m, &length)))
        //            {
        //            }
        //        }
        //    }
        //
        //    info->ClearStoredMessages();
        //}
    }
}

#endif
