#pragma once
#include "D3D11GpuCommon.hxx"
#include <GxGraphics/Graphics/PixelFormat.hxx>

namespace Graphyte::Graphics
{
    PixelFormat D3D11GpuGetPixelFormat(
        DXGI_FORMAT format) noexcept;

    DXGI_FORMAT D3D11GpuGetPixelFormat(
        PixelFormat format) noexcept;

    DXGI_FORMAT D3D11GpuGetCreateResourcePixelFormat(
        PixelFormat format) noexcept;

    DXGI_FORMAT D3D11GpuGetRenderTargetFormat(
        PixelFormat format) noexcept;

    DXGI_FORMAT D3D11GpuGetReadViewPixelFormat(
        PixelFormat format) noexcept;

    DXGI_FORMAT D3D11GpuGetWriteViewPixelFormat(
        PixelFormat format) noexcept;
}
