#include <Graphyte/Rendering/DeferredShadingCompositor.hxx>
#include <Graphyte/Graphics/ImageCodecs/ImageCodec.DDS.hxx>
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>
#include <Graphyte/Storage/FileManager.hxx>
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/Geometry/Model.hxx>
#include <Graphyte/Rendering/DeferredShadingSceneRenderer.hxx>

#if GX_PLATFORM_WINDOWS
#define CHECKING_OPENGL 0
#else
#define CHECKING_OPENGL 1
#endif

namespace Graphyte::Rendering
{
    DeferredShadingCompositor::DeferredShadingCompositor([[maybe_unused]] const class DeferredShadingSceneRederer* renderer) noexcept
        : m_Mesh{}
        , m_ShaderPS{}
        , m_ShaderVS{}
        , m_Sampler{}
        , m_Texture{}
        , m_ResourceSet{}
        , m_PipelineState{}
    {
    }

    DeferredShadingCompositor::~DeferredShadingCompositor() noexcept
    {
    }

    void DeferredShadingCompositor::ReleaseGpuResources() noexcept
    {
    }

    void DeferredShadingCompositor::Render([[maybe_unused]] Graphics::GpuCommandList& commandList) noexcept
    {
    }
}
