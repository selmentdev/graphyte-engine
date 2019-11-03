#pragma once
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuDevice final : public GpuDevice
    {
    private:
        GpuCommandListHandle m_ImmediateCommandList;

    public:
        NullGpuDevice() noexcept;
        virtual ~NullGpuDevice() noexcept;

    public:
        virtual void Tick(
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
        ) noexcept override;

        virtual void DestroyShader(
            GpuShaderHandle handle
        ) noexcept override;


        //
        // Command list.
        //
    public:
        virtual GpuCommandListHandle GetIntermediateCommandList() const noexcept override;

        virtual GpuCommandListHandle CreateCommandList() noexcept override;

        virtual void DestroyCommandList(
            GpuCommandListHandle handle
        ) noexcept override;

        virtual void PlayCommandList(
            GpuCommandListHandle handle
        ) const noexcept override;


        //
        // Viewport
        //
    public:
        virtual GpuViewportHandle CreateViewport(
            void* native_handle,
            uint32_t width,
            uint32_t height,
            bool fullscreen,
            PixelFormat color_format,
            PixelFormat depth_format,
            GpuMsaaQuality msaa
        ) noexcept override;

        virtual void DestroyViewport(
            GpuViewportHandle handle
        ) noexcept override;

        virtual void ResizeViewport(
            GpuViewportHandle handle,
            uint32_t width,
            uint32_t height,
            bool fullscreen,
            PixelFormat format
        ) noexcept override;

        virtual void BeginDrawViewport(
            GpuViewportHandle handle
        ) noexcept override;

        virtual void EndDrawViewport(
            GpuViewportHandle handle,
            bool present,
            int interval
        ) noexcept override;


        //
        // Render Target.
        //
    public:
        virtual GpuRenderTargetHandle BeginCreateRenderTarget(
            uint32_t width,
            uint32_t height,
            uint32_t surfaces
        ) noexcept override;

        virtual void EndCreateRenderTarget(
            GpuRenderTargetHandle handle
        ) noexcept override;

        virtual void SetRenderTargetSurface(
            GpuRenderTargetHandle handle,
            int32_t index,
            GpuTexture2DHandle texture,
            uint32_t mip_index
        ) noexcept override;

        virtual void DestroyRenderTarget(
            GpuRenderTargetHandle handle
        ) noexcept override;

        // virtual void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTexture2DArrayHandle texture, uint32_t array_index, uint32_t mip_index) noexcept override;
        // virtual void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTexture3DHandle texture, uint32_t slice_index, uint32_t mip_index) noexcept override;
        // virtual void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTextureCube texture, GpuCubeFace cube_face, uint32_t mip_index) noexcept override;


        //
        // Graphics Pipeline.
        //
    public:
        virtual GpuGraphicsPipelineStateHandle CreateGraphicsPipelineState(
            const GpuGraphicsPipelineStateCreateArgs& args,
            const GpuResourceSetDesc& layout
        ) noexcept override;

        virtual void DestroyGraphicsPipelineState(
            GpuGraphicsPipelineStateHandle handle
        ) noexcept override;


        //
        // Compute Pipeline.
        //
    public:
        virtual GpuComputePipelineStateHandle CreateComputePipelineState(
            const GpuComputePipelineStateCreateArgs& args,
            const GpuResourceSetDesc& layout
        ) noexcept override;

        virtual void DestroyComputePipelineState(
            GpuComputePipelineStateHandle handle
        ) noexcept override;


        //
        // Sampler.
        //
    public:
        virtual GpuSamplerHandle CreateSampler(
            const GpuSamplerCreateArgs& args
        ) noexcept override;

        virtual void DestroySampler(
            GpuSamplerHandle handle
        ) noexcept override;


        //
        // Texture 2D
        //
    public:
        virtual GpuTexture2DHandle CreateTexture2D(
            const GpuTextureCreateArgs& args
        ) noexcept override;

        virtual void DestroyTexture2D(
            GpuTexture2DHandle texture
        ) noexcept override;

        virtual void UpdateTexture2D(
            GpuTexture2DHandle texture,
            uint32_t mip_level,
            const GpuRect* rect,
            const void* data,
            uint32_t pitch
        ) noexcept override;

        virtual void GenerateMipmapsTexture2D(
            GpuTexture2DHandle texture
        ) noexcept override;

        virtual std::unique_ptr<Image> SaveTexture2D(
            GpuTexture2DHandle texture
        ) noexcept override;


        //
        // Texture 2D Array.
        //
    public:
        virtual GpuTexture2DArrayHandle CreateTexture2DArray(
            const GpuTextureCreateArgs& args
        ) noexcept override;

        virtual void DestroyTexture2DArray(
            GpuTexture2DArrayHandle handle
        ) noexcept override;


        //
        // Texture 3D.
        //
    public:
        virtual GpuTexture3DHandle CreateTexture3D(
            const GpuTextureCreateArgs& args
        ) noexcept override;

        virtual void DestroyTexture3D(
            GpuTexture3DHandle handle
        ) noexcept override;


        //
        // Texture Cube.
        //
    public:
        virtual GpuTextureCubeHandle CreateTextureCube(
            const GpuTextureCreateArgs& args
        ) noexcept override;

        virtual void DestroyTextureCube(
            GpuTextureCubeHandle handle
        ) noexcept override;


        //
        // Uniform buffer.
        //
    public:
        virtual GpuUniformBufferHandle CreateUniformBuffer(
            size_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept override;

        virtual void DestroyUniformBuffer(
            GpuUniformBufferHandle handle
        ) noexcept override;

        virtual void* LockUniformBuffer(
            GpuUniformBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept override;

        virtual void UnlockUniformBuffer(
            GpuUniformBufferHandle handle
        ) noexcept override;

        virtual void CopyUniformBuffer(
            GpuUniformBufferHandle source,
            GpuUniformBufferHandle destination
        ) noexcept override;


        //
        // Vertex buffer.
        //
    public:
        virtual GpuVertexBufferHandle CreateVertexBuffer(
            uint32_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept override;

        virtual void DestroyVertexBuffer(
            GpuVertexBufferHandle handle
        ) noexcept override;

        virtual void* LockVertexBuffer(
            GpuVertexBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept override;

        virtual void UnlockVertexBuffer(
            GpuVertexBufferHandle handle
        ) noexcept override;

        virtual void CopyVertexBuffer(
            GpuVertexBufferHandle source,
            GpuVertexBufferHandle destination
        ) noexcept override;


        //
        // Index buffer.
        //
    public:
        virtual GpuIndexBufferHandle CreateIndexBuffer(
            uint32_t stride,
            uint32_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept override;

        virtual void DestroyIndexBuffer(
            GpuIndexBufferHandle handle
        ) noexcept override;

        virtual void* LockIndexBuffer(
            GpuIndexBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept override;

        virtual void UnlockIndexBuffer(
            GpuIndexBufferHandle handle
        ) noexcept override;

        virtual void CopyIndexBuffer(
            GpuIndexBufferHandle source,
            GpuIndexBufferHandle destination
        ) noexcept override;


        //
        // Resource set.
        //
    public:
        virtual GpuResourceSetHandle CreateResourceSet(
            const GpuResourceSetDesc& desc
        ) noexcept override;

        virtual void DestroyResourceSet(
            GpuResourceSetHandle handle
        ) noexcept override;

        virtual void UpdateResourceSet(
            GpuResourceSetHandle handle,
            const GpuResourceSetDesc& desc
        ) noexcept override;


        //
        // Occlusion query.
        //
    public:
        virtual GpuOcclusionQueryHandle CreateOcclusionQuery() noexcept final
        {
            return nullptr;
        }

        virtual void DestroyOcclusionQuery(
            GpuOcclusionQueryHandle handle
        ) noexcept final
        {
            (void)handle;
        }

    public:
        void FlushLogs() noexcept;
    };
}
