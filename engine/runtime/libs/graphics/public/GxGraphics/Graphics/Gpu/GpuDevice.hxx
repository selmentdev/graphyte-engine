#pragma once
#include <GxGraphics/Graphics.module.hxx>
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include <GxGraphics/Graphics/Image.hxx>

namespace Graphyte::Graphics
{
    using GpuDeviceRef = class GpuDevice*;
    class GRAPHICS_API GpuDevice
    {
    public:
        GpuDevice() noexcept;
        virtual ~GpuDevice() noexcept;

    public:
        virtual void Tick(
            float time
        ) noexcept;

        //
        // Shader.
        //
    public:
        virtual GpuShaderHandle CreateShader(
            GpuShaderStage stage,
            GpuShaderBytecode bytecode,
            GpuInputLayout inputLayout
        ) noexcept = 0;

        virtual void DestroyShader(
            GpuShaderHandle handle
        ) noexcept = 0;


        //
        // Command list.
        //
    public:
        virtual GpuCommandListHandle GetIntermediateCommandList() const noexcept = 0;

        virtual GpuCommandListHandle CreateCommandList() noexcept = 0;

        virtual void DestroyCommandList(
            GpuCommandListHandle handle
        ) noexcept = 0;

        virtual void PlayCommandList(
            GpuCommandListHandle handle
        ) const noexcept = 0;


        //
        // Viewport.
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
        ) noexcept = 0;

        virtual void DestroyViewport(
            GpuViewportHandle handle
        ) noexcept = 0;

        virtual void ResizeViewport(
            GpuViewportHandle handle,
            uint32_t width,
            uint32_t height,
            bool fullscreen,
            PixelFormat format
        ) noexcept = 0;

        virtual void BeginDrawViewport(
            GpuViewportHandle handle
        ) noexcept = 0;

        virtual void EndDrawViewport(
            GpuViewportHandle handle,
            bool present,
            int interval
        ) noexcept = 0;


        //
        // Render Target.
        //
    public:
        virtual GpuRenderTargetHandle BeginCreateRenderTarget(
            uint32_t width,
            uint32_t height,
            uint32_t surfaces
        ) noexcept = 0;

        virtual void EndCreateRenderTarget(
            GpuRenderTargetHandle handle
        ) noexcept = 0;

        virtual void SetRenderTargetSurface(
            GpuRenderTargetHandle handle,
            int32_t index,
            GpuTexture2DHandle texture,
            uint32_t mip_index
        ) noexcept = 0;

        virtual void DestroyRenderTarget(
            GpuRenderTargetHandle handle
        ) noexcept = 0;

        //virtual void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTexture2DArrayHandle texture, uint32_t array_index, uint32_t mip_index) noexcept = 0;
        //virtual void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTexture3DHandle texture, uint32_t slice_index, uint32_t mip_index) noexcept = 0;
        //virtual void SetRenderTargetSurface(GpuRenderTargetHandle handle, int32_t index, GpuTextureCube texture, GpuCubeFace cube_face, uint32_t mip_index) noexcept = 0;

        //
        // Graphics Pipeline.
        //
    public:
        virtual GpuGraphicsPipelineStateHandle CreateGraphicsPipelineState(
            const GpuGraphicsPipelineStateCreateArgs& args,
            const GpuResourceSetDesc& layout
        ) noexcept = 0;

        virtual void DestroyGraphicsPipelineState(
            GpuGraphicsPipelineStateHandle handle
        ) noexcept = 0;


        //
        // Compute Pipeline.
        //
    public:
        virtual GpuComputePipelineStateHandle CreateComputePipelineState(
            const GpuComputePipelineStateCreateArgs& args,
            const GpuResourceSetDesc& layout
        ) noexcept = 0;

        virtual void DestroyComputePipelineState(
            GpuComputePipelineStateHandle handle
        ) noexcept = 0;


        //
        // Sampler.
        //
    public:
        virtual GpuSamplerHandle CreateSampler(
            const GpuSamplerCreateArgs& args
        ) noexcept = 0;

        virtual void DestroySampler(
            GpuSamplerHandle handle
        ) noexcept = 0;


        //
        // Texture 2D
        //
    public:
        virtual GpuTexture2DHandle CreateTexture2D(
            const GpuTextureCreateArgs& args
        ) noexcept = 0;

        virtual void DestroyTexture2D(
            GpuTexture2DHandle texture
        ) noexcept = 0;

