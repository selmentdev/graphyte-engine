#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Graphics/PixelFormat.hxx>
#include <Graphyte/Types.hxx>

namespace Graphyte::Graphics
{
    //
    // Generic handle definition.
    //
    template <typename T> using GpuHandle = T*;


    //
    // Handle declarations.
    //

    class GpuCommandList;
    using GpuCommandListHandle = GpuHandle<GpuCommandList>;

    class GpuDevice;
    using GpuDeviceHandle = GpuHandle<GpuDevice>;

    class GpuResource;
    using GpuResourceHandle = GpuHandle<GpuResource>;

    class GpuViewport;
    using GpuViewportHandle = GpuHandle<GpuViewport>;

    class GpuRenderTarget;
    using GpuRenderTargetHandle = GpuHandle<GpuRenderTarget>;

    class GpuTexture;
    using GpuTextureHandle = GpuHandle<GpuTexture>;
    using GpuTexture1DHandle = GpuHandle<GpuTexture>;
    using GpuTexture2DHandle = GpuHandle<GpuTexture>;
    using GpuTexture3DHandle = GpuHandle<GpuTexture>;
    using GpuTextureCubeHandle = GpuHandle<GpuTexture>;
    using GpuTexture2DArrayHandle = GpuHandle<GpuTexture>;

    class GpuSampler;
    using GpuSamplerHandle = GpuHandle<GpuSampler>;

    class GpuQuery;
    using GpuQueryHandle = GpuHandle<GpuQuery>;

    class GpuOcclusionQuery;
    using GpuOcclusionQueryHandle = GpuHandle<GpuOcclusionQuery>;

    class GpuResourceSet;
    using GpuResourceSetHandle = GpuHandle<GpuResourceSet>;

    class GpuBuffer;
    using GpuBufferHandle = GpuHandle<GpuBuffer>;

    class GpuVertexBuffer;
    using GpuVertexBufferHandle = GpuHandle<GpuVertexBuffer>;

    class GpuIndexBuffer;
    using GpuIndexBufferHandle = GpuHandle<GpuIndexBuffer>;

    class GpuUniformBuffer;
    using GpuUniformBufferHandle = GpuHandle<GpuUniformBuffer>;

    class GpuStructuredBuffer;
    using GpuStructuredBufferHandle = GpuHandle<GpuStructuredBuffer>;

    class GpuPipeline;
    using GpuPipelineHandle = GpuHandle<GpuPipeline>;

    class GpuGraphicsPipelineState;
    using GpuGraphicsPipelineStateHandle = GpuHandle<GpuGraphicsPipelineState>;

    class GpuComputePipelineState;
    using GpuComputePipelineStateHandle = GpuHandle<GpuComputePipelineState>;

    class GpuShader;
    using GpuShaderHandle = GpuHandle<GpuShader>;

    enum struct GpuRenderAPI
    {
        Null,
        D3D11,
        D3D12,
        Vulkan,
        OpenGL,
    };


    enum struct GpuMsaaQuality : uint8_t
    {
        Disabled,
        X2,
        X4,
        X8,
        X16,
    };

    enum struct GpuBlendType : uint8_t
    {
        Zero = 1,
        One = 2,
        SourceColor = 3,
        InvSourceColor = 4,
        SourceAlpha = 5,
        InvSourceAlpha = 6,
        DestinationAlpha = 7,
        InvDestinationAlpha = 8,
        DestinationColor = 9,
        InvDestinationColor = 10,
        SourceAlphaSaturate = 11,
        BlendFactor = 12,
        InvBlendFactor = 13,
        Source1Color = 14,
        InvSource1Color = 15,
        Source1Alpha = 16,
        InvSource1Alpha = 17,
    };

    enum struct GpuBlendOperation : uint8_t
    {
        Add = 1,
        Subtract = 2,
        RevSubtract = 3,
        Min = 4,
        Max = 5,
    };

    enum struct GpuLogicOperation : uint8_t
    {
        Clear = 0,
        Set = 1,
        Copy = 2,
        CopyInverted = 3,
        Noop = 4,
        Invert = 5,
        And = 6,
        Nand = 7,
        Or = 8,
        Nor = 9,
        Xor = 10,
        Equiv = 11,
        AndReverse = 12,
        AndInverted = 13,
        OrReverse = 14,
        OrInverted = 15,
    };

