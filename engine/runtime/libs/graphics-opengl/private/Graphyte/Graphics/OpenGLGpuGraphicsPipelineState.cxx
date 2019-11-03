#include "Graphics.GLCore.pch.hxx"
#include "OpenGLGpuGraphicsPipelineState.hxx"
#include "OpenGLGpuDevice.hxx"
#include <Graphyte/Graphics/Gpu/GpuVertex.hxx>
#include <Graphyte/Hash/FNV.hxx>
#include <Graphyte/Bitwise.hxx>
#include "OpenGLGpuTypeMapping.hxx"
#include "OpenGLGpuShader.hxx"

namespace Graphyte::Graphics
{
    struct OpenGLVertexFormat final
    {
        GLuint Binding;
        GLsizei Size;
        GLenum Type;
        GLboolean Normalized;
        GLuint Offset;

        static const GLuint MaxAttributes = 16;
    };

    static const std::array<OpenGLVertexFormat, 6> GL_InputLayout_GpuVertexUI
    {
        {
            { 0, 3, GL_FLOAT,         GL_FALSE, offsetof(GpuVertexUI, Position) },
            { 0, 2, GL_HALF_FLOAT,    GL_FALSE, offsetof(GpuVertexUI, UV[0]) },
            { 0, 2, GL_HALF_FLOAT,    GL_FALSE, offsetof(GpuVertexUI, UV[1]) },
            { 0, 2, GL_HALF_FLOAT,    GL_FALSE, offsetof(GpuVertexUI, UV[2]) },
            { 0, 2, GL_HALF_FLOAT,    GL_FALSE, offsetof(GpuVertexUI, UV[3]) },
            { 0, 4, GL_UNSIGNED_BYTE, GL_TRUE,  offsetof(GpuVertexUI, Color) },
        }
    };

    static const std::array<OpenGLVertexFormat, 4> GL_InputLayout_GpuVertexCompact
    {
        {
            { 0, 4, GL_HALF_FLOAT,  GL_FALSE, offsetof(GpuVertexCompact, Position) },
            { 0, 4, GL_BYTE,        GL_TRUE,  offsetof(GpuVertexCompact, Normal) },
            { 0, 2, GL_HALF_FLOAT,  GL_FALSE, offsetof(GpuVertexCompact, UV) },
            { 0, 4, GL_BYTE,        GL_TRUE,  offsetof(GpuVertexCompact, Tangent) },
        }
    };

    static const std::array<OpenGLVertexFormat, 6> GL_InputLayout_GpuVertexComplex
    {
        {
            { 0, 3, GL_FLOAT,         GL_FALSE, offsetof(GpuVertexComplex, Position) },
            { 0, 4, GL_BYTE,          GL_TRUE,  offsetof(GpuVertexComplex, Normal) },
            { 0, 4, GL_BYTE,          GL_TRUE,  offsetof(GpuVertexComplex, Tangent) },
            { 0, 2, GL_HALF_FLOAT,    GL_FALSE, offsetof(GpuVertexComplex, UV[0]) },
            { 0, 2, GL_HALF_FLOAT,    GL_FALSE, offsetof(GpuVertexComplex, UV[1]) },
            { 0, 4, GL_UNSIGNED_BYTE, GL_TRUE,  offsetof(GpuVertexComplex, Color) },
        }
    };
}

