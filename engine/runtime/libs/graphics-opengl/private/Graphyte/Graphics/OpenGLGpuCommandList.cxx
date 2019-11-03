#include "Graphics.GLCore.pch.hxx"
#include "OpenGLGpuCommandList.hxx"
#include "OpenGLGpuDevice.hxx"
#include "OpenGLGpuRenderTarget.hxx"
#include "OpenGLGpuGraphicsPipelineState.hxx"
#include "OpenGLGpuVertexBuffer.hxx"
#include "OpenGLGpuIndexBuffer.hxx"
#include "OpenGLGpuSampler.hxx"
#include "OpenGLGpuUniformBuffer.hxx"
#include "OpenGLGpuTexture.hxx"
#include "OpenGLGpuResourceSet.hxx"
#include "OpenGLGpuRenderTarget.hxx"

namespace Graphyte::Graphics
{
    GpuCommandListHandle OpenGLGpuDevice::GetIntermediateCommandList() const noexcept
    {
        return m_CommandList;
    }

    GpuCommandListHandle OpenGLGpuDevice::CreateCommandList() noexcept
    {
        return m_CommandList;
    }

    void OpenGLGpuDevice::DestroyCommandList(GpuCommandListHandle handle) noexcept
    {
        (void)handle;
    }

    void OpenGLGpuDevice::PlayCommandList(GpuCommandListHandle handle) const noexcept
    {
        (void)handle;
    }
}

namespace Graphyte::Graphics
{
    void OpenGLGpuCommandList::BindRenderTarget(
        GpuRenderTargetHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<OpenGLGpuRenderTarget*>(handle);

        GPU_GL_VALIDATE(glBindFramebuffer(
            GL_FRAMEBUFFER,
            native->m_Framebuffer
        ));
    }

