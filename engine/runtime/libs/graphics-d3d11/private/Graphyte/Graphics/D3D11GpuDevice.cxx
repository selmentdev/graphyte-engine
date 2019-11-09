#include "Graphics.D3D11.pch.hxx"
#include "D3D11GpuDevice.hxx"
#include "D3D11GpuSampler.hxx"
#include "D3D11GpuViewport.hxx"
#include "D3D11GpuVertexBuffer.hxx"
#include "D3D11GpuIndexBuffer.hxx"
#include "D3D11GpuPixelFormat.hxx"
#include "D3D11GpuCommandList.hxx"

#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>

namespace Graphyte::Graphics
{
    static_assert(sizeof(D3D11_SUBRESOURCE_DATA) == sizeof(GpuSubresourceData));
    static_assert(alignof(D3D11_SUBRESOURCE_DATA) == alignof(GpuSubresourceData));

    void D3D11GpuDevice::ReleaseDeferredResources() noexcept
    {
        for (auto* resource : m_ResourcesToDestroy)
        {
            resource->Release();
        }

        m_ResourcesToDestroy.clear();
    }

    D3D11GpuDevice::D3D11GpuDevice() noexcept
        : m_Factory{}
        , m_Adapter{}
        , m_Device{}
        , m_Context{}
        , m_FeatureLevel{}
        , m_ResourceLocks{}
        , m_ResourcesToDestroy{}
        , m_InputLayouts{}
        , m_RasterizerState{}
        , m_DepthStencilState{}
        , m_BlendState{}
        , m_ImmediateCommandList{}
#if ENABLE_GPU_API_DEBUG
        , m_DebugDevice{ true }
#else
        , m_DebugDevice{ false }
#endif
    {
        UINT create_flags{};

#if ENABLE_GPU_API_DEBUG
        create_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        const D3D_FEATURE_LEVEL feature_levels[]
        {
            D3D_FEATURE_LEVEL_12_1,
            D3D_FEATURE_LEVEL_12_0,
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
        };

        //
        // Create device.
        //
        Microsoft::WRL::ComPtr<ID3D11Device> device{};
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context{};

        GPU_DX_VALIDATE(D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            create_flags,
            std::data(feature_levels),
            static_cast<UINT>(std::size(feature_levels)),
            D3D11_SDK_VERSION,
            device.GetAddressOf(),
            &m_FeatureLevel,
            context.GetAddressOf()
        ));

        //
        // Try to get D3D11.1 pointers.
        //
        GPU_DX_VALIDATE(device.As(&m_Device));
        GPU_DX_VALIDATE(context.As(&m_Context));

        //
        // Get DXGI device.
        //
        Microsoft::WRL::ComPtr<IDXGIDevice1> dxgi_device{};
        GPU_DX_VALIDATE(m_Device.As(&dxgi_device));
        {
            INT gpu_thread_priority{};

            dxgi_device->GetGPUThreadPriority(
                &gpu_thread_priority
            );

            GX_LOG(LogD3D11Render, Trace, "GPU Thread priority: {}\n", gpu_thread_priority);
        }

        //
        // Get DXGI adapter.
        //
        Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
        GPU_DX_VALIDATE(dxgi_device->GetAdapter(adapter.GetAddressOf()));
        GPU_DX_VALIDATE(adapter.As(&m_Adapter));

        {
            DXGI_ADAPTER_DESC1 desc{};
            GPU_DX_VALIDATE(m_Adapter->GetDesc1(&desc));

            GX_LOG(LogD3D11Render, Info, "Adapter: (device: {:04x}, vendor: {:04x}, subsys: {:04x})\n",
                desc.DeviceId,
                desc.VendorId,
                desc.SubSysId
            );


            std::string description = System::Impl::NarrowString(desc.Description);

            GX_LOG(LogD3D11Render, Info, "Adapter: `{}`\n", description);

            GX_LOG(LogD3D11Render, Info, "Adapter: SystemMemory: {}, VideoMemory: {}, SharedMemory: {}\n",
                static_cast<uint64_t>(desc.DedicatedSystemMemory) >> 20,
                static_cast<uint64_t>(desc.DedicatedVideoMemory) >> 20,
                static_cast<uint64_t>(desc.SharedSystemMemory) >> 20
            );
        }

        //
        // Get associated factory.
        //
        GPU_DX_VALIDATE(m_Adapter->GetParent(IID_PPV_ARGS(m_Factory.GetAddressOf())));


        //
        // Device threading.
        //

        D3D11_FEATURE_DATA_THREADING threading_support{};
        GPU_DX_VALIDATE(m_Device->CheckFeatureSupport(D3D11_FEATURE_THREADING, &threading_support, sizeof(threading_support)));
        GX_LOG(LogD3D11Render, Info, "Supports driver command lists: {}\n", threading_support.DriverCommandLists ? 1 : 0);
        GX_LOG(LogD3D11Render, Info, "Supports concurrent resources: {}\n", threading_support.DriverConcurrentCreates);


        //
        // Setup debugging.
        //

