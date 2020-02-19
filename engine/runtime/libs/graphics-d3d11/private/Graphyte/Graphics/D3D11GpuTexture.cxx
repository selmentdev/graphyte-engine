#include "D3D11GpuTexture.hxx"
#include "D3D11GpuDevice.hxx"
#include "D3D11GpuPixelFormat.hxx"
#include "D3D11GpuDevice.hxx"

#include <Graphyte/Flags.hxx>

namespace Graphyte::Graphics
{
    namespace Impl
    {
        void ExpandTextureFlags(
            GpuTextureFlags flags,
            D3D11_USAGE& usage,
            UINT& bind,
            UINT& cpu_access,
            UINT& misc_flags
        ) noexcept
        {
            usage = D3D11_USAGE_DEFAULT;
            bind = D3D11_BIND_SHADER_RESOURCE;
            cpu_access = 0;
            misc_flags = 0;

            if (Flags::Has(flags, GpuTextureFlags::UnorderedAccess))
            {
                bind |= D3D11_BIND_UNORDERED_ACCESS;
            }

            if (Flags::Has(flags, GpuTextureFlags::Dynamic))
            {
                usage = D3D11_USAGE_DYNAMIC;
                cpu_access |= D3D11_CPU_ACCESS_WRITE;
            }

            if (Flags::Has(flags, GpuTextureFlags::RenderTarget))
            {
                bind |= D3D11_BIND_RENDER_TARGET;
            }

            if (Flags::Has(flags, GpuTextureFlags::GenerateMipmaps))
            {
                misc_flags |= D3D11_RESOURCE_MISC_GENERATE_MIPS;
            }

            if (Flags::Has(flags, GpuTextureFlags::DepthStencil))
            {
                bind |= D3D11_BIND_DEPTH_STENCIL;
                misc_flags = 0; // Depth stencil texture can't have mip maps generated
            }
        }
    }

    namespace Impl
    {
        inline DXGI_FORMAT EnsureNotTypeless(
            DXGI_FORMAT fmt
        )
        {
            // Assumes UNORM or FLOAT; doesn't use UINT or SINT
            switch (fmt)
            {
            case DXGI_FORMAT_R32G32B32A32_TYPELESS: return DXGI_FORMAT_R32G32B32A32_FLOAT;
            case DXGI_FORMAT_R32G32B32_TYPELESS:    return DXGI_FORMAT_R32G32B32_FLOAT;
            case DXGI_FORMAT_R16G16B16A16_TYPELESS: return DXGI_FORMAT_R16G16B16A16_UNORM;
            case DXGI_FORMAT_R32G32_TYPELESS:       return DXGI_FORMAT_R32G32_FLOAT;
            case DXGI_FORMAT_R10G10B10A2_TYPELESS:  return DXGI_FORMAT_R10G10B10A2_UNORM;
            case DXGI_FORMAT_R8G8B8A8_TYPELESS:     return DXGI_FORMAT_R8G8B8A8_UNORM;
            case DXGI_FORMAT_R16G16_TYPELESS:       return DXGI_FORMAT_R16G16_UNORM;
            case DXGI_FORMAT_R32_TYPELESS:          return DXGI_FORMAT_R32_FLOAT;
            case DXGI_FORMAT_R8G8_TYPELESS:         return DXGI_FORMAT_R8G8_UNORM;
            case DXGI_FORMAT_R16_TYPELESS:          return DXGI_FORMAT_R16_UNORM;
            case DXGI_FORMAT_R8_TYPELESS:           return DXGI_FORMAT_R8_UNORM;
            case DXGI_FORMAT_BC1_TYPELESS:          return DXGI_FORMAT_BC1_UNORM;
            case DXGI_FORMAT_BC2_TYPELESS:          return DXGI_FORMAT_BC2_UNORM;
            case DXGI_FORMAT_BC3_TYPELESS:          return DXGI_FORMAT_BC3_UNORM;
            case DXGI_FORMAT_BC4_TYPELESS:          return DXGI_FORMAT_BC4_UNORM;
            case DXGI_FORMAT_BC5_TYPELESS:          return DXGI_FORMAT_BC5_UNORM;
            case DXGI_FORMAT_B8G8R8A8_TYPELESS:     return DXGI_FORMAT_B8G8R8A8_UNORM;
            case DXGI_FORMAT_B8G8R8X8_TYPELESS:     return DXGI_FORMAT_B8G8R8X8_UNORM;
            case DXGI_FORMAT_BC7_TYPELESS:          return DXGI_FORMAT_BC7_UNORM;
            default:                                return fmt;
            }
        }