    void OpenGLGpuCommandList::BindGraphicsPipelineState(
        GpuGraphicsPipelineStateHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<OpenGLGpuGraphicsPipelineState*>(handle);

        m_CurrentVAO = native->m_VertexArrayObject;

        GPU_GL_VALIDATE(glBindVertexArray(
            native->m_VertexArrayObject
        ));

        GPU_GL_VALIDATE(glUseProgram(
            native->m_Program
        ));


        //
        // Rasterizer state.
        //

        if (native->m_RasterizerState.CullEnable != GL_FALSE)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_CULL_FACE
            ));

            GPU_GL_VALIDATE(glCullFace(
                native->m_RasterizerState.CullMode
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_CULL_FACE
            ));
        }
        
        GPU_GL_VALIDATE(glPolygonMode(
            GL_FRONT_AND_BACK,
            native->m_RasterizerState.FillMode
        ));

        GPU_GL_VALIDATE(glPolygonOffsetClamp(
            static_cast<GLfloat>(native->m_RasterizerState.DepthBias),
            native->m_RasterizerState.SlopeScaleDepthBias,
            native->m_RasterizerState.DepthBiasClamp
        ));


        if (native->m_RasterizerState.DepthClipEnable != GL_FALSE)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_DEPTH_CLAMP
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_DEPTH_CLAMP
            ));
        }

        if (native->m_RasterizerState.ScissorEnable != GL_FALSE)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_SCISSOR_TEST
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_SCISSOR_TEST
            ));
        }
        
        if (native->m_RasterizerState.MultisampleEnable != GL_FALSE)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_MULTISAMPLE
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_MULTISAMPLE
            ));
        }

        if (native->m_RasterizerState.AntialiasedLineEnable != GL_FALSE)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_LINE_SMOOTH
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_LINE_SMOOTH
            ));
        }

        GPU_GL_VALIDATE(glFrontFace(
            (native->m_RasterizerState.FrontCounterClockwise != GL_FALSE)
                ? GL_CCW
                : GL_CW
        ));

        if (GLAD_GL_NV_conservative_raster)
        {
            if (native->m_RasterizerState.ConservativeRasterizationMode != GL_FALSE)
            {
                GPU_GL_VALIDATE(glEnable(
                    GL_CONSERVATIVE_RASTERIZATION_NV
                ));
            }
            else
            {
                GPU_GL_VALIDATE(glDisable(
                    GL_CONSERVATIVE_RASTERIZATION_NV
                ));
            }
        }


        //
        // Blend state.
        //

        if (native->m_BlendState.AlphaToCoverage)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_SAMPLE_ALPHA_TO_COVERAGE
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_SAMPLE_ALPHA_TO_COVERAGE
            ));
        }

        bool const independent = (native->m_BlendState.IndependentBlendEnable != GL_FALSE);

        for (size_t i = 0; i < std::size(native->m_BlendState.RenderTarget); ++i)
        {
            auto const index = static_cast<GLuint>(i);
            bool const enable = (native->m_BlendState.RenderTarget[i].Enable != GL_FALSE);
            bool const first = (i == 0);

            if (enable && (first || independent))
            {
                GPU_GL_VALIDATE(glEnablei(
                    GL_BLEND,
                    index
                ));

                GPU_GL_VALIDATE(glBlendFuncSeparatei(
                    index,
                    native->m_BlendState.RenderTarget[i].SourceBlendColor,
                    native->m_BlendState.RenderTarget[i].DestinationBlendColor,
                    native->m_BlendState.RenderTarget[i].SourceBlendAlpha,
                    native->m_BlendState.RenderTarget[i].DestinationBlendAlpha
                ));

                GPU_GL_VALIDATE(glBlendEquationSeparatei(
                    index,
                    native->m_BlendState.RenderTarget[i].BlendOperationColor,
                    native->m_BlendState.RenderTarget[i].BlendOperationAlpha
                ));

                GPU_GL_VALIDATE(glColorMaski(
                    index,
                    native->m_BlendState.RenderTarget[i].WriteMaskR,
                    native->m_BlendState.RenderTarget[i].WriteMaskG,
                    native->m_BlendState.RenderTarget[i].WriteMaskB,
                    native->m_BlendState.RenderTarget[i].WriteMaskA
                ));
            }
            else
            {
                GPU_GL_VALIDATE(glDisablei(
                    GL_BLEND,
                    index
                ));
            }
        }


        //
        // Depth stencil state.
        //

        if (native->m_DepthStencilState.DepthEnable != GL_FALSE)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_DEPTH_TEST
            ));

            GPU_GL_VALIDATE(glDepthMask(
                native->m_DepthStencilState.DepthWriteMask
            ));

            GPU_GL_VALIDATE(glDepthFunc(
                native->m_DepthStencilState.DepthFunction
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_DEPTH_TEST
            ));
        }

        if (native->m_DepthStencilState.StencilEnable != GL_FALSE)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_STENCIL_TEST
            ));

            GPU_GL_VALIDATE(glStencilFuncSeparate(
                GL_FRONT,
                native->m_DepthStencilState.FrontFace.Comparizon,
                0,
                static_cast<GLuint>(native->m_DepthStencilState.StencilReadMask)
            ));

            GPU_GL_VALIDATE(glStencilOpSeparate(
                GL_FRONT,
                native->m_DepthStencilState.FrontFace.Fail,
                native->m_DepthStencilState.FrontFace.DepthFail,
                native->m_DepthStencilState.FrontFace.Pass
            ));

            GPU_GL_VALIDATE(glStencilFuncSeparate(
                GL_BACK,
                native->m_DepthStencilState.BackFace.Comparizon,
                0,
                static_cast<GLuint>(native->m_DepthStencilState.StencilReadMask)
            ));

            GPU_GL_VALIDATE(glStencilOpSeparate(
                GL_BACK,
                native->m_DepthStencilState.BackFace.Fail,
                native->m_DepthStencilState.BackFace.DepthFail,
                native->m_DepthStencilState.BackFace.Pass
            ));

            GPU_GL_VALIDATE(glStencilMaskSeparate(
                GL_FRONT_AND_BACK,
                native->m_DepthStencilState.StencilWriteMask
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_STENCIL_TEST
            ));
        }

        if (native->m_DepthStencilState.DepthBoundsTestEnable != GL_FALSE)
        {
            GPU_GL_VALIDATE(glEnable(
                GL_DEPTH_BOUNDS_TEST_EXT
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glDisable(
                GL_DEPTH_BOUNDS_TEST_EXT
            ));
        }



        ////////////

        GPU_GL_VALIDATE(glActiveTexture(
            GL_TEXTURE0 + 0
        ));

        GPU_GL_VALIDATE(glActiveTexture(
            GL_TEXTURE0 + 1
        ));

        GPU_GL_VALIDATE(glActiveTexture(
            GL_TEXTURE0 + 2
        ));

        GPU_GL_VALIDATE(glActiveTexture(
            GL_TEXTURE0 + 3
        ));

    }

    void OpenGLGpuCommandList::BindVertexBuffer(
        GpuVertexBufferHandle handle,
        uint32_t slot,
        uint32_t stride,
        uint32_t offset
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<OpenGLGpuVertexBuffer*>(handle);
        
        GPU_GL_VALIDATE(glVertexArrayVertexBuffer(m_CurrentVAO,
            static_cast<GLuint>(slot),
            native->m_Resource,
            static_cast<GLintptr>(offset),
            static_cast<GLsizei>(stride)
        ));
    }

    void OpenGLGpuCommandList::BindIndexBuffer(
        GpuIndexBufferHandle handle,
        uint32_t offset,
        bool short_indices
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<OpenGLGpuIndexBuffer*>(handle);
        (void)offset;
        (void)short_indices;

        GPU_GL_VALIDATE(glVertexArrayElementBuffer(
            m_CurrentVAO,
            native->m_Resource
        ));

        //GPU_GL_VALIDATE(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, native->m_Resource));
    }

    void OpenGLGpuCommandList::Draw(
        uint32_t vertex_count,
        uint32_t start_vertex_location
    ) noexcept
    {
        GPU_GL_VALIDATE(glDrawArrays(
            GL_TRIANGLES,
            static_cast<GLsizei>(start_vertex_location),
            static_cast<GLsizei>(vertex_count)
        ));
    }
    
    void OpenGLGpuCommandList::DrawIndexed(
        uint32_t index_count,
        uint32_t start_index_location,
        int32_t base_vertex_location
    ) noexcept
    {
        // TODO: primitive topology and index size should be set based on currently bound pipeline state!
        GPU_GL_VALIDATE(glDrawElementsBaseVertex(
            GL_TRIANGLES,
            static_cast<GLsizei>(index_count),
            GL_UNSIGNED_SHORT,
            reinterpret_cast<const void*>(static_cast<uintptr_t>(start_index_location)),
            static_cast<GLint>(base_vertex_location)
        ));
    }

    void OpenGLGpuCommandList::DrawInstanced(
        uint32_t vertex_count_per_instance,
        uint32_t instance_count,
        uint32_t start_vertex_location,
        uint32_t start_instance_location
    ) noexcept
    {
        (void)vertex_count_per_instance;
        (void)instance_count;
        (void)start_vertex_location;
        (void)start_instance_location;
    }

    void OpenGLGpuCommandList::DrawIndexedInstanced(
        uint32_t index_count_per_instance,
        uint32_t instance_count,
        uint32_t start_index_location,
        int32_t base_vertex_location,
        uint32_t start_instance_location
    ) noexcept
    {
        // TODO: primitive topology and index size should be set based on currently bound pipeline state!
        GPU_GL_VALIDATE(glDrawElementsInstancedBaseVertexBaseInstance(
            GL_TRIANGLES,
            static_cast<GLsizei>(index_count_per_instance),
            GL_UNSIGNED_SHORT,
            reinterpret_cast<const void*>(static_cast<uintptr_t>(start_index_location)),
            static_cast<GLsizei>(instance_count),
            static_cast<GLint>(base_vertex_location),
            static_cast<GLuint>(start_instance_location)
        ));
    }

    void OpenGLGpuCommandList::DispatchCompute(
        uint32_t threadGroupCountX,
        uint32_t threadGroupCountY,
        uint32_t threadGroupCountZ
    ) noexcept
    {
        GPU_GL_VALIDATE(glDispatchCompute(
            threadGroupCountX,
            threadGroupCountY,
            threadGroupCountZ
        ));
    }
}