    enum struct GpuFillMode : uint8_t
    {
        Wireframe = 1,
        Solid = 2,
    };

    enum struct GpuCullMode : uint8_t
    {
        None = 1,
        Front = 2,
        Back = 3,
    };

    enum struct GpuCompareOperation : uint8_t
    {
        Never = 1,
        Less = 2,
        Equal = 3,
        LessEqual = 4,
        Greater = 5,
        NotEqual = 6,
        GreaterEqual = 7,
        Always = 8,
    };

    enum struct GpuDepthWriteMask : uint8_t
    {
        Zero = 0,
        All = 1,
    };

    enum struct GpuStencilOperation : uint8_t
    {
        Keep = 1,
        Zero = 2,
        Replace = 3,
        IncrementSaturate = 4,
        DecrementSaturate = 5,
        Invert = 6,
        Increment = 7,
        Decrement = 8,
    };

    enum struct GpuColorWriteEnable : uint8_t
    {
        Red = (1 << 0),
        Green = (1 << 1),
        Blue = (1 << 2),
        Alpha = (1 << 3),
        All = Red | Green | Blue | Alpha,
    };

    enum struct GpuIndexBufferStripCut : uint8_t
    {
        Disabled,
        UInt16,
        UInt32,
    };

    enum struct GpuPrimitiveTopology : uint8_t
    {
        Point = 1,
        Line = 2,
        LineStrip = 3,
        Triangle = 4,
        TriangleStrip = 5,
        Patch = 6,
    };

    enum struct GpuPipelineStateFlags : uint8_t
    {
        None = 0,
        ToolDebug = 1,
    };

    enum struct GpuBufferUsage : uint16_t
    {
        None = 0,
        Static = 1 << 0,
        Dynamic = 1 << 1,
        Volatile = 1 << 2,
        UnorderedAccess = 1 << 3,
        ByteAddress = 1 << 4,
        UAVCounter = 1 << 5,
        StreamOutput = 1 << 6,
        DrawIndirect = 1 << 7,
        ShaderResource = 1 << 8,
        CpuAccessible = 1 << 9,
        ZeroStride = 1 << 10,
        FastVRAM = 1 << 11,
        Transient = 1 << 12,
        AnyDynamic = Dynamic | Volatile,
    };
    GX_ENUM_CLASS_FLAGS(GpuBufferUsage);

    enum struct GpuResourceLockMode
    {
        ReadWrite,
        ReadOnly,
        WriteOnly,
        WriteOnlyUnsynchronized,
        WriteOnlyPersistent,
    };


    enum struct GpuCubeFace : uint32_t
    {
        PositiveX = 0,
        NegativeX = 1,
        PositiveY = 2,
        NegativeY = 3,
        PositiveZ = 4,
        NegativeZ = 5,
    };

    enum struct GpuShaderStage : uint32_t
    {
        Unknown     = 0,
        Pixel       = 1,
        Vertex      = 2,
        Geometry    = 3,
        Hull        = 4,
        Domain      = 5,
        Compute     = 6,
    };

    enum struct GpuShaderVisibility : uint8_t
    {
        Pixel       = 1 << 0,
        Vertex      = 1 << 1,
        Geometry    = 1 << 2,
        Hull        = 1 << 3,
        Domain      = 1 << 4,
        Compute     = 1 << 5,
        None        = 0,
        All         = Pixel | Vertex | Geometry | Hull | Domain | Compute,
    };
    GX_ENUM_CLASS_FLAGS(GpuShaderVisibility);


    /**
     * @brief   This enum specifies available shader profiles.
     *
     * @note    Essentially, these enum values represent internal shader format. For example, SPIRV_1_0 may be used with
     *          both OpenGL and Vulkan.
     */
    enum struct GpuShaderProfile : uint32_t
    {
        D3DSM_5_0   = 0x0001'05'00,
        D3DSM_5_1   = 0x0001'05'01,
        D3DSM_6_0   = 0x0001'06'00,
        D3DSM_6_1   = 0x0001'06'01,
        D3DSM_6_2   = 0x0001'06'02,

        SPIRV_1_0   = 0x0002'01'00,
        SPIRV_1_1   = 0x0002'01'01,
        SPIRV_1_2   = 0x0002'01'02,

        GLSL_4_50   = 0x0003'04'50,
        GLSL_4_60   = 0x0003'04'60,

