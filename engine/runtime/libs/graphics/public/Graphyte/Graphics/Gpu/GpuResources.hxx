#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Graphics/PixelFormat.hxx>
#include <Graphyte/Graphics/Gpu/GpuDefinitions.hxx>
#include <Graphyte/Maths.hxx>

namespace Graphyte::Graphics
{
    class GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuResource>);

    class GpuSampler : public GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuSampler>);

    class GpuBuffer : public GpuResource
    {
    public:
        uint32_t m_Size;
        GpuBufferUsage m_Usage;
    };
    static_assert(!std::is_polymorphic_v<GpuBuffer>);

    class GpuIndexBuffer : public GpuBuffer
    {
    public:
        uint32_t m_Stride;
    };
    static_assert(!std::is_polymorphic_v<GpuIndexBuffer>);

    class GpuVertexBuffer : public GpuBuffer
    {
    };
    static_assert(!std::is_polymorphic_v<GpuVertexBuffer>);

    class GpuUniformBuffer : public GpuBuffer
    {
    };
    static_assert(!std::is_polymorphic_v<GpuUniformBuffer>);

    class GpuStructuredBuffer : public GpuBuffer
    {
    };
    static_assert(!std::is_polymorphic_v<GpuStructuredBuffer>);

    class GpuGraphicsPipelineState : public GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuGraphicsPipelineState>);

    class GpuComputePipelineState : public GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuComputePipelineState>);

    class GpuQuery : public GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuQuery>);

    class GpuOcclusionQuery : public GpuQuery
    {
    };
    static_assert(!std::is_polymorphic_v<GpuOcclusionQuery>);

    class GpuRenderTarget : public GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuRenderTarget>);

    class GpuTexture : public GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuTexture>);

    class GpuViewport : public GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuViewport>);

    class GpuResourceSet : public GpuResource
    {
    };
    static_assert(!std::is_polymorphic_v<GpuResourceSet>);

    class GpuShader : public GpuResource
    {
    public:
        GpuShaderStage m_Stage;
    };
    static_assert(!std::is_polymorphic_v<GpuShader>);
}