        HRESULT CaptureTexture(
            ID3D11DeviceContext* pContext,
            ID3D11Resource* pSource,
            D3D11_TEXTURE2D_DESC& desc,
            Microsoft::WRL::ComPtr<ID3D11Texture2D>& pStaging
        )
        {
            if (!pContext || !pSource)
            {
                return E_INVALIDARG;
            }

            D3D11_RESOURCE_DIMENSION resType = D3D11_RESOURCE_DIMENSION_UNKNOWN;
            pSource->GetType(&resType);

            if (resType != D3D11_RESOURCE_DIMENSION_TEXTURE2D)
            {
                return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
            }

            Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;
            HRESULT hr = pSource->QueryInterface(IID_PPV_ARGS(pTexture.GetAddressOf()));

            if (FAILED(hr))
            {
                return hr;
            }

            GX_ASSERT(pTexture != nullptr);

            pTexture->GetDesc(&desc);

            Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
            pContext->GetDevice(d3dDevice.GetAddressOf());

            if (desc.SampleDesc.Count > 1)
            {
                // MSAA content must be resolved before being copied to a staging texture
                desc.SampleDesc.Count = 1;
                desc.SampleDesc.Quality = 0;

                Microsoft::WRL::ComPtr<ID3D11Texture2D> pTemp;
                hr = d3dDevice->CreateTexture2D(&desc, nullptr, pTemp.GetAddressOf());

                if (FAILED(hr))
                {
                    return hr;
                }

                GX_ASSERT(pTemp);

                DXGI_FORMAT fmt = EnsureNotTypeless(desc.Format);

                UINT support = 0;
                hr = d3dDevice->CheckFormatSupport(fmt, &support);

                if (FAILED(hr))
                {
                    return hr;
                }

                if (!(support & D3D11_FORMAT_SUPPORT_MULTISAMPLE_RESOLVE))
                {
                    return E_FAIL;
                }

                for (UINT item = 0; item < desc.ArraySize; ++item)
                {
                    for (UINT level = 0; level < desc.MipLevels; ++level)
                    {
                        UINT index = D3D11CalcSubresource(level, item, desc.MipLevels);
                        pContext->ResolveSubresource(pTemp.Get(), index, pSource, index, fmt);
                    }
                }

                desc.BindFlags = 0;
                desc.MiscFlags &= D3D11_RESOURCE_MISC_TEXTURECUBE;
                desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
                desc.Usage = D3D11_USAGE_STAGING;

                hr = d3dDevice->CreateTexture2D(&desc, nullptr, pStaging.ReleaseAndGetAddressOf());
                if (FAILED(hr))
                {
                    return hr;
                }

                GX_ASSERT(pStaging);

                pContext->CopyResource(pStaging.Get(), pTemp.Get());
            }
            else if ((desc.Usage == D3D11_USAGE_STAGING) && (desc.CPUAccessFlags & D3D11_CPU_ACCESS_READ))
            {
                // Handle case where the source is already a staging texture we can use directly
                pStaging = pTexture;
            }
            else
            {
                // Otherwise, create a staging texture from the non-MSAA source
                desc.BindFlags = 0;
                desc.MiscFlags &= D3D11_RESOURCE_MISC_TEXTURECUBE;
                desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
                desc.Usage = D3D11_USAGE_STAGING;

                hr = d3dDevice->CreateTexture2D(&desc, nullptr, pStaging.ReleaseAndGetAddressOf());

                if (FAILED(hr))
                {
                    return hr;
                }

                GX_ASSERT(pStaging);

                pContext->CopyResource(pStaging.Get(), pSource);
            }

#if defined(_XBOX_ONE) && defined(_TITLE)

            if (d3dDevice->GetCreationFlags() & D3D11_CREATE_DEVICE_IMMEDIATE_CONTEXT_FAST_SEMANTICS)
            {
                ComPtr<ID3D11DeviceX> d3dDeviceX;
                hr = d3dDevice.As(&d3dDeviceX);

                if (FAILED(hr))
                {
                    return hr;
                }

                ComPtr<ID3D11DeviceContextX> d3dContextX;
                hr = pContext->QueryInterface(IID_GRAPHICS_PPV_ARGS(d3dContextX.GetAddressOf()));

                if (FAILED(hr))
                {
                    return hr;
                }

                UINT64 copyFence = d3dContextX->InsertFence(0);

                while (d3dDeviceX->IsFencePending(copyFence))
                {
                    SwitchToThread();
                }
            }

#endif

            return S_OK;
        }
    }
}

