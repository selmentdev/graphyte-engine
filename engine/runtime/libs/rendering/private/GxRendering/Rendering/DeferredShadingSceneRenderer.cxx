#include <Graphyte/Rendering/DeferredShadingSceneRenderer.hxx>
#include <Graphyte/Graphics/ImageCodecs/ImageCodec.DDS.hxx>
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>
#include <Graphyte/Storage/FileManager.hxx>
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/Geometry/Model.hxx>
#include <Graphyte/CommandLine.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS
#define CHECKING_OPENGL 0
#else
#define CHECKING_OPENGL 1
#endif

namespace Graphyte::Rendering
{
    DeferredShadingSceneRenderer::DeferredShadingSceneRenderer(uint32_t width, uint32_t height) noexcept
        : m_RenderTarget{}
        , m_Color{}
        , m_Depth{}
        , m_CameraParams{}
        , m_ObjectParams{}
        , m_Width{ width }
        , m_Height{ height }
    {
        {
            Graphics::GpuTextureCreateArgs args{};
            args.DataFormat = args.ViewFormat = Graphics::PixelFormat::D24_UNORM_S8_UINT;
            args.Width                        = m_Width;
            args.Height                       = m_Height;
            args.Depth                        = 1;
            args.MipCount                     = 1;
            args.DebugName                    = "DepthStencil";
            args.Flags                        = Graphics::GpuTextureFlags::DepthStencil;

            m_Depth = g_RenderDevice->CreateTexture2D(args);
        }
        {
            Graphics::GpuTextureCreateArgs args{};
            args.DataFormat = args.ViewFormat = Graphics::PixelFormat::B8G8R8A8_UNORM;
            args.Width                        = width;
            args.Height                       = height;
            args.Depth                        = 1;
            args.MipCount                     = 1;
            args.DebugName                    = "Color";
            args.Flags                        = Graphics::GpuTextureFlags::RenderTarget;
            m_Color                           = g_RenderDevice->CreateTexture2D(args);
        }

        // Create render target.
        m_RenderTarget = g_RenderDevice->BeginCreateRenderTarget(width, height, 1);
        g_RenderDevice->SetRenderTargetSurface(m_RenderTarget, 0, m_Color, 0);
        g_RenderDevice->SetRenderTargetSurface(m_RenderTarget, -1, m_Depth, 0);
        g_RenderDevice->EndCreateRenderTarget(m_RenderTarget);

        // Create buffers.
        m_CameraParams = g_RenderDevice->CreateUniformBuffer(sizeof(CameraParamsBuffer), Graphics::GpuBufferUsage::Dynamic, nullptr);
        m_ObjectParams = g_RenderDevice->CreateUniformBuffer(sizeof(ObjectParamsBuffer), Graphics::GpuBufferUsage::Dynamic, nullptr);

        {
            //Maths::Matrix rot = Maths::Matrix::RotationX(-Maths::PI_OVER_2<float>);

            ObjectParamsBuffer data{};
            //Maths::Matrix::Store(&data.World, rot);
            //Maths::Matrix::Store(&data.InverseWorld, rot);

            void* buffer = g_RenderDevice->LockUniformBuffer(m_ObjectParams, 0, sizeof(ObjectParamsBuffer), Graphics::GpuResourceLockMode::WriteOnly);
            memcpy(buffer, &data, sizeof(data));
            g_RenderDevice->UnlockUniformBuffer(m_ObjectParams);
        }
        ///////////////////////////////////////
        {
            Graphics::GpuSamplerCreateArgs desc{};
            desc.Filter    = Graphics::GpuFilter::MIN_MAG_MIP_LINEAR;
            desc.AddressU  = Graphics::GpuSamplerAddressMode::Wrap;
            desc.AddressV  = Graphics::GpuSamplerAddressMode::Wrap;
            desc.AddressW  = Graphics::GpuSamplerAddressMode::Wrap;
            desc.CompareOp = Graphics::GpuCompareOperation::Less;
            desc.MinLod    = 0.0F;
            desc.MaxLod    = 10.0F;

            m_Sampler = g_RenderDevice->CreateSampler(desc);
        }
        {
            std::unique_ptr<Graphyte::Graphics::Image> image{};
            {
                std::unique_ptr<Graphyte::Storage::Archive> reader{};

#if true
                Graphyte::Graphics::ImageCodecDDS codec{};
                std::string path = Graphyte::Storage::FileManager::GetProjectContentDirectory() + "images/201e-1067.dds";
#else
                Graphyte::Graphics::ImageCodecPNG codec{};
                std::string path = Graphyte::Storage::FileManager::GetProjectContentDirectory() + "images/uv_checker.png";
#endif

                if (Graphyte::Storage::FileManager::CreateReader(reader, path) == Status::Success)
                {
                    if (codec.Decode(*reader, image) != Status::Success)
                    {
                        GX_ASSERTF(false, "Failed to decode image");
                    }
                }
            }

            GX_ASSERT(image != nullptr);

            std::vector<Graphics::GpuSubresourceData> pixels{ image->GetSubresourcesCount() };
            for (size_t i = 0; i < image->GetSubresourcesCount(); ++i)
            {
                Graphics::ImagePixels* data = image->GetSubresource(i);
                pixels[i].Memory            = data->Buffer;
                pixels[i].Pitch             = static_cast<uint32_t>(data->LinePitch);
                pixels[i].SlicePitch        = static_cast<uint32_t>(data->SlicePitch);
            }

            Graphics::GpuTextureCreateArgs args{};
            args.Type       = Graphics::GpuTextureType::Texture2D;
            args.Width      = image->GetWidth();
            args.Height     = image->GetHeight();
            args.Depth      = 1;
            args.MipCount   = image->GetMipmapCount();
            args.DataFormat = image->GetPixelFormat();
            args.ViewFormat = image->GetPixelFormat();
            args.Data       = pixels.data();
            m_Texture       = g_RenderDevice->CreateTexture2D(args);
        }

        {
            Graphics::GpuResourceSetDesc layout{};
            layout.SetUniformBuffer(1, m_ObjectParams, Graphics::GpuShaderVisibility::Pixel | Graphics::GpuShaderVisibility::Vertex);
            layout.SetUniformBuffer(0, m_CameraParams, Graphics::GpuShaderVisibility::Pixel | Graphics::GpuShaderVisibility::Vertex);
            layout.SetTexture(0, m_Texture, Graphics::GpuShaderVisibility::Pixel);
            layout.SetSampler(0, m_Sampler, Graphics::GpuShaderVisibility::Pixel);
            m_ResourceSet = g_RenderDevice->CreateResourceSet(layout);

            Graphics::GpuGraphicsPipelineStateCreateArgs state{};
            state.InputLayout = Graphics::GpuInputLayout::Complex;

            std::unique_ptr<std::byte[]> vs_data{};
            size_t vs_size{};

            Graphyte::Status status{};

            if (CommandLine::Has("--force-glcore") || CommandLine::Has("--force-vulkan"))
            {
                status = Graphyte::Storage::FileManager::ReadBinary(vs_data, vs_size,
                    Graphyte::Storage::FileManager::GetProjectContentDirectory() + "shaders/basic.vs.spirv");
            }
            else
            {
                status = Graphyte::Storage::FileManager::ReadBinary(vs_data, vs_size,
                    Graphyte::Storage::FileManager::GetProjectContentDirectory() + "shaders/basic.vso");
            }

            GX_ASSERT(status == Status::Success);

            std::unique_ptr<std::byte[]> ps_data{};
            size_t ps_size{};

            if (CommandLine::Has("--force-glcore") || CommandLine::Has("--force-vulkan"))
            {
                status = Graphyte::Storage::FileManager::ReadBinary(ps_data, ps_size,
                    Graphyte::Storage::FileManager::GetProjectContentDirectory() + "shaders/basic.ps.spirv");
            }
            else
            {
                status = Graphyte::Storage::FileManager::ReadBinary(ps_data, ps_size,
                    Graphyte::Storage::FileManager::GetProjectContentDirectory() + "shaders/basic.pso");
            }
            GX_ASSERT(status == Status::Success);

            m_ShaderPS = g_RenderDevice->CreateShader(Graphics::GpuShaderStage::Pixel, { ps_data.get(), ps_size }, Graphics::GpuInputLayout::Complex);
            m_ShaderVS = g_RenderDevice->CreateShader(Graphics::GpuShaderStage::Vertex, { vs_data.get(), vs_size }, Graphics::GpuInputLayout::Complex);

            state.VertexShader = m_ShaderVS;
            state.PixelShader  = m_ShaderPS;

            state.Sample.Count   = 1;
            state.Sample.Quality = 0;

            state.Topology              = Graphics::GpuPrimitiveTopology::Triangle;
            state.RenderTargetCount     = 1;
            state.RenderTargetFormat[0] = Graphyte::Graphics::PixelFormat::B8G8R8A8_UNORM;
            state.DepthStencilFormat    = Graphyte::Graphics::PixelFormat::D32_FLOAT;
            state.IndexBufferStripCut   = Graphics::GpuIndexBufferStripCut::UInt16; // 16 bit indices

            state.BlendState.AlphaToCoverage                       = true;
            state.BlendState.IndependentBlend                      = false;
            state.BlendState.RenderTarget[0].BlendEnable           = true;
            state.BlendState.RenderTarget[0].SourceBlendColor      = Graphics::GpuBlendType::One;
            state.BlendState.RenderTarget[0].DestinationBlendColor = Graphics::GpuBlendType::Zero;
            state.BlendState.RenderTarget[0].BlendOperationColor   = Graphics::GpuBlendOperation::Add;
            state.BlendState.RenderTarget[0].SourceBlendAlpha      = Graphics::GpuBlendType::SourceAlpha;
            state.BlendState.RenderTarget[0].DestinationBlendAlpha = Graphics::GpuBlendType::InvSourceAlpha;
            state.BlendState.RenderTarget[0].BlendOperationAlpha   = Graphics::GpuBlendOperation::Add;
            state.BlendState.RenderTarget[0].RenderTargetWriteMask = Graphics::GpuColorWriteEnable::All;
            state.BlendState.SampleMask                            = 0xffffffff;
            state.BlendState.BlendFactors                          = Graphyte::Maths::Float4{ 1.0F, 1.0F, 1.0F, 1.0F };

            state.RasterizerState.FillMode                      = Graphics::GpuFillMode::Solid;
            state.RasterizerState.CullMode                      = Graphics::GpuCullMode::Back;
            state.RasterizerState.DepthBias                     = 0;
            state.RasterizerState.DepthBiasClamp                = 0.0F;
            state.RasterizerState.SlopeScaledDepthBias          = 0.0F;
            state.RasterizerState.DepthClipEnable               = false;
            state.RasterizerState.MultisampleEnable             = false;
            state.RasterizerState.AntialiasedLineEnable         = false;
            state.RasterizerState.FrontCounterClockwise         = false;
            state.RasterizerState.ForcedSampleCount             = 0;
            state.RasterizerState.ConservativeRasterizationMode = false;

            state.DepthStencilState.DepthWriteMask        = Graphics::GpuDepthWriteMask::All;
            state.DepthStencilState.DepthCompare          = Graphics::GpuCompareOperation::LessEqual;
            state.DepthStencilState.StencilEnable         = false;
            state.DepthStencilState.StencilReadMask       = 0xff;
            state.DepthStencilState.StencilWriteMask      = 0xff;
            state.DepthStencilState.DepthEnable           = true;
            state.DepthStencilState.FrontFace.Pass        = Graphics::GpuStencilOperation::Keep;
            state.DepthStencilState.FrontFace.Fail        = Graphics::GpuStencilOperation::Keep;
            state.DepthStencilState.FrontFace.DepthFail   = Graphics::GpuStencilOperation::Keep;
            state.DepthStencilState.FrontFace.Compare     = Graphics::GpuCompareOperation::Always;
            state.DepthStencilState.BackFace.Pass         = Graphics::GpuStencilOperation::Keep;
            state.DepthStencilState.BackFace.Fail         = Graphics::GpuStencilOperation::Keep;
            state.DepthStencilState.BackFace.DepthFail    = Graphics::GpuStencilOperation::Keep;
            state.DepthStencilState.BackFace.Compare      = Graphics::GpuCompareOperation::Always;
            state.DepthStencilState.DepthBoundsTestEnable = false;
            m_PipelineState                               = g_RenderDevice->CreateGraphicsPipelineState(state, layout);
        }

        std::string destination = Graphyte::Storage::FileManager::GetProjectContentDirectory();
        Graphyte::Storage::Path::Append(destination, "models/111a28.mesh");

        Geometry::Model model{};

        std::unique_ptr<Graphyte::Storage::Archive> reader{};
        Status status = Graphyte::Storage::FileManager::CreateReader(reader, destination);

        if (status == Status::Success)
        {
            *reader << model;
        }
        else
        {
            GX_ASSERTF(false, "Cannot load file: {} ({})\n", destination, status);
        }

        for (auto* part : model.Parts)
        {
            if (part->MeshData->GetVerticesCount() != 0)
            {
                auto sm = new StaticMesh();
                sm->LoadMesh(*part->MeshData, Graphics::GpuInputLayout::Complex);

                Maths::Float4x4A m;
                //Maths::Matrix::Store(&m, model.ComputeWorldMatrix(part));

                Meshes.push_back({ sm, m });
            }
        }
    }

