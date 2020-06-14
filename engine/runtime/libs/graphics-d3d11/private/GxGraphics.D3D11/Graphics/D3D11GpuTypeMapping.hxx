#pragma once
#include "D3D11GpuCommon.hxx"
#include "D3D11GpuSampler.hxx"
#include <GxBase/Diagnostics.hxx>

namespace Graphyte::Graphics
{
    struct D3D11GpuTypeMapping final
    {
        static inline D3D11_FILTER MapFilter(
            GpuFilter filter) noexcept
        {
            // Happens to be exactly the same for D3D11.
            return static_cast<D3D11_FILTER>(filter);
        }

        static inline D3D11_TEXTURE_ADDRESS_MODE TextureAddressMode(
            GpuSamplerAddressMode mode) noexcept
        {
            switch (mode)
            {
                case GpuSamplerAddressMode::Wrap:
                    return D3D11_TEXTURE_ADDRESS_WRAP;
                case GpuSamplerAddressMode::Mirror:
                    return D3D11_TEXTURE_ADDRESS_MIRROR;
                case GpuSamplerAddressMode::Clamp:
                    return D3D11_TEXTURE_ADDRESS_CLAMP;
                case GpuSamplerAddressMode::Border:
                    return D3D11_TEXTURE_ADDRESS_BORDER;
                case GpuSamplerAddressMode::MirrorOnce:
                    return D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;
            }

            GX_ASSERTF(false, "Invalid texture address mode: {}", static_cast<uint32_t>(mode));
            return D3D11_TEXTURE_ADDRESS_WRAP;
        }

        static inline D3D11_COMPARISON_FUNC ComparizonFunction(
            GpuCompareOperation function) noexcept
        {
            switch (function)
            {
                case GpuCompareOperation::Never:
                    return D3D11_COMPARISON_NEVER;
                case GpuCompareOperation::Less:
                    return D3D11_COMPARISON_LESS;
                case GpuCompareOperation::Equal:
                    return D3D11_COMPARISON_EQUAL;
                case GpuCompareOperation::LessEqual:
                    return D3D11_COMPARISON_LESS_EQUAL;
                case GpuCompareOperation::Greater:
                    return D3D11_COMPARISON_GREATER;
                case GpuCompareOperation::NotEqual:
                    return D3D11_COMPARISON_NOT_EQUAL;
                case GpuCompareOperation::GreaterEqual:
                    return D3D11_COMPARISON_GREATER_EQUAL;
                case GpuCompareOperation::Always:
                    return D3D11_COMPARISON_ALWAYS;
            }

            GX_ASSERTF(false, "Invalid comparizon function: {}", static_cast<uint32_t>(function));
            return D3D11_COMPARISON_LESS;
        }

        static inline D3D11_DEPTH_WRITE_MASK DepthWriteMask(
            GpuDepthWriteMask value) noexcept
        {
            switch (value)
            {
                case GpuDepthWriteMask::All:
                    return D3D11_DEPTH_WRITE_MASK_ALL;
                case GpuDepthWriteMask::Zero:
                    return D3D11_DEPTH_WRITE_MASK_ZERO;
            }

            GX_ASSERTF(false, "Invalid depth write mask: {}", static_cast<uint32_t>(value));
            return D3D11_DEPTH_WRITE_MASK_ALL;
        }

        static inline D3D11_STENCIL_OP StencilOp(
            GpuStencilOperation value) noexcept
        {
            switch (value)
            {
                case GpuStencilOperation::Keep:
                    return D3D11_STENCIL_OP_KEEP;
                case GpuStencilOperation::Zero:
                    return D3D11_STENCIL_OP_ZERO;
                case GpuStencilOperation::Replace:
                    return D3D11_STENCIL_OP_REPLACE;
                case GpuStencilOperation::IncrementSaturate:
                    return D3D11_STENCIL_OP_INCR_SAT;
                case GpuStencilOperation::DecrementSaturate:
                    return D3D11_STENCIL_OP_DECR_SAT;
                case GpuStencilOperation::Invert:
                    return D3D11_STENCIL_OP_INVERT;
                case GpuStencilOperation::Increment:
                    return D3D11_STENCIL_OP_INCR;
                case GpuStencilOperation::Decrement:
                    return D3D11_STENCIL_OP_DECR;
            }

            GX_ASSERTF(false, "Invalid stencil operation: {}", static_cast<uint32_t>(value));
            return D3D11_STENCIL_OP_KEEP;
        }

