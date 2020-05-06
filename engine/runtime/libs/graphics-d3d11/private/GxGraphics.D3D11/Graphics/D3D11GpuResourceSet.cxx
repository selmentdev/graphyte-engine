#include "D3D11GpuResourceSet.hxx"
#include "D3D11GpuCommandList.hxx"
#include "D3D11GpuDevice.hxx"
#include "D3D11GpuUniformBuffer.hxx"
#include "D3D11GpuSampler.hxx"
#include "D3D11GpuTexture.hxx"

#include <GxBase/Flags.hxx>

namespace Graphyte::Graphics
{
    void D3D11GpuCommandList::BindResourceSet(
        GpuResourceSetHandle handle
    ) noexcept
    {
        auto native = static_cast<D3D11GpuResourceSet*>(handle);

        auto bind_texture = [&](
            GpuShaderType shader,
            UINT slot,
            ID3D11ShaderResourceView* view
        ) noexcept -> void
        {
            switch (shader)
            {
            case GpuShaderType::Pixel:
                {
                    m_Context->PSSetShaderResources(slot, 1, &view);
                    break;
                }
            case GpuShaderType::Vertex:
                {
                    m_Context->VSSetShaderResources(slot, 1, &view);
                    break;
                }
            case GpuShaderType::Geometry:
                {
                    m_Context->GSSetShaderResources(slot, 1, &view);
                    break;
                }
            case GpuShaderType::Hull:
                {
                    m_Context->HSSetShaderResources(slot, 1, &view);
                    break;
                }
            case GpuShaderType::Domain:
                {
                    m_Context->DSSetShaderResources(slot, 1, &view);
                    break;
                }
            case GpuShaderType::Compute:
                {
                    m_Context->CSSetShaderResources(slot, 1, &view);
                    break;
                }
            }
        };

        auto bind_sampler = [&](
            GpuShaderType shader,
            UINT slot,
            ID3D11SamplerState* sampler
        ) noexcept -> void
        {
            switch (shader)
            {
            case GpuShaderType::Pixel:
                {
                    m_Context->PSSetSamplers(slot, 1, &sampler);
                    break;
                }
            case GpuShaderType::Vertex:
                {
                    m_Context->VSSetSamplers(slot, 1, &sampler);
                    break;
                }
            case GpuShaderType::Geometry:
                {
                    m_Context->GSSetSamplers(slot, 1, &sampler);
                    break;
                }
            case GpuShaderType::Hull:
                {
                    m_Context->HSSetSamplers(slot, 1, &sampler);
                    break;
                }
            case GpuShaderType::Domain:
                {
                    m_Context->DSSetSamplers(slot, 1, &sampler);
                    break;
                }
            case GpuShaderType::Compute:
                {
                    m_Context->CSSetSamplers(slot, 1, &sampler);
                    break;
                }
            }
        };

        auto bind_uniform_buffer = [&](
            GpuShaderType shader,
            UINT slot,
            ID3D11Buffer* buffer
        ) noexcept -> void
        {
            switch (shader)
            {
            case GpuShaderType::Pixel:
                {
                    m_Context->PSSetConstantBuffers(slot, 1, &buffer);
                    break;
                }
            case GpuShaderType::Vertex:
                {
                    m_Context->VSSetConstantBuffers(slot, 1, &buffer);
                    break;
                }
            case GpuShaderType::Geometry:
                {
                    m_Context->GSSetConstantBuffers(slot, 1, &buffer);
                    break;
                }
            case GpuShaderType::Hull:
                {
                    m_Context->HSSetConstantBuffers(slot, 1, &buffer);
                    break;
                }
            case GpuShaderType::Domain:
                {
                    m_Context->DSSetConstantBuffers(slot, 1, &buffer);
                    break;
                }
            case GpuShaderType::Compute:
                {
                    m_Context->CSSetConstantBuffers(slot, 1, &buffer);
                    break;
                }
            }
        };

        for (size_t unit = static_cast<size_t>(GpuShaderType::Pixel); unit < static_cast<size_t>(GpuShaderType::Compute); ++unit)
        {
            auto shader = static_cast<GpuShaderType>(unit);

            for (size_t slot = 0; slot < native->m_Textures[unit].size(); ++slot)
            {
                auto* texture = native->m_Textures[unit][slot];
                if (texture != nullptr)
                {
                    bind_texture(shader, static_cast<UINT>(slot), texture);
                }
            }

            for (size_t slot = 0; slot < native->m_Samplers[unit].size(); ++slot)
            {
                auto* sampler = native->m_Samplers[unit][slot];
                if (sampler != nullptr)
                {
                    bind_sampler(shader, static_cast<UINT>(slot), sampler);
                }
            }

            for (size_t slot = 0; slot < native->m_UniformBuffers[unit].size(); ++slot)
            {
                auto* buffer = native->m_UniformBuffers[unit][slot];
                if (buffer != nullptr)
                {
                    bind_uniform_buffer(shader, static_cast<UINT>(slot), buffer);
                }
            }
        }
    }
}

