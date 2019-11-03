#include "Graphics.pch.hxx"
#include "NullGpuDevice.hxx"
#include <Graphyte/Unicode.hxx>

namespace Graphyte::Graphics
{
    NullGpuDevice::NullGpuDevice() noexcept
        : m_ImmediateCommandList{ nullptr }
    {
    }

    NullGpuDevice::~NullGpuDevice() noexcept
    {
    }

    void NullGpuDevice::Tick(
        [[maybe_unused]] float time
    ) noexcept
    {
    }

    void NullGpuDevice::FlushLogs() noexcept
    {
    }
}