namespace Graphyte::Graphics
{
    GpuTexture2DHandle D3D11GpuDevice::CreateTexture2D(
        const GpuTextureCreateArgs& args
    ) noexcept
    {
        bool const has_uav = Flags::Has(args.Flags, GpuTextureFlags::UnorderedAccess);

        auto result = new D3D11GpuTexture();

        //
        // Create resource.
        //
        D3D11_TEXTURE2D_DESC desc{
            .Width = args.Width,
            .Height = args.Height,
            .MipLevels = args.MipCount,
            .ArraySize = 1,
            .Format = D3D11GpuGetCreateResourcePixelFormat(args.DataFormat),
            .SampleDesc = {
                .Count = 1,
                .Quality = 0,
            },
        };

        Impl::ExpandTextureFlags(
            args.Flags,
            desc.Usage,
            desc.BindFlags,
            desc.CPUAccessFlags,
            desc.MiscFlags
        );


        GPU_DX_VALIDATE(m_Device->CreateTexture2D(
            &desc,
            reinterpret_cast<const D3D11_SUBRESOURCE_DATA*>(args.Data),
            &result->m_Texture2D
        ));

        //
        // Get back actual texture desc.
        //
        result->m_Texture2D->GetDesc(&desc);

        result->m_Dimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        result->m_MipLevels = desc.MipLevels;
        result->m_ArrayCount = 1;
        result->m_MiscFlags = desc.MiscFlags;
        result->m_Usage = desc.Usage;
        result->m_Format = args.DataFormat;


        //
        // Create shader view.
        //
        D3D11_SHADER_RESOURCE_VIEW_DESC view_desc{
            .Format = D3D11GpuGetReadViewPixelFormat(args.ViewFormat),
            .ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D,
            .Texture2D = {
                .MostDetailedMip = 0,
                .MipLevels = args.MipCount,
            },
        };

        GPU_DX_VALIDATE(m_Device->CreateShaderResourceView(
            result->m_Texture2D,
            &view_desc,
            &result->m_ShaderResourceView
        ));


        //
        // Create UAV.
        //
        if (has_uav)
        {
            D3D11_UNORDERED_ACCESS_VIEW_DESC uav_desc{
                .Format = D3D11GpuGetWriteViewPixelFormat(args.ViewFormat),
                .ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D,
                .Texture2D = {
                    .MipSlice = 0,
                },
            };

            if (uav_desc.Format != DXGI_FORMAT_UNKNOWN)
            {
                GPU_DX_VALIDATE(m_Device->CreateUnorderedAccessView(
                    result->m_Texture2D,
                    &uav_desc,
                    &result->m_UnorderedAccessView
                ));
            }
        }


        //
        // Set debug name.
        //

#if ENABLE_GPU_API_DEBUG

        if (args.DebugName != nullptr)
        {
            D3D11SetDebugObjectName(
                result->m_Texture2D,
                args.DebugName,
                std::strlen(args.DebugName)
            );
        }

#endif

        return result;
    }

    void D3D11GpuDevice::DestroyTexture2D(
        GpuTexture2DHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuTexture*>(handle);

        GX_ASSERT(native->m_Dimension == D3D11_SRV_DIMENSION_TEXTURE2D);

        this->DeferResourceRelease(native->m_UnorderedAccessView);
        this->DeferResourceRelease(native->m_ShaderResourceView);
        this->DeferResourceRelease(native->m_Texture2D);

        delete native;
    }