        ESSL_2_00   = 0x0004'02'00,
        ESSL_3_00   = 0x0004'03'00,
        ESSL_3_10   = 0x0004'03'10,
        ESSL_3_20   = 0x0004'03'20,
        ESSL_3_30   = 0x0004'03'30,
    };

    enum class GpuShaderType : size_t
    {
        Pixel       = 0,
        Vertex      = 1,
        Geometry    = 2,
        Hull        = 3,
        Domain      = 4,
        Compute     = 5,
    };

    enum struct GpuFilterType : uint8_t
    {
        Point = 0,
        Linear = 1,
    };

    enum struct GpuFilterReductionType : uint8_t
    {
        Standard = 0,
        Comparison = 1,
        Minimum = 2,
        Maximum = 3,
    };

    enum struct GpuFilter : uint16_t;

    struct GpuFilterTraits final
    {
    public:
        static constexpr const uint16_t REDUCTION_TYPE_MASK = 0x3;
        static constexpr const uint16_t REDUCTION_TYPE_SHIFT = 7;
        static constexpr const uint16_t FILTER_TYPE_MASK = 0x3;
        static constexpr const size_t FILTER_MIN_SHIFT = 4;
        static constexpr const size_t FILTER_MAG_SHIFT = 2;
        static constexpr const size_t FILTER_MIP_SHIFT = 0;
        static constexpr const uint16_t ANISOTROPIC_BIT = 0x40;

        static constexpr GpuFilter MakeBasic(
            GpuFilterType min,
            GpuFilterType mag,
            GpuFilterType mip,
            GpuFilterReductionType reduction
        ) noexcept
        {
            uint16_t const result = static_cast<uint16_t>(
                ((static_cast<uint16_t>(min) & FILTER_TYPE_MASK) << FILTER_MIN_SHIFT) |
                ((static_cast<uint16_t>(mag) & FILTER_TYPE_MASK) << FILTER_MAG_SHIFT) |
                ((static_cast<uint16_t>(mip) & FILTER_TYPE_MASK) << FILTER_MIP_SHIFT) |
                ((static_cast<uint16_t>(reduction) & REDUCTION_TYPE_MASK) << REDUCTION_TYPE_SHIFT));

            return static_cast<GpuFilter>(result);
        }

        static constexpr GpuFilter MakeAnisotropic(
            GpuFilterReductionType reduction
        ) noexcept
        {
            uint16_t const result = static_cast<uint16_t>(
                ((static_cast<uint16_t>(GpuFilterType::Linear) & FILTER_TYPE_MASK) << FILTER_MIN_SHIFT) |
                ((static_cast<uint16_t>(GpuFilterType::Linear) & FILTER_TYPE_MASK) << FILTER_MAG_SHIFT) |
                ((static_cast<uint16_t>(GpuFilterType::Linear) & FILTER_TYPE_MASK) << FILTER_MIP_SHIFT) |
                ((static_cast<uint16_t>(reduction) & REDUCTION_TYPE_MASK) << REDUCTION_TYPE_SHIFT) |
                ANISOTROPIC_BIT);

            return static_cast<GpuFilter>(result);
        }

    public:
        static constexpr GpuFilterType GetMinFilter(
            GpuFilter filter
        ) noexcept
        {
            return static_cast<GpuFilterType>((static_cast<uint16_t>(filter) >> FILTER_MIN_SHIFT) & FILTER_TYPE_MASK);
        }

        static constexpr GpuFilterType GetMagFilter(
            GpuFilter filter
        ) noexcept
        {
            return static_cast<GpuFilterType>((static_cast<uint16_t>(filter) >> FILTER_MAG_SHIFT) & FILTER_TYPE_MASK);
        }

        static constexpr GpuFilterType GetMipFilter(
            GpuFilter filter
        ) noexcept
        {
            return static_cast<GpuFilterType>((static_cast<uint16_t>(filter) >> FILTER_MIP_SHIFT) & FILTER_TYPE_MASK);
        }

        static constexpr GpuFilterReductionType GetReductionType(
            GpuFilter filter
        ) noexcept
        {
            return static_cast<GpuFilterReductionType>((static_cast<uint16_t>(filter) >> REDUCTION_TYPE_SHIFT) & REDUCTION_TYPE_MASK);
        }

        static constexpr bool IsAnisotropic(
            GpuFilter filter
        ) noexcept
        {
            return (static_cast<uint16_t>(filter) & ANISOTROPIC_BIT) != 0;
        }
    };