    DeferredShadingSceneRenderer::~DeferredShadingSceneRenderer() noexcept
    {
    }

    void DeferredShadingSceneRenderer::SetupView(
        [[maybe_unused]] Maths::Matrix view,
        [[maybe_unused]] Maths::Matrix projection) noexcept
    {
        CameraParamsBuffer params{};
        //Maths::Matrix::Store(&params.View, view);
        //Maths::Matrix::Store(&params.Projection, projection);

        //Maths::Matrix vp = Maths::Matrix::Multiply(view, projection);
        //Maths::Matrix::Store(&params.ViewProjection, vp);

        {
            void* buffer = g_RenderDevice->LockUniformBuffer(m_CameraParams, 0, sizeof(params), Graphics::GpuResourceLockMode::WriteOnly);
            memcpy(buffer, &params, sizeof(params));
            g_RenderDevice->UnlockUniformBuffer(m_CameraParams);
        }
    }

    void DeferredShadingSceneRenderer::ReleaseGpuResources() noexcept
    {
        for (auto& mesh : Meshes)
        {
            mesh.first->ReleaseGpuResources();
            delete mesh.first;
        }

        Meshes.clear();

        g_RenderDevice->DestroyShader(m_ShaderPS);
        g_RenderDevice->DestroyShader(m_ShaderVS);

        g_RenderDevice->DestroySampler(m_Sampler);
        g_RenderDevice->DestroyGraphicsPipelineState(m_PipelineState);
        g_RenderDevice->DestroyResourceSet(m_ResourceSet);
        g_RenderDevice->DestroyTexture2D(m_Texture);

        g_RenderDevice->DestroyUniformBuffer(m_ObjectParams);
        g_RenderDevice->DestroyUniformBuffer(m_CameraParams);

        g_RenderDevice->DestroyRenderTarget(m_RenderTarget);
        g_RenderDevice->DestroyTexture2D(m_Color);
        g_RenderDevice->DestroyTexture2D(m_Depth);
    }

    void DeferredShadingSceneRenderer::Render(Graphics::GpuCommandList& commandList) noexcept
    {
        //commandList.BindRenderTarget(m_RenderTarget);
        commandList.BindGraphicsPipelineState(m_PipelineState);
        commandList.BindResourceSet(m_ResourceSet);

        for (auto& sm : Meshes)
        {
            ObjectParamsBuffer params;
            params.World = sm.second;
            //Maths::Matrix::Store(&params.InverseWorld, Maths::Matrix::Inverse(nullptr, Maths::Matrix::Load(&params.World)));
            void* buffer = g_RenderDevice->LockUniformBuffer(m_ObjectParams, 0, sizeof(params), Graphics::GpuResourceLockMode::WriteOnly);
            memcpy(buffer, &params, sizeof(params));
            g_RenderDevice->UnlockUniformBuffer(m_ObjectParams);

            sm.first->Render(commandList);
        }
    }

    void DeferredShadingSceneRenderer::RenderGeometry([[maybe_unused]] Graphics::GpuCommandList& commandList) noexcept
    {
    }

    void DeferredShadingSceneRenderer::RenderLights([[maybe_unused]] Graphics::GpuCommandList& commandList) noexcept
    {
    }
}