    void D3D11GpuDevice::UpdateTexture2D(
        GpuTexture2DHandle handle,
        uint32_t mip_level,
        const GpuRect* rect,
        const void* data,
        uint32_t pitch
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuTexture*>(handle);

        GX_ASSERT(native->m_Dimension == D3D11_SRV_DIMENSION_TEXTURE2D);

        UINT subresource = D3D11CalcSubresource(mip_level, 0, native->m_MipLevels);
        
        if (Flags::Has(native->m_Usage, D3D11_USAGE_DYNAMIC))
        {
            D3D11_MAPPED_SUBRESOURCE resource;

            HRESULT hr = m_Context->Map(
                native->m_Texture2D,
                subresource,
                D3D11_MAP_WRITE_DISCARD,
                0,
                &resource
            );

            if (SUCCEEDED(hr))
            {
                GX_ASSERTF(resource.RowPitch == pitch, "Invalid row pitch: passed u, got {}", pitch, resource.RowPitch);

                if (resource.RowPitch == pitch)
                {
                    memcpy_s(resource.pData, resource.DepthPitch, data, resource.DepthPitch);
                }

                m_Context->Unmap(
                    native->m_Texture2D,
                    subresource
                );
            }
            else
            {
                GX_ASSERTF(false, "Failed to map Texture2D memory: {:08x}", hr);
            }
        }
        else
        {
            D3D11_BOX box{};
            if (rect != nullptr)
            {
                box = {
                    .left = rect->Left,
                    .top = rect->Top,
                    .front = 0,
                    .right = rect->Right,
                    .bottom = rect->Bottom,
                    .back = 1,
                };
            }

            m_Context->UpdateSubresource(
                native->m_Texture2D,
                subresource,
                (rect != nullptr) ? &box : nullptr,
                data,
                pitch, 0
            );
        }
    }

    void D3D11GpuDevice::GenerateMipmapsTexture2D(
        GpuTexture2DHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuTexture*>(handle);

        GX_ASSERT(native->m_Dimension == D3D11_SRV_DIMENSION_TEXTURE2D);

        GX_ASSERT((native->m_MiscFlags & D3D11_RESOURCE_MISC_GENERATE_MIPS) != 0);

        if ((native->m_MiscFlags & D3D11_RESOURCE_MISC_GENERATE_MIPS) != 0)
        {
            m_Context->GenerateMips(
                native->m_ShaderResourceView
            );
        }
    }

    std::unique_ptr<Image> D3D11GpuDevice::SaveTexture2D(
        GpuTexture2DHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuTexture*>(handle);

        GX_ASSERT(native->m_Dimension == D3D11_SRV_DIMENSION_TEXTURE2D);
        
        //
        // Create staging texture.
        //

        D3D11_TEXTURE2D_DESC desc = {};

        Microsoft::WRL::ComPtr<ID3D11Texture2D> pStaging;

        HRESULT hr = Impl::CaptureTexture(
            m_Context.Get(),
            native->m_Texture2D,
            desc,
            pStaging
        );

        if (FAILED(hr))
        {
            return nullptr;
        }

        auto result = Image::Create2D(
            D3D11GpuGetPixelFormat(desc.Format),
            desc.Width,
            desc.Height
        );

        D3D11_MAPPED_SUBRESOURCE mapped{};
        GPU_DX_VALIDATE(m_Context->Map(pStaging.Get(), 0, D3D11_MAP_READ, 0, &mapped));

        if (mapped.pData == nullptr)
        {
            m_Context->Unmap(pStaging.Get(), 0);
            return nullptr;
        }

        auto source_scanline = reinterpret_cast<const std::byte*>(mapped.pData);

        auto pixels = result->GetSubresource(0);
        auto row_pitch = std::min<size_t>(pixels->LinePitch, mapped.RowPitch);

        for (uint32_t row = 0; row < pixels->Height; ++row)
        {
            auto target_scanline = pixels->GetScanline<std::byte>(row);

            memcpy_s(target_scanline, row_pitch, source_scanline, row_pitch);

            source_scanline += mapped.RowPitch;
        }

        m_Context->Unmap(pStaging.Get(), 0);

        return result;
    }
}

