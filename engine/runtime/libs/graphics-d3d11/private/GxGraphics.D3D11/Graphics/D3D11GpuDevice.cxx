#include "D3D11GpuDevice.hxx"
#include "D3D11GpuSampler.hxx"
#include "D3D11GpuViewport.hxx"
#include "D3D11GpuVertexBuffer.hxx"
#include "D3D11GpuIndexBuffer.hxx"
#include "D3D11GpuPixelFormat.hxx"
#include "D3D11GpuCommandList.hxx"

#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>

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
        // clang-format off
        // FIXME reformat it to constexpr
        , m_ImmediateCommandList{}
#if ENABLE_GPU_API_DEBUG
        , m_DebugDevice{ true }
#else
        , m_DebugDevice{ false }
#endif
    // clang-format on
    {
        UINT create_flags{};

#if ENABLE_GPU_API_DEBUG
        create_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        const D3D_FEATURE_LEVEL feature_levels[]{
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
            context.GetAddressOf()));

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
                &gpu_thread_priority);

            GX_LOG_TRACE(LogD3D11Render, "GPU Thread priority: {}\n", gpu_thread_priority);
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

            GX_LOG_INFO(LogD3D11Render, "Adapter: (device: {:04x}, vendor: {:04x}, subsys: {:04x})\n",
                desc.DeviceId,
                desc.VendorId,
                desc.SubSysId);


            std::string description = System::Impl::NarrowString(desc.Description);

            GX_LOG_INFO(LogD3D11Render, "Adapter: `{}`\n", description);

            GX_LOG_INFO(LogD3D11Render, "Adapter: SystemMemory: {}, VideoMemory: {}, SharedMemory: {}\n",
                static_cast<uint64_t>(desc.DedicatedSystemMemory) >> 20,
                static_cast<uint64_t>(desc.DedicatedVideoMemory) >> 20,
                static_cast<uint64_t>(desc.SharedSystemMemory) >> 20);
        }

        //
        // Get associated factory.
        //
        GPU_DX_VALIDATE(m_Adapter->GetParent(IID_PPV_ARGS(m_Factory.GetAddressOf())));


        //
        // Device threading.
        //

        D3D11_FEATURE_DATA_THREADING featureThreading{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_THREADING, &featureThreading, sizeof(featureThreading))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureThreading.DriverCommandLists: {}\n", !!featureThreading.DriverCommandLists);
            GX_LOG_INFO(LogD3D11Render, "- FeatureThreading.DriverConcurrentCreates: {}\n", !!featureThreading.DriverConcurrentCreates);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_THREADING is not supported\n");
        }

        D3D11_FEATURE_DATA_D3D11_OPTIONS1 featureOptions1{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS1, &featureOptions1, sizeof(featureOptions1))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions1.TiledResourcesTier: {}\n", featureOptions1.TiledResourcesTier);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions1.MinMaxFiltering: {}\n", !!featureOptions1.MinMaxFiltering);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions1.ClearViewAlsoSupportsDepthOnlyFormats: {}\n", !!featureOptions1.ClearViewAlsoSupportsDepthOnlyFormats);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions1.MapOnDefaultBuffers: {}\n", !!featureOptions1.MapOnDefaultBuffers);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_D3D11_OPTIONS1 is not supported\n");
        }

        D3D11_FEATURE_DATA_DOUBLES featureDoubles{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_DOUBLES, &featureDoubles, sizeof(featureDoubles))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureDoubles.DoublePrecisionFloatShaderOps: {}\n", featureDoubles.DoublePrecisionFloatShaderOps);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_DOUBLES is not supported\n");
        }

        D3D11_FEATURE_DATA_D3D11_OPTIONS featureOptions{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &featureOptions, sizeof(featureOptions))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.OutputMergerLogicOp: {}\n", !!featureOptions.OutputMergerLogicOp);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.UAVOnlyRenderingForcedSampleCount: {}\n", !!featureOptions.UAVOnlyRenderingForcedSampleCount);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.DiscardAPIsSeenByDriver: {}\n", !!featureOptions.DiscardAPIsSeenByDriver);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.FlagsForUpdateAndCopySeenByDriver: {}\n", !!featureOptions.FlagsForUpdateAndCopySeenByDriver);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.ClearView: {}\n", !!featureOptions.ClearView);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.CopyWithOverlap: {}\n", !!featureOptions.CopyWithOverlap);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.ConstantBufferPartialUpdate: {}\n", !!featureOptions.ConstantBufferPartialUpdate);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.ConstantBufferOffsetting: {}\n", !!featureOptions.ConstantBufferOffsetting);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.MapNoOverwriteOnDynamicConstantBuffer: {}\n", !!featureOptions.MapNoOverwriteOnDynamicConstantBuffer);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.MapNoOverwriteOnDynamicBufferSRV: {}\n", !!featureOptions.MapNoOverwriteOnDynamicBufferSRV);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.MultisampleRTVWithForcedSampleCountOne: {}\n", !!featureOptions.MultisampleRTVWithForcedSampleCountOne);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.SAD4ShaderInstructions: {}\n", !!featureOptions.SAD4ShaderInstructions);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.ExtendedDoublesShaderInstructions: {}\n", !!featureOptions.ExtendedDoublesShaderInstructions);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions.ExtendedResourceSharing: {}\n", !!featureOptions.ExtendedResourceSharing);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_D3D11_OPTIONS is not supported\n");
        }

        D3D11_FEATURE_DATA_ARCHITECTURE_INFO featureArchitectureInfo{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_ARCHITECTURE_INFO, &featureArchitectureInfo, sizeof(featureArchitectureInfo))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureArchitectureInfo.TileBasedDeferredRenderer: {}\n", !!featureArchitectureInfo.TileBasedDeferredRenderer);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_ARCHITECTURE_INFO is not supported\n");
        }

        D3D11_FEATURE_DATA_SHADER_MIN_PRECISION_SUPPORT featureShaderMinPrecision{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT, &featureShaderMinPrecision, sizeof(featureShaderMinPrecision))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureShaderMinPrecision.PixelShaderMinPrecision: {}\n", featureShaderMinPrecision.PixelShaderMinPrecision);
            GX_LOG_INFO(LogD3D11Render, "- FeatureShaderMinPrecision.AllOtherShaderStagesMinPrecision: {}\n", featureShaderMinPrecision.AllOtherShaderStagesMinPrecision);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT is not supported\n");
        }

        D3D11_FEATURE_DATA_MARKER_SUPPORT featureMarkerSupport{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_MARKER_SUPPORT, &featureMarkerSupport, sizeof(featureMarkerSupport))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureMarkerSupport.Profile: {}\n", !!featureMarkerSupport.Profile);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_MARKER_SUPPORT is not supported\n");
        }

        D3D11_FEATURE_DATA_D3D11_OPTIONS2 featureOptions2{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS2, &featureOptions2, sizeof(featureOptions2))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions2.PSSpecifiedStencilRefSupported: {}\n", !!featureOptions2.PSSpecifiedStencilRefSupported);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions2.TypedUAVLoadAdditionalFormats: {}\n", !!featureOptions2.TypedUAVLoadAdditionalFormats);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions2.ROVsSupported: {}\n", !!featureOptions2.ROVsSupported);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions2.ConservativeRasterizationTier: {}\n", (uint32_t)featureOptions2.ConservativeRasterizationTier);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions2.TiledResourcesTier: {}\n", (uint32_t)featureOptions2.TiledResourcesTier);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions2.MapOnDefaultTextures: {}\n", !!featureOptions2.MapOnDefaultTextures);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions2.StandardSwizzle: {}\n", !!featureOptions2.StandardSwizzle);
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions2.UnifiedMemoryArchitecture: {}\n", !!featureOptions2.UnifiedMemoryArchitecture);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_D3D11_OPTIONS2 is not supported\n");
        }

        D3D11_FEATURE_DATA_D3D11_OPTIONS3 featureOptions3{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS3, &featureOptions3, sizeof(featureOptions3))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions3.VPAndRTArrayIndexFromAnyShaderFeedingRasterizer: {}\n", !!featureOptions3.VPAndRTArrayIndexFromAnyShaderFeedingRasterizer);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_D3D11_OPTIONS3 is not supported\n");
        }

        D3D11_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT featureGpuVirtualAddressSupport{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT, &featureGpuVirtualAddressSupport, sizeof(featureGpuVirtualAddressSupport))))
        {
            GX_LOG_INFO(LogD3D11Render, "- GpuVirtualAddress.MaxGPUVirtualAddressBitsPerResource: {}\n", featureGpuVirtualAddressSupport.MaxGPUVirtualAddressBitsPerResource);
            GX_LOG_INFO(LogD3D11Render, "- GpuVirtualAddress.MaxGPUVirtualAddressBitsPerProcess: {}\n", featureGpuVirtualAddressSupport.MaxGPUVirtualAddressBitsPerProcess);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT is not supported\n");
        }

        D3D11_FEATURE_DATA_D3D11_OPTIONS4 featureOptions4{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS4, &featureOptions4, sizeof(featureOptions4))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions4.ExtendedNV12SharedTextureSupported: {}\n", !!featureOptions4.ExtendedNV12SharedTextureSupported);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_D3D11_OPTIONS4 is not supported\n");
        }

        D3D11_FEATURE_DATA_SHADER_CACHE featureShaderCache{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_SHADER_CACHE, &featureShaderCache, sizeof(featureShaderCache))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureShaderCache.SupportFlags: {:x}\n", featureShaderCache.SupportFlags);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_SHADER_CACHE is not supported\n");
        }

        D3D11_FEATURE_DATA_D3D11_OPTIONS5 featureOptions5{};
        if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS5, &featureOptions5, sizeof(featureOptions5))))
        {
            GX_LOG_INFO(LogD3D11Render, "- FeatureOptions5.SharedResourceTier: {}\n", !!featureOptions5.SharedResourceTier);
        }
        else
        {
            GX_LOG_INFO(LogD3D11Render, "D3D11_FEATURE_D3D11_OPTIONS5 is not supported\n");
        }


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
                D3D11_MESSAGE_ID hide[] = {
                    D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                };

                D3D11_INFO_QUEUE_FILTER filter = {
                    .AllowList = {},
                    .DenyList  = {
                        .NumIDs  = static_cast<UINT>(std::size(hide)),
                        .pIDList = hide,
                    }
                };

                info_queue->AddStorageFilterEntries(&filter);
            }
        }


        m_ImmediateCommandList = new D3D11GpuCommandList();

        m_ImmediateCommandList->m_Context = m_Context.Get();
        m_ImmediateCommandList->m_Device  = m_Device.Get();
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

        GX_LOG_TRACE(LogD3D11Render, "Shutting down D3D11 render device\n");

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
            typedef HRESULT(__stdcall * fPtrDXGIGetDebugInterface)(const IID&, void**);
            HMODULE hMod = GetModuleHandleW(L"Dxgidebug.dll");
            fPtrDXGIGetDebugInterface ffDXGIGetDebugInterface
                = (fPtrDXGIGetDebugInterface)(void*)GetProcAddress(
                    hMod,
                    "DXGIGetDebugInterface");

            Microsoft::WRL::ComPtr<IDXGIDebug> debug{};
            if (SUCCEEDED(ffDXGIGetDebugInterface(
                    __uuidof(IDXGIDebug),
                    (void**)debug.GetAddressOf())))
            {
                debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
            }
        }
#endif
    }

    void D3D11GpuDevice::Tick(
        float time) noexcept
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
                            GX_LOG_TRACE(LogD3D11Render, "D3D11-DEBUG: {}}\n", m->pDescription);
                        }
                    }
                }

                info->ClearStoredMessages();
            }
        }
    }
}