    enum struct GpuFilter : uint16_t
    {
        MIN_MAG_MIP_POINT                               = 0b00'0'00'00'00,
        MIN_MAG_POINT_MIP_LINEAR                        = 0b00'0'00'00'01,
        MIN_POINT_MAG_LINEAR_MIP_POINT                  = 0b00'0'00'01'00,
        MIN_POINT_MAG_MIP_LINEAR                        = 0b00'0'00'01'01,
        MIN_LINEAR_MAG_MIP_POINT                        = 0b00'0'01'00'00,
        MIN_LINEAR_MAG_POINT_MIP_LINEAR                 = 0b00'0'01'00'01,
        MIN_MAG_LINEAR_MIP_POINT                        = 0b00'0'01'01'00,
        MIN_MAG_MIP_LINEAR                              = 0b00'0'01'01'01,
        ANISOTROPIC                                     = 0b00'1'01'01'01,

        COMPARISON_MIN_MAG_MIP_POINT                    = 0b01'0'00'00'00,
        COMPARISON_MIN_MAG_POINT_MIP_LINEAR             = 0b01'0'00'00'01,
        COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT       = 0b01'0'00'01'00,
        COMPARISON_MIN_POINT_MAG_MIP_LINEAR             = 0b01'0'00'01'01,
        COMPARISON_MIN_LINEAR_MAG_MIP_POINT             = 0b01'0'01'00'00,
        COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR      = 0b01'0'01'00'01,
        COMPARISON_MIN_MAG_LINEAR_MIP_POINT             = 0b01'0'01'01'00,
        COMPARISON_MIN_MAG_MIP_LINEAR                   = 0b01'0'01'01'01,
        COMPARISON_ANISOTROPIC                          = 0b01'1'01'01'01,

        MINIMUM_MIN_MAG_MIP_POINT                       = 0b10'0'00'00'00,
        MINIMUM_MIN_MAG_POINT_MIP_LINEAR                = 0b10'0'00'00'01,
        MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT          = 0b10'0'00'01'00,
        MINIMUM_MIN_POINT_MAG_MIP_LINEAR                = 0b10'0'00'01'01,
        MINIMUM_MIN_LINEAR_MAG_MIP_POINT                = 0b10'0'01'00'00,
        MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR         = 0b10'0'01'00'01,
        MINIMUM_MIN_MAG_LINEAR_MIP_POINT                = 0b10'0'01'01'00,
        MINIMUM_MIN_MAG_MIP_LINEAR                      = 0b10'0'01'01'01,
        MINIMUM_ANISOTROPIC                             = 0b10'1'01'01'01,

        MAXIMUM_MIN_MAG_MIP_POINT                       = 0b11'0'00'00'00,
        MAXIMUM_MIN_MAG_POINT_MIP_LINEAR                = 0b11'0'00'00'01,
        MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT          = 0b11'0'00'01'00,
        MAXIMUM_MIN_POINT_MAG_MIP_LINEAR                = 0b11'0'00'01'01,
        MAXIMUM_MIN_LINEAR_MAG_MIP_POINT                = 0b11'0'01'00'00,
        MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR         = 0b11'0'01'00'01,
        MAXIMUM_MIN_MAG_LINEAR_MIP_POINT                = 0b11'0'01'01'00,
        MAXIMUM_MIN_MAG_MIP_LINEAR                      = 0b11'0'01'01'01,
        MAXIMUM_ANISOTROPIC                             = 0b11'1'01'01'01,
    };

    enum struct GpuSamplerAddressMode : uint8_t
    {
        Wrap = 1,
        Mirror = 2,
        Clamp = 3,
        Border = 4,
        MirrorOnce = 5,
    };

    enum class GpuInputLayout : uint32_t
    {
        UI,
        Compact,
        Complex,
    };

    //
    // Structures
    //

    struct GpuShaderBytecode final
    {
        const void* Bytecode;
        size_t Size;
    };

    struct GpuSubresourceData final
    {
        void* Memory;
        uint32_t Pitch;
        uint32_t SlicePitch;
    };

    struct GpuViewportDesc final
    {
        float TopLeftX;
        float TopLeftY;
        float Width;
        float Height;
        float MinDepth;
        float MaxDepth;
    };

    struct GpuRect final
    {
        uint32_t Left;
        uint32_t Top;
        uint32_t Right;
        uint32_t Bottom;
    };

