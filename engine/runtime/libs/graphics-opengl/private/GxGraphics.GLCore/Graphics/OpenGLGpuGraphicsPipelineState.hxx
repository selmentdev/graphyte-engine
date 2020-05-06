#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuCommon.hxx"

namespace Graphyte::Graphics
{
    struct OpenGLNativeRenderTargetBlend final
    {
        GLboolean Enable;
        GLenum SourceBlendColor;
        GLenum DestinationBlendColor;
        GLenum BlendOperationColor;
        GLenum SourceBlendAlpha;
        GLenum DestinationBlendAlpha;
        GLenum BlendOperationAlpha;
        GLboolean WriteMaskR;
        GLboolean WriteMaskG;
        GLboolean WriteMaskB;
        GLboolean WriteMaskA;
    };

    struct OpenGLNativeBlendState final
    {
        GLboolean AlphaToCoverage;
        GLboolean IndependentBlendEnable;
        OpenGLNativeRenderTargetBlend RenderTarget[8];
        GLuint SampleMask;
        GLfloat BlendFactors[4];
    };

    struct OpenGLNativeRasterizerState final
    {
        GLenum FillMode;
        GLenum CullMode;
        GLboolean FrontCounterClockwise;
        GLboolean CullEnable;
        GLint DepthBias;
        GLfloat DepthBiasClamp;
        GLfloat SlopeScaleDepthBias;
        GLboolean DepthClipEnable;
        GLboolean ScissorEnable;
        GLboolean MultisampleEnable;
        GLboolean AntialiasedLineEnable;
        GLboolean ConservativeRasterizationMode;
    };

    struct OpenGLNativeStencilOperationState final
    {
        GLenum Fail;
        GLenum DepthFail;
        GLenum Pass;
        GLenum Comparizon;
    };

    struct OpenGLNativeDepthStencilState final
    {
        GLboolean DepthWriteMask;
        GLenum DepthFunction;
        GLboolean DepthEnable;
        GLboolean StencilEnable;
        GLboolean DepthBoundsTestEnable;
        GLubyte StencilReadMask;
        GLubyte StencilWriteMask;
        OpenGLNativeStencilOperationState FrontFace;
        OpenGLNativeStencilOperationState BackFace;
    };

    class OpenGLGpuGraphicsPipelineState final : public GpuGraphicsPipelineState
    {
    public:
        GLuint m_VertexArrayObject;
        GLuint m_Program;

        OpenGLNativeRasterizerState m_RasterizerState;
        OpenGLNativeBlendState m_BlendState;
        OpenGLNativeDepthStencilState m_DepthStencilState;
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuGraphicsPipelineState>);
}
