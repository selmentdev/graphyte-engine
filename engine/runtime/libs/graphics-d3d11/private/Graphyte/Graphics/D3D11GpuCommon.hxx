#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/String.hxx>

#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include <dxgi1_5.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxgiformat.h>
#include <DXGIMessages.h>
#include <wrl/client.h>

namespace Graphyte::Graphics
{
    void D3D11ReportFailure(
        HRESULT result,
        const char* expression,
        const char* file,
        unsigned int line,
        ID3D11Device* device
    ) noexcept;

    GX_DECLARE_LOG_CATEGORY(LogD3D11Render, Trace, Trace);

#define GPU_DX_VALIDATE(expression) \
    { \
        HRESULT _gx_hr_result = expression; \
        if (FAILED(_gx_hr_result)) \
        { \
            D3D11ReportFailure(_gx_hr_result, #expression, __FILE__, __LINE__, nullptr); \
        } \
    }

#define GPU_DX_VALIDATE_DEVICE(device, expression) \
    { \
        HRESULT _gx_hr_result = expression; \
        if (FAILED(_gx_hr_result)) \
        { \
            D3D11ReportFailure(_gx_hr_result, #expression, __FILE__, __LINE__, device); \
        } \
    }

    template <size_t N>
    __forceinline void D3D11SetDebugObjectName(
        ID3D11DeviceChild* resource,
        const char(&name)[N]
    ) noexcept
    {
        [[maybe_unused]] HRESULT hr =resource->SetPrivateData(
            WKPDID_D3DDebugObjectName,
            static_cast<UINT>(N - 1),
            name
        );

        GPU_DX_VALIDATE(hr);
    }

    __forceinline void D3D11SetDebugObjectName(
        ID3D11DeviceChild* resource,
        const char* name,
        size_t length
    ) noexcept
    {
        [[maybe_unused]] HRESULT hr =resource->SetPrivateData(
            WKPDID_D3DDebugObjectName,
            static_cast<UINT>(length),
            name
        );

        GPU_DX_VALIDATE(hr);
    }
}