        Microsoft::WRL::ComPtr<ID3D11Debug> debug;
        if (SUCCEEDED(m_Device.As(&debug)))
        {
            Microsoft::WRL::ComPtr<ID3D11InfoQueue> info_queue;
            if (SUCCEEDED(debug.As(&info_queue)))
            {
#if ENABLE_GPU_API_DEBUG
                GPU_DX_VALIDATE(info_queue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, TRUE));
                GPU_DX_VALIDATE(info_queue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, TRUE));
                GPU_DX_VALIDATE(info_queue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_WARNING, TRUE));
#endif
                D3D11_MESSAGE_ID hide[] =
                {
                    D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                };

                D3D11_INFO_QUEUE_FILTER filter = {
                    .AllowList = {},
                    .DenyList = {
                        .NumIDs = static_cast<UINT>(std::size(hide)),
                        .pIDList = hide,
                    }
                };

                info_queue->AddStorageFilterEntries(&filter);
            }
        }


        m_ImmediateCommandList = new D3D11GpuCommandList();
        m_ImmediateCommandList->m_Context = m_Context.Get();
        m_ImmediateCommandList->m_Device = m_Device.Get();
    }

    D3D11GpuDevice::~D3D11GpuDevice() noexcept
    {
        ID3D11RenderTargetView* nullViews[] = { nullptr };
        m_Context->OMSetRenderTargets((UINT)std::size(nullViews), nullViews, nullptr);


        for (auto& resource : m_InputLayouts)
        {
            resource.second->Release();
        }

        m_InputLayouts.clear();

        for (auto& resource : m_DepthStencilState)
        {
            resource.second->Release();
        }

        m_DepthStencilState.clear();

        for (auto& resource : m_RasterizerState)
        {
            resource.second->Release();
        }

        m_RasterizerState.clear();

        for (auto& resource : m_BlendState)
        {
            resource.second->Release();
        }

        m_BlendState.clear();

        this->ReleaseDeferredResources();

        GX_LOG(LogD3D11Render, Trace, "Shutting down D3D11 render device\n");

        this->m_Context->ClearState();
        this->m_Context->Flush();

        FlushLogs();

        delete m_ImmediateCommandList;

        auto r = m_Context.Reset();
        GX_ABORT_UNLESS(r == 0, "Failed to release D3D11 Immediate Context");
        
        r = m_Device.Reset();
        GX_ABORT_UNLESS(r == 0, "Failed to release D3D11 Device");

        r = m_Adapter.Reset();
        GX_ABORT_UNLESS(r == 0, "Failed to release DXGI Adapter");

        r = m_Factory.Reset();
        GX_ABORT_UNLESS(r == 0, "Failed to release DXGI Factory");

        GX_ASSERT(m_ResourceLocks.size() == 0);
        GX_ASSERT(m_ResourcesToDestroy.size() == 0);

#if false
        {
            Microsoft::WRL::ComPtr<ID3D11Debug> debug{};
            GPU_DX_VALIDATE(m_Device.As(&debug));
            if (debug != nullptr)
            {
                debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL | D3D11_RLDO_SUMMARY);
            }
        }
#endif

#if ENABLE_GPU_API_DEBUG
        {
            typedef HRESULT(__stdcall *fPtrDXGIGetDebugInterface)(const IID&, void**);
            HMODULE hMod = GetModuleHandleW(L"Dxgidebug.dll");
            fPtrDXGIGetDebugInterface ffDXGIGetDebugInterface
                = (fPtrDXGIGetDebugInterface)(void*)GetProcAddress(
                    hMod,
                    "DXGIGetDebugInterface"
                );

            Microsoft::WRL::ComPtr<IDXGIDebug> debug{};
            if (SUCCEEDED(ffDXGIGetDebugInterface(
                __uuidof(IDXGIDebug),
                (void**)debug.GetAddressOf()))
            )
            {
                debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
            }
        }
#endif
    }

    void D3D11GpuDevice::Tick(
        float time
    ) noexcept
    {
        (void)time;
        this->ReleaseDeferredResources();
    }

    void D3D11GpuDevice::FlushLogs() noexcept
    {
        if (m_DebugDevice)
        {
            Microsoft::WRL::ComPtr<ID3D11InfoQueue> info{};
            GPU_DX_VALIDATE(m_Device.As(&info));

            if (info != nullptr)
            {
                UINT64 messages = info->GetNumStoredMessagesAllowedByRetrievalFilter();
                for (UINT64 i = 0; i < messages; ++i)
                {
                    SIZE_T length = 0;
                    if (SUCCEEDED(info->GetMessage(i, nullptr, &length)))
                    {
                        std::vector<uint8_t> data(length);

                        D3D11_MESSAGE* m = reinterpret_cast<D3D11_MESSAGE*>(data.data());
                        if (SUCCEEDED(info->GetMessage(i, m, &length)))
                        {
                            GX_LOG(LogD3D11Render, Trace, "D3D11-DEBUG: {}}\n", m->pDescription);
                        }
                    }
                }

                info->ClearStoredMessages();
            }
        }
    }
}