    struct GpuBox final
    {
        uint32_t Left;
        uint32_t Top;
        uint32_t Front;
        uint32_t Right;
        uint32_t Bottom;
        uint32_t Back;
    };

    struct GpuSampleDesc final
    {
        uint32_t Count;
        uint32_t Quality;
    };

    struct GpuLimits final
    {
        static constexpr const size_t TextureUnitsCount = 16;
        static constexpr const size_t UniformBuffersCount = 16;
        static constexpr const size_t ResourceSetCount = 8;
        static constexpr const size_t ShaderUnitsCount = 6;
    };

    struct GpuSamplerCreateArgs final
    {
        float BorderColor[4];
        float MipLodBias;
        float MinLod;
        float MaxLod;
        uint32_t MaxAnisotropy;
        GpuFilter Filter;
        GpuSamplerAddressMode AddressU;
        GpuSamplerAddressMode AddressV;
        GpuSamplerAddressMode AddressW;
        GpuCompareOperation CompareOp;
    };

    struct GpuRenderTargetBlendDesc final
    {
        bool BlendEnable;
        bool LogicOpEnable;
        GpuBlendType SourceBlendColor;
        GpuBlendType DestinationBlendColor;
        GpuBlendOperation BlendOperationColor;
        GpuBlendType SourceBlendAlpha;
        GpuBlendType DestinationBlendAlpha;
        GpuBlendOperation BlendOperationAlpha;
        GpuLogicOperation LogicOperation;
        GpuColorWriteEnable RenderTargetWriteMask;
    };

    struct GpuBlendStateDesc final
    {
        bool AlphaToCoverage;
        bool IndependentBlend;
        GpuRenderTargetBlendDesc RenderTarget[8];
        uint32_t SampleMask;
        Float4 BlendFactors;
    };

    struct GpuRasterizerStateDesc final
    {
        GpuFillMode FillMode;
        GpuCullMode CullMode;
        int DepthBias;
        float DepthBiasClamp;
        float SlopeScaledDepthBias;
        uint32_t ForcedSampleCount;
        bool DepthClipEnable;
        bool ScissorEnable;
        bool MultisampleEnable;
        bool AntialiasedLineEnable;
        bool FrontCounterClockwise;
        bool ConservativeRasterizationMode;
    };

    struct GpuDepthStencilOperationDesc final
    {
        GpuStencilOperation Fail;
        GpuStencilOperation DepthFail;
        GpuStencilOperation Pass;
        GpuCompareOperation Compare;
    };

    struct GpuDepthStencilStateDesc final
    {
        GpuDepthWriteMask DepthWriteMask;
        GpuCompareOperation DepthCompare;
        GpuDepthStencilOperationDesc FrontFace;
        GpuDepthStencilOperationDesc BackFace;
        uint8_t StencilReadMask;
        uint8_t StencilWriteMask;
        bool DepthEnable;
        bool StencilEnable;
        bool DepthBoundsTestEnable;
    };

    struct GpuGraphicsPipelineStateCreateArgs final
    {
        GpuShaderHandle VertexShader;
        GpuShaderHandle PixelShader;
        GpuShaderHandle GeometryShader;
        GpuShaderHandle DomainShader;
        GpuShaderHandle HullShader;
        GpuBlendStateDesc BlendState;
        GpuRasterizerStateDesc RasterizerState;
        GpuDepthStencilStateDesc DepthStencilState;
        GpuInputLayout InputLayout;
        GpuIndexBufferStripCut IndexBufferStripCut;
        GpuPrimitiveTopology Topology;
        uint32_t RenderTargetCount;
        PixelFormat RenderTargetFormat[8];
        PixelFormat DepthStencilFormat;
        GpuSampleDesc Sample;
        uint32_t NodeMask;
        GpuPipelineStateFlags Flags;
    };

    struct GpuComputePipelineStateCreateArgs final
    {
        GpuShaderBytecode ComputeShader;
        uint64_t NodeMask;
        GpuPipelineStateFlags Flags;
    };

    enum struct GpuTextureType : uint32_t
    {
        Texture2D,
        Texture2DArray,
        Texture3D,
        TextureCube,
    };

