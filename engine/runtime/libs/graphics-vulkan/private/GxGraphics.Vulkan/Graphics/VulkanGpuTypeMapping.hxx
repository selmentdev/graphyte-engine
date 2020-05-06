#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    struct VulkanGpuTypeMapping final
    {
        static inline VkSamplerAddressMode TextureAddressMode(
            GpuSamplerAddressMode mode
        ) noexcept
        {
            switch (mode)
            {
            case GpuSamplerAddressMode::Wrap:
                return VK_SAMPLER_ADDRESS_MODE_REPEAT;
            case GpuSamplerAddressMode::Mirror:
                return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
            case GpuSamplerAddressMode::Clamp:
                return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            case GpuSamplerAddressMode::Border:
                return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
            case GpuSamplerAddressMode::MirrorOnce:
                return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
            }

            GX_ASSERTF(false, "Invalid texture address mode: {}", static_cast<uint32_t>(mode));
            return VK_SAMPLER_ADDRESS_MODE_REPEAT;
        }

        static inline VkCompareOp ComparizonFunction(
            GpuCompareOperation function
        ) noexcept
        {
            switch (function)
            {
            case GpuCompareOperation::Never:
                return VK_COMPARE_OP_NEVER;
            case GpuCompareOperation::Less:
                return VK_COMPARE_OP_LESS;
            case GpuCompareOperation::Equal:
                return VK_COMPARE_OP_EQUAL;
            case GpuCompareOperation::LessEqual:
                return VK_COMPARE_OP_LESS_OR_EQUAL;
            case GpuCompareOperation::Greater:
                return VK_COMPARE_OP_GREATER;
            case GpuCompareOperation::NotEqual:
                return VK_COMPARE_OP_NOT_EQUAL;
            case GpuCompareOperation::GreaterEqual:
                return VK_COMPARE_OP_GREATER_OR_EQUAL;
            case GpuCompareOperation::Always:
                return VK_COMPARE_OP_ALWAYS;
            }

            GX_ASSERTF(false, "Invalid comparizon function: {}", static_cast<uint32_t>(function));
            return VK_COMPARE_OP_LESS;
        }

        static inline uint32_t DepthWriteMask(
            GpuDepthWriteMask value
        ) noexcept
        {
            switch (value)
            {
            case GpuDepthWriteMask::All:
                return 0xff;
            case GpuDepthWriteMask::Zero:
                return 0x00;
            }

            GX_ASSERTF(false, "Invalid depth write mask: {}", static_cast<uint32_t>(value));
            return 0xff;
        }

        static inline VkStencilOp StencilOp(
            GpuStencilOperation value
        ) noexcept
        {
            switch (value)
            {
            case GpuStencilOperation::Keep:
                return VK_STENCIL_OP_KEEP;
            case GpuStencilOperation::Zero:
                return VK_STENCIL_OP_ZERO;
            case GpuStencilOperation::Replace:
                return VK_STENCIL_OP_REPLACE;
            case GpuStencilOperation::IncrementSaturate:
                return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
            case GpuStencilOperation::DecrementSaturate:
                return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
            case GpuStencilOperation::Invert:
                return VK_STENCIL_OP_INVERT;
            case GpuStencilOperation::Increment:
                return VK_STENCIL_OP_INCREMENT_AND_WRAP;
            case GpuStencilOperation::Decrement:
                return VK_STENCIL_OP_DECREMENT_AND_WRAP;
            }

            GX_ASSERTF(false, "Invalid stencil operation: {}", static_cast<uint32_t>(value));
            return VK_STENCIL_OP_KEEP;
        }

        static inline VkBlendOp BlendOperation(
            GpuBlendOperation value
        ) noexcept
        {
            switch (value)
            {
            case GpuBlendOperation::Add:
                return VK_BLEND_OP_ADD;
            case GpuBlendOperation::Subtract:
                return VK_BLEND_OP_SUBTRACT;
            case GpuBlendOperation::RevSubtract:
                return VK_BLEND_OP_REVERSE_SUBTRACT;
            case GpuBlendOperation::Min:
                return VK_BLEND_OP_MIN;
            case GpuBlendOperation::Max:
                return VK_BLEND_OP_MAX;
            }

            GX_ASSERTF(false, "Invalid blend operation: {}", static_cast<uint32_t>(value));
            return VK_BLEND_OP_ADD;
        }

        static inline VkBlendFactor BlendType(
            GpuBlendType value
        ) noexcept
        {
            switch (value)
            {
            case GpuBlendType::Zero:
                return VK_BLEND_FACTOR_ZERO;
            case GpuBlendType::One:
                return VK_BLEND_FACTOR_ONE;
            case GpuBlendType::SourceColor:
                return VK_BLEND_FACTOR_SRC_COLOR;
            case GpuBlendType::InvSourceColor:
                return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
            case GpuBlendType::SourceAlpha:
                return VK_BLEND_FACTOR_SRC_ALPHA;
            case GpuBlendType::InvSourceAlpha:
                return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
            case GpuBlendType::DestinationAlpha:
                return VK_BLEND_FACTOR_DST_ALPHA;
            case GpuBlendType::InvDestinationAlpha:
                return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
            case GpuBlendType::DestinationColor:
                return VK_BLEND_FACTOR_DST_COLOR;
            case GpuBlendType::InvDestinationColor:
                return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
            case GpuBlendType::SourceAlphaSaturate:
                return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
            case GpuBlendType::BlendFactor:
                return VK_BLEND_FACTOR_CONSTANT_COLOR;
            case GpuBlendType::InvBlendFactor:
                return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
            case GpuBlendType::Source1Color:
                return VK_BLEND_FACTOR_SRC1_COLOR;
            case GpuBlendType::InvSource1Color:
                return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
            case GpuBlendType::Source1Alpha:
                return VK_BLEND_FACTOR_SRC1_ALPHA;
            case GpuBlendType::InvSource1Alpha:
                return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
            }

            GX_ASSERTF(false, "Invalid blend type: {}", static_cast<uint32_t>(value));
            return VK_BLEND_FACTOR_ZERO;
        }

        static inline VkPolygonMode FillMode(
            GpuFillMode value
        ) noexcept
        {
            switch (value)
            {
            case GpuFillMode::Solid:
                return VK_POLYGON_MODE_FILL;
            case GpuFillMode::Wireframe:
                return VK_POLYGON_MODE_LINE;
            }

            GX_ASSERTF(false, "Invalid fill mode: {}", static_cast<uint32_t>(value));
            return VK_POLYGON_MODE_FILL;
        }

        static inline VkCullModeFlags CullMode(
            GpuCullMode value
        ) noexcept
        {
            switch (value)
            {
            case GpuCullMode::None:
                return VK_CULL_MODE_NONE;
            case GpuCullMode::Front:
                return VK_CULL_MODE_FRONT_BIT;
            case GpuCullMode::Back:
                return VK_CULL_MODE_BACK_BIT;
            }

            GX_ASSERTF(false, "Invalid cull mode: {}", static_cast<uint32_t>(value));
            return VK_CULL_MODE_NONE;
        }

        static inline VkPrimitiveTopology PrimitiveTopology(
            GpuPrimitiveTopology value
        ) noexcept
        {
            switch (value)
            {
            case GpuPrimitiveTopology::Line:
                return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
            case GpuPrimitiveTopology::LineStrip:
                return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
            case GpuPrimitiveTopology::Patch:
                return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
            case GpuPrimitiveTopology::Point:
                return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
            case GpuPrimitiveTopology::Triangle:
                return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
            case GpuPrimitiveTopology::TriangleStrip:
                return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
            }

            GX_ASSERTF(false, "Invalid primitive topology: {}", static_cast<uint32_t>(value));
            return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        }
    };
}
