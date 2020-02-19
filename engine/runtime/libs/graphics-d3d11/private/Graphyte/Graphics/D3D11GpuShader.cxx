#include "D3D11GpuShader.hxx"
#include "D3D11GpuTypeMapping.hxx"
#include "D3D11GpuDevice.hxx"

namespace Graphyte::Graphics
{
    static const std::array<D3D11_INPUT_ELEMENT_DESC, 6> D3D11_InputLayout_GpuVertexUI {
        {
            { .SemanticName = "POSITION",   .SemanticIndex = 0, .Format = DXGI_FORMAT_R32G32B32_FLOAT,  .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TEXCOORD",   .SemanticIndex = 0, .Format = DXGI_FORMAT_R16G16_FLOAT,     .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TEXCOORD",   .SemanticIndex = 1, .Format = DXGI_FORMAT_R16G16_FLOAT,     .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TEXCOORD",   .SemanticIndex = 2, .Format = DXGI_FORMAT_R16G16_FLOAT,     .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TEXCOORD",   .SemanticIndex = 3, .Format = DXGI_FORMAT_R16G16_FLOAT,     .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "COLOR",      .SemanticIndex = 0, .Format = DXGI_FORMAT_R8G8B8A8_UNORM,   .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
        }
    };

    static const std::array<D3D11_INPUT_ELEMENT_DESC, 4> D3D11_InputLayout_GpuVertexCompact {
        {
            { .SemanticName = "POSITION",   .SemanticIndex = 0, .Format = DXGI_FORMAT_R16G16B16A16_FLOAT,   .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "NORMAL",     .SemanticIndex = 0, .Format = DXGI_FORMAT_R8G8B8A8_SNORM,       .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TEXCOORD",   .SemanticIndex = 0, .Format = DXGI_FORMAT_R16G16_FLOAT,         .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TANGENT",    .SemanticIndex = 0, .Format = DXGI_FORMAT_R8G8B8A8_SNORM,       .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
        }
    };

    static const std::array<D3D11_INPUT_ELEMENT_DESC, 6> D3D11_InputLayout_GpuVertexComplex {
        {
            { .SemanticName = "POSITION",   .SemanticIndex = 0, .Format = DXGI_FORMAT_R32G32B32_FLOAT,  .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "NORMAL",     .SemanticIndex = 0, .Format = DXGI_FORMAT_R8G8B8A8_SNORM,   .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TANGENT",    .SemanticIndex = 0, .Format = DXGI_FORMAT_R8G8B8A8_SNORM,   .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TEXCOORD",   .SemanticIndex = 0, .Format = DXGI_FORMAT_R16G16_FLOAT,     .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "TEXCOORD",   .SemanticIndex = 1, .Format = DXGI_FORMAT_R16G16_FLOAT,     .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
            { .SemanticName = "COLOR",      .SemanticIndex = 0, .Format = DXGI_FORMAT_R8G8B8A8_UNORM,   .InputSlot = 0, .AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,  .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,  .InstanceDataStepRate = 0 },
        }
    };
}

namespace Graphyte::Graphics
{
    GpuShaderHandle D3D11GpuDevice::CreateShader(
        GpuShaderStage stage,
        GpuShaderBytecode bytecode,
        GpuInputLayout inputLayout
        ) noexcept
    {
        auto result = new D3D11GpuShader();
        result->m_Stage = stage;

        switch (stage)
        {
        case GpuShaderStage::Pixel:
            {
                GPU_DX_VALIDATE(m_Device->CreatePixelShader(
                    bytecode.Bytecode,
                    bytecode.Size,
                    nullptr,
                    &result->m_PS
                ));
                break;
            }
        case GpuShaderStage::Vertex:
            {
                GPU_DX_VALIDATE(m_Device->CreateVertexShader(
                    bytecode.Bytecode,
                    bytecode.Size,
                    nullptr,
                    &result->m_VS
                ));

                auto it = m_InputLayouts.find(inputLayout);
                if (it == m_InputLayouts.end())
                {

                    //
                    // Not found, try to create one using vertex shader and description.
                    //
                    const D3D11_INPUT_ELEMENT_DESC* layout_desc{};
                    UINT layout_size{};

                    switch (inputLayout)
                    {
                    case GpuInputLayout::Compact:
                        {
                            layout_desc = std::data(D3D11_InputLayout_GpuVertexCompact);
                            layout_size = static_cast<UINT>(std::size(D3D11_InputLayout_GpuVertexCompact));
                            break;
                        }
                    case GpuInputLayout::Complex:
                        {
                            layout_desc = std::data(D3D11_InputLayout_GpuVertexComplex);
                            layout_size = static_cast<UINT>(std::size(D3D11_InputLayout_GpuVertexComplex));
                            break;
                        }
                    case GpuInputLayout::UI:
                        {
                            layout_desc = std::data(D3D11_InputLayout_GpuVertexUI);
                            layout_size = static_cast<UINT>(std::size(D3D11_InputLayout_GpuVertexUI));
                            break;
                        }
                    }

                    GX_ASSERT(layout_desc != nullptr);
                    GX_ASSERT(layout_size != 0);

                    ID3D11InputLayout* layoutResource{};
                    GPU_DX_VALIDATE(m_Device->CreateInputLayout(
                        layout_desc,
                        layout_size,
                        bytecode.Bytecode,
                        bytecode.Size,
                        &layoutResource
                    ));

                    m_InputLayouts.insert(std::make_pair(inputLayout, layoutResource));
                }

                break;
            }
        case GpuShaderStage::Geometry:
            {
                GPU_DX_VALIDATE(m_Device->CreateGeometryShader(
                    bytecode.Bytecode,
                    bytecode.Size,
                    nullptr,
                    &result->m_GS
                ));
                break;
            }
        case GpuShaderStage::Hull:
            {
                GPU_DX_VALIDATE(m_Device->CreateHullShader(
                    bytecode.Bytecode,
                    bytecode.Size,
                    nullptr,
                    &result->m_HS
                ));
                break;
            }
        case GpuShaderStage::Domain:
            {
                GPU_DX_VALIDATE(m_Device->CreateDomainShader(
                    bytecode.Bytecode,
                    bytecode.Size,
                    nullptr,
                    &result->m_DS
                ));
                break;
            }
        case GpuShaderStage::Compute:
            {
                GPU_DX_VALIDATE(m_Device->CreateComputeShader(
                    bytecode.Bytecode,
                    bytecode.Size,
                    nullptr,
                    &result->m_CS
                ));
                break;
            }
        default:
            GX_ASSERT_NOT_IMPLEMENTED();
        }

        return result;
    }

    void D3D11GpuDevice::DestroyShader(
        GpuShaderHandle handle
        ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<D3D11GpuShader*>(handle);

        switch (native->m_Stage)
        {
        case GpuShaderStage::Pixel:
            {
                this->DeferResourceRelease(native->m_PS);
                break;
            }
        case GpuShaderStage::Vertex:
            {
                this->DeferResourceRelease(native->m_VS);
                break;
            }
        case GpuShaderStage::Geometry:
            {
                this->DeferResourceRelease(native->m_GS);
                break;
            }
        case GpuShaderStage::Hull:
            {
                this->DeferResourceRelease(native->m_HS);
                break;
            }
        case GpuShaderStage::Domain:
            {
                this->DeferResourceRelease(native->m_DS);
                break;
            }
        case GpuShaderStage::Compute:
            {
                this->DeferResourceRelease(native->m_CS);
                break;
            }
        default:
            GX_ASSERT_NOT_IMPLEMENTED();
        }

        delete native;
    }
}