    /*!
     * \remarks
     *      Render target used in 3D environment should also have mipmaps generated.
     */
    enum struct GpuTextureFlags : uint32_t
    {
        Default = 0,
        RenderTarget = 1 << 0,
        Dynamic = 1 << 1,
        DepthStencil = 1 << 2,
        UnorderedAccess = 1 << 3,
        GenerateMipmaps = 1 << 4,
    };
    GX_ENUM_CLASS_FLAGS(GpuTextureFlags);

    struct GpuTextureCreateArgs final
    {
        GpuTextureType Type;
        GpuTextureFlags Flags;
        uint32_t Width;
        uint32_t Height;
        uint32_t Depth;
        uint32_t MipCount;
        const GpuSubresourceData* Data;
        PixelFormat DataFormat;
        PixelFormat ViewFormat;
        const char* DebugName;
    };

    struct GpuTextureCreateViewArgs final
    {
        GpuTextureHandle Texture;
        PixelFormat ViewFormat;
    };

    enum class GpuResourceType : uint8_t
    {
        Texture = 0,
        UniformBuffer = 1,
        StructuredBuffer = 2,
        Sampler = 3,
    };

    enum class GpuResourceBindingFlags : uint8_t
    {
        None = 0,
        Structured = 1 << 0,
    };

    struct GpuResourceBindingKey final
    {
        union
        {
            struct
            {
                GpuResourceType ResourceType;
                uint8_t ShaderRegister;
                GpuShaderVisibility ShaderVisibility;
                GpuResourceBindingFlags Flags;
            };
            uint32_t Index;
        };
    };
    static_assert(sizeof(GpuResourceBindingKey) == sizeof(uint32_t));
    static_assert(alignof(GpuResourceBindingKey) == alignof(uint32_t));

    struct GpuResourceBinding final
    {
        GpuResourceBindingKey Key;
        union
        {
            GpuSamplerHandle Sampler;
            GpuTextureHandle Texture;
            GpuUniformBufferHandle UniformBuffer;
        } Resource;
    };

    class GpuResourceSetDesc final
    {
    public:
        std::vector<GpuResourceBinding> m_Bindings;

        void SetTexture(
            uint32_t shader_register,
            GpuTextureHandle handle,
            GpuShaderVisibility shader_visibility
        ) noexcept
        {
            GpuResourceBinding binding{};
            binding.Key.ResourceType = GpuResourceType::Texture;
            binding.Key.ShaderRegister = static_cast<uint8_t>(shader_register);
            binding.Key.ShaderVisibility = shader_visibility;
            binding.Key.Flags = GpuResourceBindingFlags::None;
            binding.Resource.Texture = handle;

            Set(binding);
        }

        void SetSampler(
            uint32_t shader_register,
            GpuSamplerHandle handle,
            GpuShaderVisibility shader_visibility
        ) noexcept
        {
            GpuResourceBinding binding{};
            binding.Key.ResourceType = GpuResourceType::Sampler;
            binding.Key.ShaderRegister = static_cast<uint8_t>(shader_register);
            binding.Key.ShaderVisibility = shader_visibility;
            binding.Key.Flags = GpuResourceBindingFlags::None;
            binding.Resource.Sampler = handle;

            Set(binding);
        }

        void SetUniformBuffer(
            uint32_t shader_register,
            GpuUniformBufferHandle handle,
            GpuShaderVisibility shader_visibility
        ) noexcept
        {
            GpuResourceBinding binding{};
            binding.Key.ResourceType = GpuResourceType::UniformBuffer;
            binding.Key.ShaderRegister = static_cast<uint8_t>(shader_register);
            binding.Key.ShaderVisibility = shader_visibility;
            binding.Resource.UniformBuffer = handle;

            Set(binding);
        }

        void Finalize() noexcept
        {
            std::sort(std::begin(m_Bindings), std::end(m_Bindings), [](const GpuResourceBinding& left, const GpuResourceBinding& right)
            {
                return left.Key.Index < right.Key.Index;
            });
        }

    private:
        void Set(
            const GpuResourceBinding& binding
        ) noexcept
        {
            auto&& it = std::find_if(std::begin(m_Bindings), std::end(m_Bindings), [&](const GpuResourceBinding& other)
            {
                return binding.Key.ResourceType == other.Key.ResourceType
                    && binding.Key.ShaderRegister == other.Key.ShaderRegister;
            });

            if (it != std::end(m_Bindings))
            {
                (*it) = binding;
            }
            else
            {
                m_Bindings.push_back(binding);
            }
        }
    };
}
