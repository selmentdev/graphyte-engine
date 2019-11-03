#pragma once
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuDevice final : public GpuDevice
    {
    private:
        VKAPI_ATTR static VkBool32 VKAPI_CALL DebugCallback(
            VkDebugReportFlagsEXT flags,
            VkDebugReportObjectTypeEXT objType,
            uint64_t obj,
            size_t location,
            int32_t code,
            const char* layerPrefix,
            const char* msg,
            void* userData
        ) noexcept;
        
    public:
        GpuCommandListHandle m_CommandList;

        VkInstance m_Instance;
        VkDebugReportCallbackEXT m_DebugCallback;
        VkPhysicalDevice m_PhysicalDevice;
        VkDevice m_Device;
        VkQueue m_GraphicsQueue;
        VkQueue m_ComputeQueue;
        VkCommandPool m_CommandPool;
        VmaAllocator m_Allocator;

    public:
        VulkanGpuDevice() noexcept;
        virtual ~VulkanGpuDevice() noexcept;

    public:
        void Tick(
            float time
        ) noexcept final;


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
            GpuTexture2DHandle texture
        ) noexcept final;

        void UpdateTexture2D(
            GpuTexture2DHandle texture,
            uint32_t mip_level,
            const GpuRect* rect,
            const void* data,
            uint32_t pitch
        ) noexcept final;

        void GenerateMipmapsTexture2D(
            GpuTexture2DHandle texture
        ) noexcept final;

        std::unique_ptr<Image> SaveTexture2D(
            GpuTexture2DHandle texture
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
        GpuOcclusionQueryHandle CreateOcclusionQuery() noexcept final
        {
            return nullptr;
        }

        void DestroyOcclusionQuery(
            GpuOcclusionQueryHandle handle
        ) noexcept final
        {
            (void)handle;
        }


    public:
        void FlushLogs() noexcept;

    private:
        void InitializeD3D11() noexcept;

    public:
        VkCommandBuffer BeginCommandList() noexcept
        {
            VkCommandBufferAllocateInfo ci{};
            ci.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            ci.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            ci.commandPool = m_CommandPool;
            ci.commandBufferCount = 1;

            VkCommandBuffer commandBuffer{ VK_NULL_HANDLE };
            vkAllocateCommandBuffers(m_Device, &ci, &commandBuffer);

            VkCommandBufferBeginInfo bi{};
            bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

            vkBeginCommandBuffer(commandBuffer, &bi);
            return commandBuffer;
        }

        void EndCommandList(
            VkCommandBuffer commandBuffer
        ) noexcept
        {
            vkEndCommandBuffer(commandBuffer);

            VkSubmitInfo submitInfo{};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers = &commandBuffer;

            vkQueueSubmit(m_GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
            vkQueueWaitIdle(m_GraphicsQueue);

            vkFreeCommandBuffers(m_Device, m_CommandPool, 1, &commandBuffer);
        }
    };
}
