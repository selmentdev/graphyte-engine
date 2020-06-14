#include "D3D11GpuGraphicsPipelineState.hxx"
#include "D3D11GpuDevice.hxx"
#include "D3D11GpuShader.hxx"
#include "D3D11GpuTypeMapping.hxx"
#include <GxBase/Hash/FNV.hxx>
#include <GxBase/Bitwise.hxx>

namespace Graphyte::Graphics
{
    namespace Impl
    {
        using GpuHash = Hash::HashFnv1A64;

        __forceinline uint64_t Hash(
            const GpuBlendStateDesc& state) noexcept
        {
            return GpuHash::FromBuffer(
                reinterpret_cast<const std::byte*>(&state),
                sizeof(state));
        }

        __forceinline uint64_t Hash(
            const GpuRasterizerStateDesc& state) noexcept
        {
            return GpuHash::FromBuffer(
                reinterpret_cast<const std::byte*>(&state),
                sizeof(state));
        }

        __forceinline uint64_t Hash(
            const GpuDepthStencilStateDesc& state) noexcept
        {
            return GpuHash::FromBuffer(
                reinterpret_cast<const std::byte*>(&state),
                sizeof(state));
        }
    }

    GpuGraphicsPipelineStateHandle D3D11GpuDevice::CreateGraphicsPipelineState(
        const GpuGraphicsPipelineStateCreateArgs& args,
        const GpuResourceSetDesc& layout) noexcept
    {
        auto result = new D3D11GpuGraphicsPipelineState{};

        if (args.VertexShader != nullptr)
        {
            result->m_VS = static_cast<D3D11GpuShader*>(args.VertexShader)->m_VS;
        }

        if (args.PixelShader != nullptr)
        {
            result->m_PS = static_cast<D3D11GpuShader*>(args.PixelShader)->m_PS;
        }

        if (args.GeometryShader != nullptr)
        {
            result->m_GS = static_cast<D3D11GpuShader*>(args.GeometryShader)->m_GS;
        }

        if (args.DomainShader != nullptr)
        {
            result->m_DS = static_cast<D3D11GpuShader*>(args.DomainShader)->m_DS;
        }

        if (args.HullShader != nullptr)
        {
            result->m_HS = static_cast<D3D11GpuShader*>(args.HullShader)->m_HS;
        }


        //
        // Allocate input layout.
        //
        {
            ID3D11InputLayout* input_layout{};

            auto it = this->m_InputLayouts.find(args.InputLayout);
            if (it != m_InputLayouts.end())
            {
                input_layout = it->second;
            }

            GX_ASSERT(input_layout != nullptr);
            result->m_InputLayout = input_layout;
        }

        //
        // Create depth stencil state.
        //
        {
            auto key = Impl::Hash(args.DepthStencilState);
            GX_LOG(LogD3D11Render, Trace, "[D3D11]: DepthStencilState - {}\n", key);

            auto it = m_DepthStencilState.find(key);

            ID3D11DepthStencilState* depth_stencil{};

            if (it != m_DepthStencilState.end())
            {
                depth_stencil = it->second;
            }
            else
            {
                D3D11_DEPTH_STENCIL_DESC desc{
                    .DepthEnable    = args.DepthStencilState.DepthEnable ? TRUE : FALSE,
                    .DepthWriteMask = D3D11GpuTypeMapping::DepthWriteMask(args.DepthStencilState.DepthWriteMask),
                    .DepthFunc      = D3D11GpuTypeMapping::ComparizonFunction(args.DepthStencilState.DepthCompare),

                    .StencilEnable    = args.DepthStencilState.StencilEnable ? TRUE : FALSE,
                    .StencilReadMask  = args.DepthStencilState.StencilReadMask,
                    .StencilWriteMask = args.DepthStencilState.StencilWriteMask,

                    .FrontFace = {
                        .StencilFailOp      = D3D11GpuTypeMapping::StencilOp(args.DepthStencilState.FrontFace.Fail),
                        .StencilDepthFailOp = D3D11GpuTypeMapping::StencilOp(args.DepthStencilState.FrontFace.DepthFail),
                        .StencilPassOp      = D3D11GpuTypeMapping::StencilOp(args.DepthStencilState.FrontFace.Pass),
                        .StencilFunc        = D3D11GpuTypeMapping::ComparizonFunction(args.DepthStencilState.FrontFace.Compare),
                    },

                    .BackFace = { .StencilFailOp = D3D11GpuTypeMapping::StencilOp(args.DepthStencilState.BackFace.Fail), .StencilDepthFailOp = D3D11GpuTypeMapping::StencilOp(args.DepthStencilState.BackFace.DepthFail), .StencilPassOp = D3D11GpuTypeMapping::StencilOp(args.DepthStencilState.BackFace.Pass), .StencilFunc = D3D11GpuTypeMapping::ComparizonFunction(args.DepthStencilState.BackFace.Compare) },
                };

                GPU_DX_VALIDATE(m_Device->CreateDepthStencilState(&desc, &depth_stencil));

                m_DepthStencilState.insert(std::make_pair(key, depth_stencil));
            }

            GX_ASSERT(depth_stencil != nullptr);
            depth_stencil->AddRef();
            result->m_DepthStencilState = depth_stencil;
        }

        //
        // Create blend state.
        //
        {
            auto key = Impl::Hash(args.BlendState);
            GX_LOG(LogD3D11Render, Trace, "[D3D11]: BlendState - {}\n", key);

            auto it = m_BlendState.find(key);

            ID3D11BlendState* blend_state_object{};

            if (it != m_BlendState.end())
            {
                blend_state_object = it->second;
            }
            else
            {
                D3D11_BLEND_DESC desc{
                    .AlphaToCoverageEnable  = args.BlendState.AlphaToCoverage ? TRUE : FALSE,
                    .IndependentBlendEnable = args.BlendState.IndependentBlend ? TRUE : FALSE,
                };

                GX_ASSERT(std::size(desc.RenderTarget) == std::size(args.BlendState.RenderTarget));

                for (size_t i = 0; i < std::size(desc.RenderTarget); ++i)
                {
                    if (args.BlendState.RenderTarget[i].BlendEnable)
                    {
                        //
                        // Copyout params only when we have actual values.
                        //

                        desc.RenderTarget[i] = {
                            .BlendEnable = TRUE,

                            .SrcBlend  = D3D11GpuTypeMapping::BlendType(args.BlendState.RenderTarget[i].SourceBlendColor),
                            .DestBlend = D3D11GpuTypeMapping::BlendType(args.BlendState.RenderTarget[i].DestinationBlendColor),
                            .BlendOp   = D3D11GpuTypeMapping::BlendOperation(args.BlendState.RenderTarget[i].BlendOperationColor),

                            .SrcBlendAlpha  = D3D11GpuTypeMapping::BlendType(args.BlendState.RenderTarget[i].SourceBlendAlpha),
                            .DestBlendAlpha = D3D11GpuTypeMapping::BlendType(args.BlendState.RenderTarget[i].DestinationBlendAlpha),
                            .BlendOpAlpha   = D3D11GpuTypeMapping::BlendOperation(args.BlendState.RenderTarget[i].BlendOperationAlpha),

                            .RenderTargetWriteMask = static_cast<UINT8>(args.BlendState.RenderTarget[i].RenderTargetWriteMask),
                        };
                    }
                    else
                    {
                        desc.RenderTarget[i] = {
                            .BlendEnable           = FALSE,
                            .SrcBlend              = D3D11_BLEND_ONE,
                            .DestBlend             = D3D11_BLEND_ZERO,
                            .BlendOp               = D3D11_BLEND_OP_ADD,
                            .SrcBlendAlpha         = D3D11_BLEND_ONE,
                            .DestBlendAlpha        = D3D11_BLEND_ZERO,
                            .BlendOpAlpha          = D3D11_BLEND_OP_ADD,
                            .RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL,
                        };
                    }
                }

                GPU_DX_VALIDATE(m_Device->CreateBlendState(&desc, &blend_state_object));

                m_BlendState.insert(std::make_pair(key, blend_state_object));
            }

            GX_ASSERT(blend_state_object != nullptr);
            blend_state_object->AddRef();
            result->m_BlendState = blend_state_object;
        }


        //
        // Create rasterizer state.
        //
        {
            auto key = Impl::Hash(args.RasterizerState);
            GX_LOG(LogD3D11Render, Trace, "[D3D11]: RasterizerState - {}\n", key);

            auto it = m_RasterizerState.find(key);

            ID3D11RasterizerState* rasterizer_state_object{};

            if (it != m_RasterizerState.end())
            {
                rasterizer_state_object = it->second;
            }
            else
            {
                D3D11_RASTERIZER_DESC desc{
                    .FillMode              = D3D11GpuTypeMapping::FillMode(args.RasterizerState.FillMode),
                    .CullMode              = D3D11GpuTypeMapping::CullMode(args.RasterizerState.CullMode),
                    .FrontCounterClockwise = args.RasterizerState.FrontCounterClockwise ? TRUE : FALSE,
                    .DepthBias             = args.RasterizerState.DepthBias,
                    .DepthBiasClamp        = args.RasterizerState.DepthBiasClamp,
                    .SlopeScaledDepthBias  = args.RasterizerState.SlopeScaledDepthBias,
                    .DepthClipEnable       = args.RasterizerState.DepthClipEnable ? TRUE : FALSE,
                    .ScissorEnable         = args.RasterizerState.ScissorEnable ? TRUE : FALSE,
                    .MultisampleEnable     = args.RasterizerState.MultisampleEnable ? TRUE : FALSE,
                    .AntialiasedLineEnable = args.RasterizerState.AntialiasedLineEnable ? TRUE : FALSE,
                };

                GPU_DX_VALIDATE(m_Device->CreateRasterizerState(&desc, &rasterizer_state_object));

                m_RasterizerState.insert(std::make_pair(key, rasterizer_state_object));
            }

            GX_ASSERT(rasterizer_state_object != nullptr);
            rasterizer_state_object->AddRef();
            result->m_RasterizerState = rasterizer_state_object;
        }

        //
        // D3D11 implementation doesn't use resource layout anyway.
        //
        (void)layout;


        //
        // Non-state params.
        //
        result->m_BlendState_SampleMask   = args.BlendState.SampleMask;
        result->m_BlendState_BlendFactors = args.BlendState.BlendFactors;
        result->m_PrimitiveTopology       = D3D11GpuTypeMapping::PrimitiveTopology(args.Topology);

        return result;
    }

    void D3D11GpuDevice::DestroyGraphicsPipelineState(
        GpuGraphicsPipelineStateHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuGraphicsPipelineState*>(handle);

        this->DeferResourceRelease(native->m_VS);
        this->DeferResourceRelease(native->m_PS);
        this->DeferResourceRelease(native->m_GS);
        this->DeferResourceRelease(native->m_DS);
        this->DeferResourceRelease(native->m_HS);
        this->DeferResourceRelease(native->m_BlendState);
        this->DeferResourceRelease(native->m_RasterizerState);
        this->DeferResourceRelease(native->m_DepthStencilState);

        delete native;
    }
}
