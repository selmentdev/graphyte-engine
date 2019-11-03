#pragma once
#include "D3D12Common.hxx"
#include <Graphyte/Graphics/PixelFormat.hxx>

namespace Graphyte::Graphics::Render
{
    DXGI_FORMAT D3D12GetPixelFormat(PixelFormat format) noexcept;
    DXGI_FORMAT D3D12GetRenderTargetFormat(PixelFormat format) noexcept;
}
