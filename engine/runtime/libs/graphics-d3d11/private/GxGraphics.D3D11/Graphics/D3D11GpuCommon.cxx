#include <GxBase/Application.hxx>

#include "D3D11GpuCommon.hxx"

namespace Graphyte::Graphics
{
    GX_DEFINE_LOG_CATEGORY(LogD3D11Render);

    __forceinline std::string D3D11GetErrorMessage(
        HRESULT hr) noexcept
    {
        return fmt::format("{}: HRESULT = {:08x}", Diagnostics::GetMessageFromHRESULT(hr), hr);
    }

    void D3D11CheckDeviceRemoved(
        HRESULT hr,
        ID3D11Device* device) noexcept
    {
        GX_ASSERT(hr == DXGI_ERROR_DEVICE_REMOVED);
        (void)hr;
        (void)device;

        GX_ABORT("Device removed: {} {}\n",
            Diagnostics::GetMessageFromHRESULT(hr),
            Diagnostics::GetMessageFromHRESULT(device->GetDeviceRemovedReason()));
    }

    void D3D11CheckDeviceOutOfMemory(
        HRESULT hr) noexcept
    {
        GX_ASSERT(hr == E_OUTOFMEMORY);

        GX_ABORT("Device: out of memory: {:08x}\n", static_cast<uint32_t>(hr));
    }

    void D3D11ReportFailure(
        HRESULT result,
        const char* expression,
        const char* file,
        unsigned int line,
        ID3D11Device* device) noexcept
    {
        GX_ASSERT(FAILED(result));

        auto error = D3D11GetErrorMessage(result);

        if (result == DXGI_ERROR_DEVICE_REMOVED)
        {
            D3D11CheckDeviceRemoved(result, device);
        }
        else if (result == E_OUTOFMEMORY)
        {
            D3D11CheckDeviceOutOfMemory(result);
        }

        GX_LOG(LogD3D11Render, Fatal, "{} failed at {}:{} with error {}\n", expression, file, line, error.c_str());
    }
}
