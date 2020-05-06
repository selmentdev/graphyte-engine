#pragma once
#include <GxGraphics/Graphics/Gpu/GpuDevice.hxx>
#include "OpenGLGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuDevice final : public GpuDevice
    {
    public:
#if GRAPHYTE_PLATFORM_WINDOWS
        HGLRC m_InitialContext;
        HWND m_InitialWindow;
#endif

        GpuCommandListHandle m_CommandList;

    public:
        static void APIENTRY DebugMessageCallback(
            GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* context
        ) noexcept;

    public:
        OpenGLGpuDevice() noexcept;
        virtual ~OpenGLGpuDevice() noexcept;

    public:
        void Tick(
            float time
        ) noexcept override;

        //
        // Shader.
        //
    public:
        virtual GpuShaderHandle CreateShader(
            GpuShaderStage stage,
            GpuShaderBytecode bytecode,
            GpuInputLayout inputLayout
        ) noexcept final;

        virtual void DestroyShader(
            GpuShaderHandle handle
        ) noexcept final;


        //
        // Command list.
        //
    public:
        GpuCommandListHandle GetIntermediateCommandList() const noexcept final;

        GpuCommandListHandle CreateCommandList() noexcept final;

        void DestroyCommandList(
            GpuCommandListHandle handle
        ) noexcept final;

        void PlayCommandList(
            GpuCommandListHandle handle
        ) const noexcept final;


        //
        // Viewport
        //
    public:
        GpuViewportHandle CreateViewport(
            void* native_handle,
            uint32_t width,
            uint32_t height,
            bool fullscreen,
            PixelFormat color_format,
            PixelFormat depth_format,
            GpuMsaaQuality msaa
        ) noexcept final;

        void DestroyViewport(
            GpuViewportHandle handle
        ) noexcept final;

        void ResizeViewport(
            GpuViewportHandle handle,
            uint32_t width,
            uint32_t height,
            bool fullscreen,
            PixelFormat format
        ) noexcept final;

        void BeginDrawViewport(
            GpuViewportHandle handle
        ) noexcept final;

        void EndDrawViewport(
            GpuViewportHandle handle,
            bool present,
            int interval
        ) noexcept final;


        //
        // Render Target.
        //
    public:
        GpuRenderTargetHandle BeginCreateRenderTarget(
            uint32_t width,
            uint32_t height,
            uint32_t surfaces
        ) noexcept final;

        void EndCreateRenderTarget(
            GpuRenderTargetHandle handle
        ) noexcept final;

        void SetRenderTargetSurface(
            GpuRenderTargetHandle handle,
            int32_t index,
            GpuTexture2DHandle texture,
            uint32_t mip_index
        ) noexcept final;

        void DestroyRenderTarget(
            GpuRenderTargetHandle handle
        ) noexcept final;

        // void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTexture2DArrayHandle texture, uint32_t array_index, uint32_t mip_index) noexcept final;
        // void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTexture3DHandle texture, uint32_t slice_index, uint32_t mip_index) noexcept final;
        // void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTextureCube texture, GpuCubeFace cube_face, uint32_t mip_index) noexcept final;


        //
        // Graphics Pipeline.
        //
    public:
        GpuGraphicsPipelineStateHandle CreateGraphicsPipelineState(
            const GpuGraphicsPipelineStateCreateArgs& args,
            const GpuResourceSetDesc& layout
        ) noexcept final;

        void DestroyGraphicsPipelineState(
            GpuGraphicsPipelineStateHandle handle
        ) noexcept final;


        //
        // Compute Pipeline.
        //
    public:
        GpuComputePipelineStateHandle CreateComputePipelineState(
            const GpuComputePipelineStateCreateArgs& args,
            const GpuResourceSetDesc& layout
        ) noexcept final;

        void DestroyComputePipelineState(
            GpuComputePipelineStateHandle handle
        ) noexcept final;


        //
        // Sampler.
        //
    public:
        GpuSamplerHandle CreateSampler(
            const GpuSamplerCreateArgs& args
        ) noexcept final;

        void DestroySampler(
            GpuSamplerHandle handle
        ) noexcept final;


        //
        // Texture 2D
        //
    public:
        GpuTexture2DHandle CreateTexture2D(
            const GpuTextureCreateArgs& args
        ) noexcept final;

        void DestroyTexture2D(
            GpuTexture2DHandle handle
        ) noexcept final;

        void UpdateTexture2D(
            GpuTexture2DHandle handle,
            uint32_t mip_level,
            const GpuRect* rect,
            const void* data,
            uint32_t pitch
        ) noexcept final;

        void GenerateMipmapsTexture2D(
            GpuTexture2DHandle handle
        ) noexcept final;

        std::unique_ptr<Image> SaveTexture2D(
            GpuTexture2DHandle handle
        ) noexcept final;


        //
        // Texture 2D Array.
        //
    public:
        GpuTexture2DArrayHandle CreateTexture2DArray(
            const GpuTextureCreateArgs& args
        ) noexcept final;

        void DestroyTexture2DArray(
            GpuTexture2DArrayHandle handle
        ) noexcept final;


        //
        // Texture 3D.
        //
    public:
        GpuTexture3DHandle CreateTexture3D(
            const GpuTextureCreateArgs& args
        ) noexcept final;

        void DestroyTexture3D(
            GpuTexture3DHandle handle
        ) noexcept final;


        //
        // Texture Cube.
        //
    public:
        GpuTextureCubeHandle CreateTextureCube(
            const GpuTextureCreateArgs& args
        ) noexcept final;

        void DestroyTextureCube(
            GpuTextureCubeHandle handle
        ) noexcept final;


        //
        // Uniform buffer.
        //
    public:
        GpuUniformBufferHandle CreateUniformBuffer(
            size_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept final;

        void DestroyUniformBuffer(
            GpuUniformBufferHandle handle
        ) noexcept final;

        void* LockUniformBuffer(
            GpuUniformBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept final;

        void UnlockUniformBuffer(
            GpuUniformBufferHandle handle
        ) noexcept final;

        void CopyUniformBuffer(
            GpuUniformBufferHandle source,
            GpuUniformBufferHandle destination
        ) noexcept final;

        //
        // Vertex buffer.
        //
    public:
        GpuVertexBufferHandle CreateVertexBuffer(
            uint32_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept final;

        void DestroyVertexBuffer(
            GpuVertexBufferHandle handle
        ) noexcept final;

        void* LockVertexBuffer(
            GpuVertexBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept final;

        void UnlockVertexBuffer(
            GpuVertexBufferHandle handle
        ) noexcept final;

        void CopyVertexBuffer(
            GpuVertexBufferHandle source,
            GpuVertexBufferHandle destination
        ) noexcept final;


        //
        // Index buffer.
        //
    public:
        GpuIndexBufferHandle CreateIndexBuffer(
            uint32_t stride,
            uint32_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept final;

        void DestroyIndexBuffer(
            GpuIndexBufferHandle handle
        ) noexcept final;

        void* LockIndexBuffer(
            GpuIndexBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept final;

        void UnlockIndexBuffer(
            GpuIndexBufferHandle handle
        ) noexcept final;

        void CopyIndexBuffer(
            GpuIndexBufferHandle source,
            GpuIndexBufferHandle destination
        ) noexcept final;


        //
        // Resource set.
        //
    public:
        GpuResourceSetHandle CreateResourceSet(
            const GpuResourceSetDesc& desc
        ) noexcept final;

        void DestroyResourceSet(
            GpuResourceSetHandle handle
        ) noexcept final;

        void UpdateResourceSet(
            GpuResourceSetHandle handle,
            const GpuResourceSetDesc& desc
        ) noexcept final;


        //
        // Occlusion query.
        //
    public:
        GpuOcclusionQueryHandle CreateOcclusionQuery() noexcept final;

        void DestroyOcclusionQuery(
            GpuOcclusionQueryHandle handle
        ) noexcept final;

    public:
        void FlushLogs() noexcept;
    };
}