namespace Graphyte::Graphics
{
    GpuResourceSetHandle D3D11GpuDevice::CreateResourceSet(
        const GpuResourceSetDesc& desc
    ) noexcept
    {
        auto result = new D3D11GpuResourceSet();
        
        for (auto& binding : desc.m_Bindings)
        {
            auto& slot = binding.Key.ShaderRegister;
            auto& visibility = binding.Key.ShaderVisibility;

            switch (binding.Key.ResourceType)
            {
            case GpuResourceType::UniformBuffer:
                {
                    auto native = static_cast<D3D11GpuUniformBuffer*>(binding.Resource.UniformBuffer);
                    GX_ASSERT(native != nullptr);

                    if (Flags::Has(visibility, GpuShaderVisibility::Pixel))
                    {
                        result->m_UniformBuffers[(size_t)GpuShaderType::Pixel][slot] = native->m_Resource;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Vertex))
                    {
                        result->m_UniformBuffers[(size_t)GpuShaderType::Vertex][slot] = native->m_Resource;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Geometry))
                    {
                        result->m_UniformBuffers[(size_t)GpuShaderType::Geometry][slot] = native->m_Resource;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Hull))
                    {
                        result->m_UniformBuffers[(size_t)GpuShaderType::Hull][slot] = native->m_Resource;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Domain))
                    {
                        result->m_UniformBuffers[(size_t)GpuShaderType::Domain][slot] = native->m_Resource;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Compute))
                    {
                        result->m_UniformBuffers[(size_t)GpuShaderType::Compute][slot] = native->m_Resource;
                    }

                    break;
                }
            case GpuResourceType::Sampler:
                {
                    auto native = static_cast<D3D11GpuSampler*>(binding.Resource.Sampler);
                    GX_ASSERT(native != nullptr);

                    if (Flags::Has(visibility, GpuShaderVisibility::Pixel))
                    {
                        result->m_Samplers[(size_t)GpuShaderType::Pixel][slot] = native->m_Sampler;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Vertex))
                    {
                        result->m_Samplers[(size_t)GpuShaderType::Vertex][slot] = native->m_Sampler;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Geometry))
                    {
                        result->m_Samplers[(size_t)GpuShaderType::Geometry][slot] = native->m_Sampler;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Hull))
                    {
                        result->m_Samplers[(size_t)GpuShaderType::Hull][slot] = native->m_Sampler;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Domain))
                    {
                        result->m_Samplers[(size_t)GpuShaderType::Domain][slot] = native->m_Sampler;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Compute))
                    {
                        result->m_Samplers[(size_t)GpuShaderType::Compute][slot] = native->m_Sampler;
                    }

                    break;
                }
            case GpuResourceType::Texture:
                {
                    auto native = static_cast<D3D11GpuTexture*>(binding.Resource.Texture);
                    GX_ASSERT(native != nullptr);

                    if (Flags::Has(visibility, GpuShaderVisibility::Pixel))
                    {
                        result->m_Textures[(size_t)GpuShaderType::Pixel][slot] = native->m_ShaderResourceView;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Vertex))
                    {
                        result->m_Textures[(size_t)GpuShaderType::Vertex][slot] = native->m_ShaderResourceView;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Geometry))
                    {
                        result->m_Textures[(size_t)GpuShaderType::Geometry][slot] = native->m_ShaderResourceView;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Hull))
                    {
                        result->m_Textures[(size_t)GpuShaderType::Hull][slot] = native->m_ShaderResourceView;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Domain))
                    {
                        result->m_Textures[(size_t)GpuShaderType::Domain][slot] = native->m_ShaderResourceView;
                    }

                    if (Flags::Has(visibility, GpuShaderVisibility::Compute))
                    {
                        result->m_Textures[(size_t)GpuShaderType::Compute][slot] = native->m_ShaderResourceView;
                    }

                    break;
                }
            case GpuResourceType::StructuredBuffer:
                {
                    // not supported right now.
                    break;
                }
            }
        }

        return result;
    }

    void D3D11GpuDevice::DestroyResourceSet(
        GpuResourceSetHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuResourceSet*>(handle);

        delete native;
    }

    void D3D11GpuDevice::UpdateResourceSet(
        GpuResourceSetHandle handle,
        const GpuResourceSetDesc& desc
    ) noexcept
    {
        (void)handle;
        (void)desc;
    }
}