namespace Graphyte::Graphics
{
    GpuTexture2DArrayHandle D3D11GpuDevice::CreateTexture2DArray(
        const GpuTextureCreateArgs& args
    ) noexcept
    {
        bool const has_uav = Flags::Has(args.Flags, GpuTextureFlags::UnorderedAccess);

        auto result = new D3D11GpuTexture();

        //
        // Create resource.
        //
        D3D11_TEXTURE2D_DESC desc{
            .Width = args.Width,
            .Height = args.Height,
            .MipLevels = args.MipCount,
            .ArraySize = args.Depth,
            .Format = D3D11GpuGetCreateResourcePixelFormat(args.DataFormat),
            .SampleDesc = {
                .Count = 1,
                .Quality = 0,
            },
        };

        Impl::ExpandTextureFlags(
            args.Flags,
            desc.Usage,
            desc.BindFlags,
            desc.CPUAccessFlags,
            desc.MiscFlags
        );

        GPU_DX_VALIDATE(m_Device->CreateTexture2D(
            &desc,
            reinterpret_cast<const D3D11_SUBRESOURCE_DATA*>(args.Data),
            &result->m_Texture2D
        ));


        //
        // Get back actual texture desc.
        //
        result->m_Texture2D->GetDesc(&desc);

        result->m_Dimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
        result->m_MipLevels = desc.MipLevels;
        result->m_ArrayCount = 1;
        result->m_MiscFlags = desc.MiscFlags;
        result->m_Usage = desc.Usage;
        result->m_Format = args.DataFormat;

        
        //
        // Create shader view.
        //
        D3D11_SHADER_RESOURCE_VIEW_DESC view_desc{
            .Format = D3D11GpuGetReadViewPixelFormat(args.ViewFormat),
            .ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY,
        };

        view_desc.Texture2DArray = {
            .MostDetailedMip = 0,
            .MipLevels = args.MipCount,
            .FirstArraySlice = 0,
            .ArraySize = args.Depth,
        };

        GPU_DX_VALIDATE(m_Device->CreateShaderResourceView(
            result->m_Texture2D,
            &view_desc,
            &result->m_ShaderResourceView
        ));


        //
        // Create UAV.
        //
        if (has_uav)
        {
            D3D11_UNORDERED_ACCESS_VIEW_DESC uav_desc{
                .Format = D3D11GpuGetWriteViewPixelFormat(args.ViewFormat),
                .ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY,
                .Texture2DArray = {
                    .MipSlice = 0,
                    .FirstArraySlice = 0,
                    .ArraySize = args.Depth,
                },
            };

            if (uav_desc.Format != DXGI_FORMAT_UNKNOWN)
            {
                GPU_DX_VALIDATE(m_Device->CreateUnorderedAccessView(
                    result->m_Texture2D,
                    &uav_desc,
                    &result->m_UnorderedAccessView
                ));
            }
        }


        //
        // Set debug name.
        //

#if ENABLE_GPU_API_DEBUG

        if (args.DebugName != nullptr)
        {
            D3D11SetDebugObjectName(
                result->m_Texture2D,
                args.DebugName,
                std::strlen(args.DebugName)
            );
        }

#endif

        return result;
    }

    void D3D11GpuDevice::DestroyTexture2DArray(
        GpuTexture2DArrayHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuTexture*>(handle);

        GX_ASSERT(native->m_Dimension == D3D11_SRV_DIMENSION_TEXTURE2DARRAY);

        this->DeferResourceRelease(native->m_UnorderedAccessView);
        this->DeferResourceRelease(native->m_ShaderResourceView);
        this->DeferResourceRelease(native->m_Texture2D);

        delete native;
    }
}

namespace Graphyte::Graphics
{
    GpuTexture3DHandle D3D11GpuDevice::CreateTexture3D(
        const GpuTextureCreateArgs& args
    ) noexcept
    {
        bool const has_uav = Flags::Has(args.Flags, GpuTextureFlags::UnorderedAccess);

        auto result = new D3D11GpuTexture();


        //
        // Create resource.
        //
        D3D11_TEXTURE3D_DESC desc{
            .Width = args.Width,
            .Height = args.Height,
            .Depth = args.Depth,
            .MipLevels = args.MipCount,
            .Format = D3D11GpuGetCreateResourcePixelFormat(args.DataFormat),
        };
        
        Impl::ExpandTextureFlags(
            args.Flags,
            desc.Usage,
            desc.BindFlags,
            desc.CPUAccessFlags,
            desc.MiscFlags
        );

        GPU_DX_VALIDATE(m_Device->CreateTexture3D(
            &desc,
            reinterpret_cast<const D3D11_SUBRESOURCE_DATA*>(args.Data),
            &result->m_Texture3D
        ));


        //
        // Get back actual texture desc.
        //
        result->m_Texture3D->GetDesc(&desc);

        result->m_Dimension = D3D11_SRV_DIMENSION_TEXTURE3D;
        result->m_MipLevels = desc.MipLevels;
        result->m_ArrayCount = 1;
        result->m_MiscFlags = desc.MiscFlags;
        result->m_Usage = desc.Usage;
        result->m_Format = args.DataFormat;
        

        //
        // Create shader view.
        //
        D3D11_SHADER_RESOURCE_VIEW_DESC view_desc{
            .Format = D3D11GpuGetReadViewPixelFormat(args.ViewFormat),
            .ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D,
            .Texture3D = {
                .MostDetailedMip = 0,
                .MipLevels = args.MipCount,
            },
        };

        GPU_DX_VALIDATE(m_Device->CreateShaderResourceView(
            result->m_Texture3D,
            &view_desc,
            &result->m_ShaderResourceView
        ));


        //
        // Create UAV.
        //

        if (has_uav)
        {
            D3D11_UNORDERED_ACCESS_VIEW_DESC uav_desc{
                .Format = D3D11GpuGetWriteViewPixelFormat(args.ViewFormat),
                .ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D,
                .Texture3D = {
                    .MipSlice = 0,
                    .FirstWSlice = 0,
                    .WSize = args.Depth,
                },
            };

            if (uav_desc.Format != DXGI_FORMAT_UNKNOWN)
            {
                GPU_DX_VALIDATE(m_Device->CreateUnorderedAccessView(
                    result->m_Texture3D,
                    &uav_desc,
                    &result->m_UnorderedAccessView
                ));
            }
        }


        //
        // Set debug name.
        //

#if ENABLE_GPU_API_DEBUG

        if (args.DebugName != nullptr)
        {
            D3D11SetDebugObjectName(
                result->m_Texture2D,
                args.DebugName,
                std::strlen(args.DebugName)
            );
        }

#endif

        return result;
    }