        virtual void UpdateTexture2D(
            GpuTexture2DHandle texture,
            uint32_t mip_level,
            const GpuRect* rect,
            const void* data,
            uint32_t pitch
        ) noexcept = 0;

        virtual void GenerateMipmapsTexture2D(
            GpuTexture2DHandle texture
        ) noexcept = 0;

        virtual std::unique_ptr<Image> SaveTexture2D(
            GpuTexture2DHandle texture
        ) noexcept = 0;


        //
        // Texture 2D Array.
        //
    public:
        virtual GpuTexture2DArrayHandle CreateTexture2DArray(
            const GpuTextureCreateArgs& args
        ) noexcept = 0;

        virtual void DestroyTexture2DArray(
            GpuTexture2DArrayHandle handle
        ) noexcept = 0;


        //
        // Texture 3D.
        //
    public:
        virtual GpuTexture3DHandle CreateTexture3D(
            const GpuTextureCreateArgs& args
        ) noexcept = 0;

        virtual void DestroyTexture3D(
            GpuTexture3DHandle handle
        ) noexcept = 0;


        //
        // Texture Cube.
        //
    public:
        virtual GpuTextureCubeHandle CreateTextureCube(
            const GpuTextureCreateArgs& args
        ) noexcept = 0;

        virtual void DestroyTextureCube(
            GpuTextureCubeHandle handle
        ) noexcept = 0;


        //
        // Uniform buffer.
        //
    public:
        virtual GpuUniformBufferHandle CreateUniformBuffer(
            size_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept = 0;

        virtual void DestroyUniformBuffer(
            GpuUniformBufferHandle handle
        ) noexcept = 0;

        virtual void* LockUniformBuffer(
            GpuUniformBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept = 0;

        virtual void UnlockUniformBuffer(
            GpuUniformBufferHandle handle
        ) noexcept = 0;

        virtual void CopyUniformBuffer(
            GpuUniformBufferHandle source,
            GpuUniformBufferHandle destination
        ) noexcept = 0;

        //
        // Vertex buffer.
        //
    public:
        virtual GpuVertexBufferHandle CreateVertexBuffer(
            uint32_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept = 0;

        virtual void DestroyVertexBuffer(
            GpuVertexBufferHandle handle
        ) noexcept = 0;

        virtual void* LockVertexBuffer(
            GpuVertexBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept = 0;

        virtual void UnlockVertexBuffer(
            GpuVertexBufferHandle handle
        ) noexcept = 0;

        virtual void CopyVertexBuffer(
            GpuVertexBufferHandle source,
            GpuVertexBufferHandle destination
        ) noexcept = 0;


        //
        // Index buffer.
        //
    public:
        virtual GpuIndexBufferHandle CreateIndexBuffer(
            uint32_t stride,
            uint32_t size,
            GpuBufferUsage usage,
            const GpuSubresourceData* subresource
        ) noexcept = 0;

        virtual void DestroyIndexBuffer(
            GpuIndexBufferHandle handle
        ) noexcept = 0;

        virtual void* LockIndexBuffer(
            GpuIndexBufferHandle handle,
            uint32_t offset,
            uint32_t size,
            GpuResourceLockMode lock_mode
        ) noexcept = 0;

        virtual void UnlockIndexBuffer(
            GpuIndexBufferHandle handle
        ) noexcept = 0;

        virtual void CopyIndexBuffer(
            GpuIndexBufferHandle source,
            GpuIndexBufferHandle destination
        ) noexcept = 0;


        //
        // Resource set.
        //
    public:
        virtual GpuResourceSetHandle CreateResourceSet(
            const GpuResourceSetDesc& desc
        ) noexcept = 0;

        virtual void DestroyResourceSet(
            GpuResourceSetHandle handle
        ) noexcept = 0;

        virtual void UpdateResourceSet(
            GpuResourceSetHandle handle,
            const GpuResourceSetDesc& desc
        ) noexcept = 0;


        //
        // Occlusion query.
        //
    public:
        virtual GpuOcclusionQueryHandle CreateOcclusionQuery() noexcept = 0;

        virtual void DestroyOcclusionQuery(
            GpuOcclusionQueryHandle handle
        ) noexcept = 0;
    };
}

namespace Graphyte
{
    extern GRAPHICS_API std::unique_ptr<Graphics::GpuDevice> GRenderDevice;
}