namespace Graphyte::Graphics
{
    GpuGraphicsPipelineStateHandle OpenGLGpuDevice::CreateGraphicsPipelineState(
        const GpuGraphicsPipelineStateCreateArgs& args,
        const GpuResourceSetDesc& layout
    ) noexcept
    {
        auto native = new OpenGLGpuGraphicsPipelineState();

        GPU_GL_VALIDATE(glCreateVertexArrays(
            1,
            &native->m_VertexArrayObject
        ));

        auto bind_format = [&](const OpenGLVertexFormat* data, size_t count) noexcept
        {
            for (GLuint i = 0; i < OpenGLVertexFormat::MaxAttributes; ++i)
            {
                if (i < count)
                {
                    GPU_GL_VALIDATE(glEnableVertexArrayAttrib(
                        native->m_VertexArrayObject,
                        i
                    ));

                    GPU_GL_VALIDATE(glVertexArrayAttribFormat(
                        native->m_VertexArrayObject,
                        i,
                        data[i].Size,
                        data[i].Type,
                        data[i].Normalized,
                        data[i].Offset
                    ));

                    GPU_GL_VALIDATE(glVertexArrayAttribBinding(
                        native->m_VertexArrayObject,
                        i,
                        data[i].Binding
                    ));
                }
                else
                {
                    GPU_GL_VALIDATE(glDisableVertexArrayAttrib(
                        native->m_VertexArrayObject,
                        i
                    ));
                }
            }
        };

        switch (args.InputLayout)
        {
        case GpuInputLayout::UI:
            bind_format(
                std::data(GL_InputLayout_GpuVertexUI),
                std::size(GL_InputLayout_GpuVertexUI)
            );

            break;

        case GpuInputLayout::Compact:
            bind_format(
                std::data(GL_InputLayout_GpuVertexCompact),
                std::size(GL_InputLayout_GpuVertexCompact)
            );

            break;

        case GpuInputLayout::Complex:
            bind_format(
                std::data(GL_InputLayout_GpuVertexComplex),
                std::size(GL_InputLayout_GpuVertexComplex)
            );

            break;
        }

#if ENABLE_GPU_API_DEBUG
        GPU_GL_VALIDATE(glObjectLabel(
            GL_VERTEX_ARRAY,
            native->m_VertexArrayObject,
            static_cast<GLsizei>(strlen("Pipeline VAO")),
            "Pipeline VAO"
        ));
#endif

        GPU_GL_VALIDATE(
            native->m_Program = glCreateProgram()
        );

#if ENABLE_GPU_API_DEBUG
        GPU_GL_VALIDATE(glObjectLabel(
            GL_PROGRAM,
            native->m_Program,
            static_cast<GLsizei>(strlen("Pipeline Program")),
            "Pipeline Program"
        ));
#endif

        if (args.PixelShader != nullptr)
        {
            GPU_GL_VALIDATE(glAttachShader(
                native->m_Program,
                static_cast<OpenGLGpuShader*>(args.PixelShader)->m_Resource
            ));
        }

        if (args.VertexShader != nullptr)
        {
            GPU_GL_VALIDATE(glAttachShader(
                native->m_Program,
                static_cast<OpenGLGpuShader*>(args.VertexShader)->m_Resource
            ));
        }

        if (args.GeometryShader != nullptr)
        {
            GPU_GL_VALIDATE(glAttachShader(
                native->m_Program,
                static_cast<OpenGLGpuShader*>(args.GeometryShader)->m_Resource
            ));
        }

        if (args.HullShader != nullptr)
        {
            GPU_GL_VALIDATE(glAttachShader(
                native->m_Program,
                static_cast<OpenGLGpuShader*>(args.HullShader)->m_Resource
            ));
        }

        if (args.DomainShader != nullptr)
        {
            GPU_GL_VALIDATE(glAttachShader(
                native->m_Program,
                static_cast<OpenGLGpuShader*>(args.DomainShader)->m_Resource
            ));
        }

        GPU_GL_VALIDATE(glLinkProgram(
            native->m_Program
        ));

        GLint link_status = 0;

        GPU_GL_VALIDATE(glGetProgramiv(
            native->m_Program,
            GL_LINK_STATUS,
            &link_status
        ));

        {
            GPU_GL_VALIDATE(glGetProgramiv(
                native->m_Program,
                GL_VALIDATE_STATUS,
                &link_status
            ));
            
            GLint maxLength = 0;

            GPU_GL_VALIDATE(glGetProgramiv(
                native->m_Program,
                GL_INFO_LOG_LENGTH,
                &maxLength
            ));

            if (maxLength != 0)
            {
                std::vector<char> errorLog(static_cast<size_t>(maxLength));

                GPU_GL_VALIDATE(glGetProgramInfoLog(
                    native->m_Program,
                    maxLength,
                    &maxLength,
                    &errorLog[0]
                ));

                std::string log;

                for (size_t i = 0; i < errorLog.size(); i++)
                {
                    log += errorLog[i];
                }

                GX_LOG(LogOpenGLRender, Trace, "{}\n", log);
            }
        }

        //
        // Create rasterizer state.
        //
        native->m_RasterizerState.FillMode = OpenGLGpuTypeMapping::FillMode(args.RasterizerState.FillMode);
        native->m_RasterizerState.CullMode = OpenGLGpuTypeMapping::CullMode(args.RasterizerState.CullMode);
        native->m_RasterizerState.CullEnable = (args.RasterizerState.CullMode == GpuCullMode::None) ? GL_FALSE : GL_TRUE;
        //uint32_t ForcedSampleCount;
        native->m_RasterizerState.DepthBias = static_cast<GLint>(args.RasterizerState.DepthBias);
        native->m_RasterizerState.DepthBiasClamp = static_cast<GLfloat>(args.RasterizerState.DepthBiasClamp);
        native->m_RasterizerState.SlopeScaleDepthBias = static_cast<GLfloat>(args.RasterizerState.SlopeScaledDepthBias);
        native->m_RasterizerState.DepthClipEnable = static_cast<GLboolean>(args.RasterizerState.DepthClipEnable);
        native->m_RasterizerState.ScissorEnable = static_cast<GLboolean>(args.RasterizerState.ScissorEnable);
        native->m_RasterizerState.MultisampleEnable = static_cast<GLboolean>(args.RasterizerState.MultisampleEnable);
        native->m_RasterizerState.AntialiasedLineEnable = static_cast<GLboolean>(args.RasterizerState.AntialiasedLineEnable);
        native->m_RasterizerState.FrontCounterClockwise = static_cast<GLboolean>(args.RasterizerState.FrontCounterClockwise);
        native->m_RasterizerState.ConservativeRasterizationMode = static_cast<GLboolean>(args.RasterizerState.ConservativeRasterizationMode);


        //
        // Create blend state.
        //

        native->m_BlendState.AlphaToCoverage = static_cast<GLboolean>(args.BlendState.AlphaToCoverage);
        native->m_BlendState.IndependentBlendEnable = static_cast<GLboolean>(args.BlendState.IndependentBlend);
        native->m_BlendState.SampleMask = static_cast<GLuint>(args.BlendState.SampleMask);

        native->m_BlendState.BlendFactors[0] = static_cast<GLfloat>(args.BlendState.BlendFactors.X);
        native->m_BlendState.BlendFactors[1] = static_cast<GLfloat>(args.BlendState.BlendFactors.Y);
        native->m_BlendState.BlendFactors[2] = static_cast<GLfloat>(args.BlendState.BlendFactors.Z);
        native->m_BlendState.BlendFactors[3] = static_cast<GLfloat>(args.BlendState.BlendFactors.W);

        for (size_t i = 0; i < std::size(args.BlendState.RenderTarget); ++i)
        {
            auto& target_rt = native->m_BlendState.RenderTarget[i];
            auto& source_rt = args.BlendState.RenderTarget[i];

            if (source_rt.BlendEnable)
            {
                target_rt.Enable = GL_TRUE;
                target_rt.SourceBlendColor = OpenGLGpuTypeMapping::BlendType(source_rt.SourceBlendColor);
                target_rt.DestinationBlendColor = OpenGLGpuTypeMapping::BlendType(source_rt.DestinationBlendColor);
                target_rt.BlendOperationColor = OpenGLGpuTypeMapping::BlendOperation(source_rt.BlendOperationColor);
                target_rt.SourceBlendAlpha = OpenGLGpuTypeMapping::BlendType(source_rt.SourceBlendAlpha);
                target_rt.DestinationBlendAlpha = OpenGLGpuTypeMapping::BlendType(source_rt.DestinationBlendAlpha);
                target_rt.BlendOperationAlpha = OpenGLGpuTypeMapping::BlendOperation(source_rt.BlendOperationAlpha);

                target_rt.WriteMaskR = static_cast<GLboolean>(Flags::Has(source_rt.RenderTargetWriteMask, GpuColorWriteEnable::Red));
                target_rt.WriteMaskG = static_cast<GLboolean>(Flags::Has(source_rt.RenderTargetWriteMask, GpuColorWriteEnable::Green));
                target_rt.WriteMaskB = static_cast<GLboolean>(Flags::Has(source_rt.RenderTargetWriteMask, GpuColorWriteEnable::Blue));
                target_rt.WriteMaskA = static_cast<GLboolean>(Flags::Has(source_rt.RenderTargetWriteMask, GpuColorWriteEnable::Alpha));
            }
            else
            {
                target_rt.Enable = GL_FALSE;
            }
        }


        //
        // Create depth stencil state.
        //

        native->m_DepthStencilState.DepthWriteMask = OpenGLGpuTypeMapping::DepthWriteMask(args.DepthStencilState.DepthWriteMask);
        native->m_DepthStencilState.DepthFunction = OpenGLGpuTypeMapping::ComparizonFunction(args.DepthStencilState.DepthCompare);

        native->m_DepthStencilState.FrontFace.Fail = OpenGLGpuTypeMapping::StencilOperation(args.DepthStencilState.FrontFace.Fail);
        native->m_DepthStencilState.FrontFace.DepthFail = OpenGLGpuTypeMapping::StencilOperation(args.DepthStencilState.FrontFace.DepthFail);
        native->m_DepthStencilState.FrontFace.Pass = OpenGLGpuTypeMapping::StencilOperation(args.DepthStencilState.FrontFace.Pass);
        native->m_DepthStencilState.FrontFace.Comparizon = OpenGLGpuTypeMapping::ComparizonFunction(args.DepthStencilState.FrontFace.Compare);

        native->m_DepthStencilState.BackFace.Fail = OpenGLGpuTypeMapping::StencilOperation(args.DepthStencilState.BackFace.Fail);
        native->m_DepthStencilState.BackFace.DepthFail = OpenGLGpuTypeMapping::StencilOperation(args.DepthStencilState.BackFace.DepthFail);
        native->m_DepthStencilState.BackFace.Pass = OpenGLGpuTypeMapping::StencilOperation(args.DepthStencilState.BackFace.Pass);
        native->m_DepthStencilState.BackFace.Comparizon = OpenGLGpuTypeMapping::ComparizonFunction(args.DepthStencilState.BackFace.Compare);

        native->m_DepthStencilState.StencilReadMask = static_cast<GLubyte>(args.DepthStencilState.StencilReadMask);
        native->m_DepthStencilState.StencilWriteMask = static_cast<GLubyte>(args.DepthStencilState.StencilWriteMask);
        native->m_DepthStencilState.DepthEnable = static_cast<GLboolean>(args.DepthStencilState.DepthEnable);
        native->m_DepthStencilState.StencilEnable = static_cast<GLboolean>(args.DepthStencilState.StencilEnable);
        native->m_DepthStencilState.DepthBoundsTestEnable = static_cast<GLboolean>(args.DepthStencilState.DepthBoundsTestEnable);

        (void)layout;
        return native;
    }

    void OpenGLGpuDevice::DestroyGraphicsPipelineState(
        GpuGraphicsPipelineStateHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<OpenGLGpuGraphicsPipelineState*>(handle);

        GPU_GL_VALIDATE(glDeleteProgram(
            native->m_Program
        ));

        GPU_GL_VALIDATE(glDeleteVertexArrays(
            1,
            &native->m_VertexArrayObject
        ));

        delete native;
    }
}