    void D3D11GpuDevice::DestroyTexture3D(
        GpuTexture3DHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuTexture*>(handle);

        GX_ASSERT(native->m_Dimension == D3D11_SRV_DIMENSION_TEXTURE3D);

        this->DeferResourceRelease(native->m_UnorderedAccessView);
        this->DeferResourceRelease(native->m_ShaderResourceView);
        this->DeferResourceRelease(native->m_Texture3D);

        delete native;
    }
}

namespace Graphyte::Graphics
{
    GpuTextureCubeHandle D3D11GpuDevice::CreateTextureCube(
        const GpuTextureCreateArgs& args
    ) noexcept
    {
        bool const has_uav = Flags::Has(args.Flags, GpuTextureFlags::UnorderedAccess);

        auto result = new D3D11GpuTexture();


        //
        // Create resource.
        //
        D3D11_TEXTURE2D_DESC desc{
            .Width = args.Width,
            .Height = args.Height,
            .MipLevels = args.MipCount,
            .ArraySize = 6,
            .Format = D3D11GpuGetCreateResourcePixelFormat(args.DataFormat),
            .SampleDesc = {
                .Count = 1,
                .Quality = 0,
            },
        };
        
        Impl::ExpandTextureFlags(
            args.Flags,
            desc.Usage,
            desc.BindFlags,
            desc.CPUAccessFlags,
            desc.MiscFlags
        );

        GPU_DX_VALIDATE(m_Device->CreateTexture2D(
            &desc,
            reinterpret_cast<const D3D11_SUBRESOURCE_DATA*>(args.Data),
            &result->m_Texture2D
        ));


        //
        // Get back actual texture desc.
        //
        result->m_Texture2D->GetDesc(&desc);

        result->m_Dimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
        result->m_MipLevels = desc.MipLevels;
        result->m_ArrayCount = 1;
        result->m_MiscFlags = desc.MiscFlags;
        result->m_Usage = desc.Usage;
        result->m_Format = args.DataFormat;

        
        //
        // Create shader view.
        //
        D3D11_SHADER_RESOURCE_VIEW_DESC view_desc{
            .Format = D3D11GpuGetReadViewPixelFormat(args.ViewFormat),
            .ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE,
            .TextureCube = {
                .MostDetailedMip = 0,
                .MipLevels = args.MipCount
            },
        };

        GPU_DX_VALIDATE(m_Device->CreateShaderResourceView(
            result->m_Texture2D,
            &view_desc,
            &result->m_ShaderResourceView
        ));


        //
        // Create UAV.
        //
        if (has_uav)
        {
            D3D11_UNORDERED_ACCESS_VIEW_DESC uav_desc{
                .Format = D3D11GpuGetWriteViewPixelFormat(args.ViewFormat),
                .ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2DARRAY,
                .Texture2DArray = {
                    .MipSlice = 0,
                    .FirstArraySlice = 0,
                    .ArraySize = 6,
                },
            };
        }

        return result;
    }

    void D3D11GpuDevice::DestroyTextureCube(
        GpuTextureCubeHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuTexture*>(handle);

        GX_ASSERT(native->m_Dimension == D3D11_SRV_DIMENSION_TEXTURECUBE);

        this->DeferResourceRelease(native->m_UnorderedAccessView);
        this->DeferResourceRelease(native->m_ShaderResourceView);
        this->DeferResourceRelease(native->m_Texture2D);

        delete native;
    }
}
