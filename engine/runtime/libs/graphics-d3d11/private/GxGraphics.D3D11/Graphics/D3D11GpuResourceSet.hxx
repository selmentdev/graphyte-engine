#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuCommon.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuResourceSet : public GpuResourceSet
    {
    public:
        struct UniformBufferSlot final
        {
            ID3D11Buffer* Buffer;
            uint32_t Offset;
            uint32_t Size;
            uint32_t Slot;
        };

        struct ShaderResourceViewSlot final
        {
            ID3D11ShaderResourceView* Resource;
            uint32_t Slot;
        };

    public:
        std::array<std::array<ID3D11ShaderResourceView*, GpuLimits::TextureUnitsCount>, GpuLimits::ShaderUnitsCount> m_Textures;
        std::array<std::array<ID3D11SamplerState*, GpuLimits::TextureUnitsCount>, GpuLimits::ShaderUnitsCount> m_Samplers;
        std::array<std::array<ID3D11Buffer*, GpuLimits::UniformBuffersCount>, GpuLimits::ShaderUnitsCount> m_UniformBuffers;
    };
}
