#include "D3D11GpuSampler.hxx"
#include "D3D11GpuTypeMapping.hxx"
#include "D3D11GpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuSamplerHandle D3D11GpuDevice::CreateSampler(
        const GpuSamplerCreateArgs& args
    ) noexcept
    {
        D3D11_SAMPLER_DESC desc{
            .Filter = D3D11GpuTypeMapping::MapFilter(args.Filter),
            .AddressU = D3D11GpuTypeMapping::TextureAddressMode(args.AddressU),
            .AddressV = D3D11GpuTypeMapping::TextureAddressMode(args.AddressV),
            .AddressW = D3D11GpuTypeMapping::TextureAddressMode(args.AddressW),
            .MipLODBias = args.MipLodBias,
            .MaxAnisotropy = args.MaxAnisotropy,
            .ComparisonFunc = D3D11GpuTypeMapping::ComparizonFunction(args.CompareOp),
            .BorderColor = {
                args.BorderColor[0],
                args.BorderColor[1],
                args.BorderColor[2],
                args.BorderColor[3],
            },
            .MinLOD = args.MinLod,
            .MaxLOD = args.MaxLod,
        };

        ID3D11SamplerState* sampler_state{};
        GPU_DX_VALIDATE(m_Device->CreateSamplerState(
            &desc,
            &sampler_state
        ));

        auto result = new D3D11GpuSampler();
        result->m_Sampler = sampler_state;
        return result;
    }

    void D3D11GpuDevice::DestroySampler(
        GpuSamplerHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<D3D11GpuSampler*>(handle);

        this->DeferResourceRelease(native->m_Sampler);

        delete native;
    }
}
