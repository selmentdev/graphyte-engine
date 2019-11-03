#pragma once
#include "OpenGLGpuCommon.hxx"
#include "OpenGLGpuSampler.hxx"
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::Graphics
{
    struct OpenGLGpuTypeMapping final
    {
        static inline GLenum TextureAddressMode(
            GpuSamplerAddressMode value
        ) noexcept
        {
            switch (value)
            {
            case GpuSamplerAddressMode::Wrap:
                return GL_REPEAT;
            case GpuSamplerAddressMode::Mirror:
                return GL_MIRRORED_REPEAT;
            case GpuSamplerAddressMode::Clamp:
                return GL_CLAMP_TO_EDGE;
            case GpuSamplerAddressMode::Border:
                return GL_CLAMP_TO_BORDER;
            case GpuSamplerAddressMode::MirrorOnce:
                return GL_MIRROR_CLAMP_TO_EDGE;
            }

            GX_ASSERTF(false, "Invalid texture address mode: {}", static_cast<uint32_t>(value));
            return GL_REPEAT;
        }

        static inline GLenum ComparizonFunction(
            GpuCompareOperation value
        ) noexcept
        {
            switch (value)
            {
            case GpuCompareOperation::Never:
                return GL_NEVER;
            case GpuCompareOperation::Less:
                return GL_LESS;
            case GpuCompareOperation::Equal:
                return GL_EQUAL;
            case GpuCompareOperation::LessEqual:
                return GL_LEQUAL;
            case GpuCompareOperation::Greater:
                return GL_GREATER;
            case GpuCompareOperation::NotEqual:
                return GL_NOTEQUAL;
            case GpuCompareOperation::GreaterEqual:
                return GL_GEQUAL;
            case GpuCompareOperation::Always:
                return GL_ALWAYS;
            }

            GX_ASSERTF(false, "Invalid comparizon function: {}", static_cast<uint32_t>(value));
            return GL_LESS;
        }

        static inline GLboolean DepthWriteMask(
            GpuDepthWriteMask value
        ) noexcept
        {
            switch (value)
            {
            case GpuDepthWriteMask::All:
                return GL_TRUE;
            case GpuDepthWriteMask::Zero:
                return GL_FALSE;
            }

            GX_ASSERTF(false, "Invalid depth write mask: {}", static_cast<uint32_t>(value));
            return GL_TRUE;
        }

        static inline GLenum StencilOperation(
            GpuStencilOperation value
        ) noexcept
        {
            switch (value)
            {
            case GpuStencilOperation::Keep:
                return GL_KEEP;
            case GpuStencilOperation::Zero:
                return GL_ZERO;
            case GpuStencilOperation::Replace:
                return GL_REPLACE;
            case GpuStencilOperation::IncrementSaturate:
                return GL_INCR;
            case GpuStencilOperation::DecrementSaturate:
                return GL_DECR;
            case GpuStencilOperation::Invert:
                return GL_INVERT;
            case GpuStencilOperation::Increment:
                return GL_INCR_WRAP;
            case GpuStencilOperation::Decrement:
                return GL_DECR_WRAP;
            }

            GX_ASSERTF(false, "Invalid stencil operation: {}", static_cast<uint32_t>(value));
            return GL_KEEP;
        }

        static inline GLenum BlendType(
            GpuBlendType value
        ) noexcept
        {
            switch (value)
            {
            case GpuBlendType::Zero:
                return GL_ZERO;
            case GpuBlendType::One:
                return GL_ONE;
            case GpuBlendType::SourceColor:
                return GL_SRC_COLOR;
            case GpuBlendType::InvSourceColor:
                return GL_ONE_MINUS_SRC_COLOR;
            case GpuBlendType::SourceAlpha:
                return GL_SRC_ALPHA;
            case GpuBlendType::InvSourceAlpha:
                return GL_ONE_MINUS_SRC_ALPHA;
            case GpuBlendType::DestinationAlpha:
                return GL_DST_ALPHA;
            case GpuBlendType::InvDestinationAlpha:
                return GL_ONE_MINUS_DST_ALPHA;
            case GpuBlendType::DestinationColor:
                return GL_DST_COLOR;
            case GpuBlendType::InvDestinationColor:
                return GL_ONE_MINUS_DST_COLOR;
            case GpuBlendType::SourceAlphaSaturate:
                return GL_SRC_ALPHA_SATURATE;
            case GpuBlendType::BlendFactor:
                return GL_CONSTANT_ALPHA;
            case GpuBlendType::InvBlendFactor:
                return GL_ONE_MINUS_CONSTANT_ALPHA;
            case GpuBlendType::Source1Color:
                return GL_SRC1_COLOR;
            case GpuBlendType::InvSource1Color:
                return GL_ONE_MINUS_SRC1_COLOR;
            case GpuBlendType::Source1Alpha:
                return GL_SRC1_ALPHA;
            case GpuBlendType::InvSource1Alpha:
                return GL_ONE_MINUS_SRC1_ALPHA;
            }

            GX_ASSERTF(false, "Invalid blend type: {}", static_cast<uint32_t>(value));
            return GL_ONE;
        }

        static inline GLenum BlendOperation(
            GpuBlendOperation value
        ) noexcept
        {
            switch (value)
            {
            case GpuBlendOperation::Add:
                return GL_FUNC_ADD;
            case GpuBlendOperation::Subtract:
                return GL_FUNC_SUBTRACT;
            case GpuBlendOperation::RevSubtract:
                return GL_FUNC_REVERSE_SUBTRACT;
            case GpuBlendOperation::Min:
                return GL_MIN;
            case GpuBlendOperation::Max:
                return GL_MAX;
            }

            GX_ASSERTF(false, "Invalid blend operation: {}", static_cast<uint32_t>(value));
            return GL_FUNC_ADD;
        }

        static inline GLenum FillMode(
            GpuFillMode value
        ) noexcept
        {
            switch (value)
            {
            case GpuFillMode::Wireframe:
                return GL_LINE;
            case GpuFillMode::Solid:
                return GL_FILL;
            }

            GX_ASSERTF(false, "Invalid fill mode: {}", static_cast<uint32_t>(value));
            return GL_FILL;
        }

        static inline GLenum CullMode(
            GpuCullMode value
        ) noexcept
        {
            switch (value)
            {
            case GpuCullMode::Front:
                return GL_FRONT;
            case GpuCullMode::Back:
                return GL_BACK;
            case GpuCullMode::None:
                //GX_ASSERTF(false, "GpuCullMode::None shouldn't be passed to this function. Check other code for disabling culling instead.");
                return GL_BACK;
            }
            GX_ASSERTF(false, "Invalid cull mode: {}", static_cast<uint32_t>(value));
            return GL_BACK;
        }

        static inline GLenum PrimitiveTopology(
            GpuPrimitiveTopology value
        ) noexcept
        {
            switch (value)
            {
            case GpuPrimitiveTopology::Point:
                return GL_POINTS;
            case GpuPrimitiveTopology::Line:
                return GL_LINES;
            case GpuPrimitiveTopology::LineStrip:
                return GL_LINE_STRIP;
            case GpuPrimitiveTopology::Triangle:
                return GL_TRIANGLES;
            case GpuPrimitiveTopology::TriangleStrip:
                return GL_TRIANGLE_STRIP;
            case GpuPrimitiveTopology::Patch:
                return GL_PATCHES;
            }

            GX_ASSERTF(false, "Invalid primitive topology: {}", static_cast<uint32_t>(value));
            return GL_TRIANGLES;
        }
    };
}
