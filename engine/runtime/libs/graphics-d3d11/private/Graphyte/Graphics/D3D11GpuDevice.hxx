#pragma once
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>
#include "D3D11GpuCommon.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuCommandList;

    struct D3D11GpuResourceLockKey final
    {
        void* Resource;
        uint32_t Subresource;

        D3D11GpuResourceLockKey() noexcept = default;

        D3D11GpuResourceLockKey(
            ID3D11Buffer* resource,
            uint32_t subresource = 0
        ) noexcept
            : Resource{ (void*)resource }
            , Subresource{ subresource }
        {
        }

        D3D11GpuResourceLockKey(
            ID3D11Texture2D* resource,
            uint32_t subresource = 0
        ) noexcept
            : Resource{ (void*)resource }
            , Subresource{ subresource }
        {
        }

        D3D11GpuResourceLockKey(
            ID3D11Texture3D* resource,
            uint32_t subresource = 0
        ) noexcept
            : Resource{ (void*)resource }
            , Subresource{ subresource }
        {
        }

        bool operator == (const D3D11GpuResourceLockKey& other) const noexcept
        {
            return Resource == other.Resource && Subresource == other.Subresource;
        }
        bool operator != (const D3D11GpuResourceLockKey& other) const noexcept
        {
            return Resource != other.Resource || Subresource != other.Subresource;
        }

        bool operator < (const D3D11GpuResourceLockKey& other) const noexcept
        {
            if (Resource == other.Resource)
            {
                return Subresource < other.Subresource;
            }
            return Resource < other.Resource;
        }

        D3D11GpuResourceLockKey& operator= (const D3D11GpuResourceLockKey& other) noexcept
        {
            Resource = other.Resource;
            Subresource = other.Subresource;
            return (*this);
        }
    };

    struct D3D11GpuResourceLockData final
    {
    private:
        uint8_t* m_Data;
        bool m_WasAllocated;

    public:
        Microsoft::WRL::ComPtr<ID3D11Resource> StagingResource;
        uint32_t Pitch;
        uint32_t DepthPitch;

        D3D11GpuResourceLockData() noexcept
            : m_Data{}
            , m_WasAllocated{ false }
            , StagingResource{}
            , Pitch{}
            , DepthPitch{}
        {
        }

        void Allocate(
            size_t size
        ) noexcept
        {
            m_Data = (uint8_t*)_aligned_malloc(size, 16);
            m_WasAllocated = true;
        }

        void SetData(
            void* data
        ) noexcept
        {
            GX_ASSERT(!m_WasAllocated);
            m_Data = (uint8_t*)data;
        }

        uint8_t* GetData() const noexcept
        {
            return m_Data;
        }

        void DeallocateData() noexcept
        {
            GX_ASSERT(m_WasAllocated);
            _aligned_free(m_Data);
            m_Data = nullptr;
        }
    };

    class D3D11GpuDevice final : public GpuDevice
    {
        friend class D3D11GpuViewport;
        friend class D3D11GpuSampler;
        friend class D3D11GpuVertexBuffer;
        friend class D3D11GpuTexture2D;
        friend class D3D11GpuTexture2DArray;
        friend class D3D11GpuTexture3D;
        friend class D3D11GpuTextureCube;
        friend class D3D11GpuCommandList;
    private:
        Microsoft::WRL::ComPtr<IDXGIFactory1> m_Factory;
        Microsoft::WRL::ComPtr<IDXGIAdapter1> m_Adapter;
        Microsoft::WRL::ComPtr<ID3D11Device1> m_Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_Context;
        D3D_FEATURE_LEVEL m_FeatureLevel;

        std::map<D3D11GpuResourceLockKey, D3D11GpuResourceLockData> m_ResourceLocks;

        // Created lazily
        std::vector<ID3D11DeviceChild*> m_ResourcesToDestroy;

        std::map<GpuInputLayout, ID3D11InputLayout*> m_InputLayouts;
        std::map<uint64_t, ID3D11RasterizerState*> m_RasterizerState;
        std::map<uint64_t, ID3D11DepthStencilState*> m_DepthStencilState;
        std::map<uint64_t, ID3D11BlendState*> m_BlendState;

        D3D11GpuCommandList* m_ImmediateCommandList;

        bool m_DebugDevice;

    private:
        void DeferResourceRelease(
            ID3D11DeviceChild* resource
        ) noexcept
        {
            if (resource != nullptr)
            {
                m_ResourcesToDestroy.push_back(resource);
            }
        }
        void ReleaseDeferredResources() noexcept;

    public:
        D3D11GpuDevice() noexcept;
        virtual ~D3D11GpuDevice() noexcept;

    public:
        void Tick(float time) noexcept override;

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

        virtual void DestroyCommandList(
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