        static inline D3D11_BLEND_OP BlendOperation(
            GpuBlendOperation value) noexcept
        {
            switch (value)
            {
                case GpuBlendOperation::Add:
                    return D3D11_BLEND_OP_ADD;
                case GpuBlendOperation::Subtract:
                    return D3D11_BLEND_OP_SUBTRACT;
                case GpuBlendOperation::RevSubtract:
                    return D3D11_BLEND_OP_REV_SUBTRACT;
                case GpuBlendOperation::Min:
                    return D3D11_BLEND_OP_MIN;
                case GpuBlendOperation::Max:
                    return D3D11_BLEND_OP_MAX;
            }

            GX_ASSERTF(false, "Invalid blend operation: {}", static_cast<uint32_t>(value));
            return D3D11_BLEND_OP_ADD;
        }

        static inline D3D11_BLEND BlendType(
            GpuBlendType value) noexcept
        {
            switch (value)
            {
                case GpuBlendType::Zero:
                    return D3D11_BLEND_ZERO;
                case GpuBlendType::One:
                    return D3D11_BLEND_ONE;
                case GpuBlendType::SourceColor:
                    return D3D11_BLEND_SRC_COLOR;
                case GpuBlendType::InvSourceColor:
                    return D3D11_BLEND_INV_SRC_COLOR;
                case GpuBlendType::SourceAlpha:
                    return D3D11_BLEND_SRC_ALPHA;
                case GpuBlendType::InvSourceAlpha:
                    return D3D11_BLEND_INV_SRC_ALPHA;
                case GpuBlendType::DestinationAlpha:
                    return D3D11_BLEND_DEST_ALPHA;
                case GpuBlendType::InvDestinationAlpha:
                    return D3D11_BLEND_INV_DEST_ALPHA;
                case GpuBlendType::DestinationColor:
                    return D3D11_BLEND_DEST_COLOR;
                case GpuBlendType::InvDestinationColor:
                    return D3D11_BLEND_INV_DEST_COLOR;
                case GpuBlendType::SourceAlphaSaturate:
                    return D3D11_BLEND_SRC_ALPHA_SAT;
                case GpuBlendType::BlendFactor:
                    return D3D11_BLEND_BLEND_FACTOR;
                case GpuBlendType::InvBlendFactor:
                    return D3D11_BLEND_INV_BLEND_FACTOR;
                case GpuBlendType::Source1Color:
                    return D3D11_BLEND_SRC1_COLOR;
                case GpuBlendType::InvSource1Color:
                    return D3D11_BLEND_INV_SRC1_COLOR;
                case GpuBlendType::Source1Alpha:
                    return D3D11_BLEND_SRC1_ALPHA;
                case GpuBlendType::InvSource1Alpha:
                    return D3D11_BLEND_INV_SRC1_ALPHA;
            }

            GX_ASSERTF(false, "Invalid blend type: {}", static_cast<uint32_t>(value));
            return D3D11_BLEND_ZERO;
        }

        static inline D3D11_FILL_MODE FillMode(
            GpuFillMode value) noexcept
        {
            switch (value)
            {
                case GpuFillMode::Solid:
                    return D3D11_FILL_SOLID;
                case GpuFillMode::Wireframe:
                    return D3D11_FILL_WIREFRAME;
            }

            GX_ASSERTF(false, "Invalid fill mode: {}", static_cast<uint32_t>(value));
            return D3D11_FILL_SOLID;
        }

        static inline D3D11_CULL_MODE CullMode(
            GpuCullMode value) noexcept
        {
            switch (value)
            {
                case GpuCullMode::None:
                    return D3D11_CULL_NONE;
                case GpuCullMode::Front:
                    return D3D11_CULL_FRONT;
                case GpuCullMode::Back:
                    return D3D11_CULL_BACK;
            }

            GX_ASSERTF(false, "Invalid cull mode: {}", static_cast<uint32_t>(value));
            return D3D11_CULL_NONE;
        }

        static inline D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology(
            GpuPrimitiveTopology value) noexcept
        {
            switch (value)
            {
                case GpuPrimitiveTopology::Line:
                    return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
                case GpuPrimitiveTopology::LineStrip:
                    return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
                case GpuPrimitiveTopology::Patch:
                    return D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST;
                case GpuPrimitiveTopology::Point:
                    return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
                case GpuPrimitiveTopology::Triangle:
                    return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                case GpuPrimitiveTopology::TriangleStrip:
                    return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
            }

            GX_ASSERTF(false, "Invalid primitive topology: {}", static_cast<uint32_t>(value));
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        }
    };
}
