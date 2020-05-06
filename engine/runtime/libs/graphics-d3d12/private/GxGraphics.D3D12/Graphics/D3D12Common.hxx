#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/String.hxx>

#include <d3d12.h>
#include <d3d12sdklayers.h>
#include <d3d12shader.h>
#include <d3d12video.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <dxgi1_5.h>
#include <dxgi1_6.h>
#include <DXGIMessages.h>
#include <dxgidebug.h>
#include <dxgiformat.h>
#include <wrl/client.h>
#include "common/d3dx12.h"

namespace Graphyte::Graphics::Render
{
    GX_DECLARE_LOG_CATEGORY(LogD3D12Render, Trace, Trace);

    __forceinline void D3D12Verify(HRESULT result) noexcept
    {
        if (FAILED(result))
        {
            auto message = fmt::format("D3D11 failure: HRESULT[{:08x}]", result);

            Diagnostic::Debug::Write(message.c_str());
            Diagnostic::Debug::Fail(message.c_str());
        }
    }

    GRAPHICS_API const char* D3DGetErrorString(HRESULT hr) noexcept;
}
