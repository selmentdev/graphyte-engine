#include "Graphics.Vulkan.pch.hxx"
#include "VulkanGpuGraphicsPipelineState.hxx"
#include "VulkanGpuDevice.hxx"
#include "VulkanGpuTypeMapping.hxx"
#include "VulkanGpuPixelFormat.hxx"
#include <Graphyte/Graphics/Gpu/GpuVertex.hxx>
#include "VulkanGpuShader.hxx"
#include "VulkanGpuSampler.hxx"
#include <Graphyte/Flags.hxx>

namespace Graphyte::Graphics
{
    static const std::array<VkVertexInputAttributeDescription, 6> VK_VertexInput_GpuVertexUI
    {
        {
            { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GpuVertexUI, Position) },
            { 0, 1, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexUI, UV[0]) },
            { 0, 2, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexUI, UV[1]) },
            { 0, 3, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexUI, UV[2]) },
            { 0, 4, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexUI, UV[3]) },
            { 0, 5, VK_FORMAT_R8G8B8A8_UNORM, offsetof(GpuVertexUI, Color) },
        }
    };

    static const std::array<VkVertexInputAttributeDescription, 4> VK_VertexInput_GpuVertexCompact
    {
        {
            { 0, 0, VK_FORMAT_R16G16B16A16_SFLOAT, offsetof(GpuVertexCompact, Position) },
            { 0, 1, VK_FORMAT_R8G8B8A8_SNORM, offsetof(GpuVertexCompact, Normal) },
            { 0, 2, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexCompact, UV) },
            { 0, 3, VK_FORMAT_R8G8B8A8_SNORM, offsetof(GpuVertexCompact, Tangent) },
        }
    };

    static const std::array<VkVertexInputAttributeDescription, 6> VK_VertexInput_GpuVertexComplex
    {
        {
            { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GpuVertexComplex, Position) },
            { 1, 0, VK_FORMAT_R8G8B8A8_SNORM, offsetof(GpuVertexComplex, Normal) },
            { 2, 0, VK_FORMAT_R8G8B8A8_SNORM, offsetof(GpuVertexComplex, Tangent) },
            { 3, 0, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexComplex, UV[0]) },
            { 4, 0, VK_FORMAT_R16G16_SFLOAT, offsetof(GpuVertexComplex, UV[1]) },
            { 5, 0, VK_FORMAT_R8G8B8A8_UNORM, offsetof(GpuVertexComplex, Color) },
        }
    };

    static const VkVertexInputBindingDescription VK_VertexBinding_GpuVertexComplex
    {
        0, sizeof(GpuVertexComplex), VK_VERTEX_INPUT_RATE_VERTEX
    };

    static VkDescriptorType GetDescriptorType(
        GpuResourceBindingKey key
    )
    {
        switch (key.ResourceType)
        {
        case GpuResourceType::Sampler:
            return VK_DESCRIPTOR_TYPE_SAMPLER;
        case GpuResourceType::UniformBuffer:
            return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        case GpuResourceType::Texture:
            return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
        case GpuResourceType::StructuredBuffer:
            return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        }

        return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }

    static VkShaderStageFlags ConvertShaderStageFlags(
        GpuShaderVisibility visibility
    ) noexcept
    {
        VkShaderStageFlags result{};

        if (Flags::Has(visibility, GpuShaderVisibility::Pixel))
        {
            result |= VK_SHADER_STAGE_FRAGMENT_BIT;
        }

        if (Flags::Has(visibility, GpuShaderVisibility::Vertex))
        {
            result |= VK_SHADER_STAGE_VERTEX_BIT;
        }

        if (Flags::Has(visibility, GpuShaderVisibility::Compute))
        {
            result |= VK_SHADER_STAGE_COMPUTE_BIT;
        }

        if (Flags::Has(visibility, GpuShaderVisibility::Geometry))
        {
            result |= VK_SHADER_STAGE_GEOMETRY_BIT;
        }

        if (Flags::Has(visibility, GpuShaderVisibility::Domain))
        {
            result |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        }

        if (Flags::Has(visibility, GpuShaderVisibility::Hull))
        {
            result |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        }

        return result;
    }
}

namespace Graphyte::Graphics
{
    GpuGraphicsPipelineStateHandle VulkanGpuDevice::CreateGraphicsPipelineState(
        const GpuGraphicsPipelineStateCreateArgs& args,
        const GpuResourceSetDesc& layout
    ) noexcept
    {
        VkAllocationCallbacks* allocator = nullptr;

        std::vector<VkPipelineShaderStageCreateInfo> shaderStageInfo{};

        if (args.PixelShader != nullptr)
        {
            auto shader = static_cast<VulkanGpuShader*>(args.PixelShader)->m_Resource;

            VkPipelineShaderStageCreateInfo stage{};
            stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            stage.module = shader;
            stage.pName = "main";

            shaderStageInfo.push_back(stage);
        }

        if (args.VertexShader != nullptr)
        {
            auto shader = static_cast<VulkanGpuShader*>(args.VertexShader)->m_Resource;

            VkPipelineShaderStageCreateInfo stage{};
            stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.stage = VK_SHADER_STAGE_VERTEX_BIT;
            stage.module = shader;
            stage.pName = "main";

            shaderStageInfo.push_back(stage);
        }

        if (args.GeometryShader != nullptr)
        {
            auto shader = static_cast<VulkanGpuShader*>(args.GeometryShader)->m_Resource;

            VkPipelineShaderStageCreateInfo stage{};
            stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
            stage.module = shader;
            stage.pName = "main";

            shaderStageInfo.push_back(stage);
        }

        if (args.HullShader != nullptr)
        {
            auto shader = static_cast<VulkanGpuShader*>(args.HullShader)->m_Resource;

            VkPipelineShaderStageCreateInfo stage{};
            stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
            stage.module = shader;
            stage.pName = "main";

            shaderStageInfo.push_back(stage);
        }

        if (args.DomainShader != nullptr)
        {
            auto shader = static_cast<VulkanGpuShader*>(args.DomainShader)->m_Resource;

            VkPipelineShaderStageCreateInfo stage{};
            stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
            stage.module = shader;
            stage.pName = "main";

            shaderStageInfo.push_back(stage);
        }

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.pVertexBindingDescriptions = &VK_VertexBinding_GpuVertexComplex;
        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.pVertexAttributeDescriptions = std::data(VK_VertexInput_GpuVertexComplex);
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(std::size(VK_VertexInput_GpuVertexComplex));

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        static const VkDynamicState dynamicStates[]
        {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR,
            VK_DYNAMIC_STATE_STENCIL_REFERENCE,
            VK_DYNAMIC_STATE_DEPTH_BOUNDS,
        };

        VkPipelineDynamicStateCreateInfo dynamicStateInfo{};
        dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicStateInfo.pDynamicStates = std::data(dynamicStates);
        dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(std::size(dynamicStates));

        VkPipelineRasterizationStateCreateInfo rasterizer = {};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling = {};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineDepthStencilStateCreateInfo depthStencil = {};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo colorBlending = {};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        std::vector<VkDescriptorSetLayoutBinding> layoutBinding{};
        layoutBinding.resize(layout.m_Bindings.size());

        std::array<VkSampler, 16> immutableSamplers{};

        size_t descriptorCount{ 0 };
        size_t samplersCount{ 0 };

        for (auto const& binding : layout.m_Bindings)
        {
            layoutBinding[descriptorCount].binding = static_cast<uint32_t>(descriptorCount);
            layoutBinding[descriptorCount].descriptorCount = 1;
            layoutBinding[descriptorCount].stageFlags = ConvertShaderStageFlags(binding.Key.ShaderVisibility);
            layoutBinding[descriptorCount].descriptorType = GetDescriptorType(binding.Key);
            layoutBinding[descriptorCount].pImmutableSamplers = nullptr;

            if (binding.Key.ResourceType == GpuResourceType::Sampler)
            {
                immutableSamplers[samplersCount] = static_cast<VulkanGpuSampler*>(binding.Resource.Sampler)->m_Resource;
                layoutBinding[descriptorCount].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
                layoutBinding[descriptorCount].pImmutableSamplers = &immutableSamplers[samplersCount];
                ++samplersCount;
            }

            ++descriptorCount;
        }


        VkDescriptorSetLayoutCreateInfo layoutInfo;
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.pNext = nullptr;
        layoutInfo.flags = 0;
        layoutInfo.bindingCount = static_cast<uint32_t>(descriptorCount);
        layoutInfo.pBindings = std::data(layoutBinding);

        VkDescriptorSetLayout layoutHandle{};
        GPU_VK_VALIDATE(vkCreateDescriptorSetLayout(
            m_Device,
            &layoutInfo,
            nullptr,
            &layoutHandle
        ));



#if false
        VkDescriptorSetLayoutBinding uboLayoutBinding = {};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
        samplerLayoutBinding.binding = 1;
        samplerLayoutBinding.descriptorCount = 1;
        samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        samplerLayoutBinding.pImmutableSamplers = nullptr;
        samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
#endif

        //std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
        //VkDescriptorSetLayoutCreateInfo layoutInfo = {};
        //layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        //layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        //layoutInfo.pBindings = bindings.data();
        //
        //VkDescriptorSetLayout descriptorSetLayout{};
        //
        //if (vkCreateDescriptorSetLayout(m_Device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
        //{
        //    //throw std::runtime_error("failed to create descriptor set layout!");
        //}

        VkRenderPass handle_render_pass = VK_NULL_HANDLE;
        {
            VkSubpassDescription subpass{};
            subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

            VkAttachmentDescription attachments[9]{};
            VkAttachmentReference colorAttachmentRef[8]{};

            uint32_t attachmentCount{ 0 };

            for (uint32_t i = 0; i < args.RenderTargetCount; ++i)
            {
                attachments[i].format = VKGetPixelFormat(args.RenderTargetFormat[i]);
                attachments[i].samples = VK_SAMPLE_COUNT_1_BIT;
                attachments[i].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                attachments[i].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
                attachments[i].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                attachments[i].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
                attachments[i].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
                attachments[i].finalLayout = VK_IMAGE_LAYOUT_GENERAL;

                colorAttachmentRef[i].attachment = static_cast<uint32_t>(i);
                colorAttachmentRef[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
                ++attachmentCount;
            }

            subpass.pColorAttachments = colorAttachmentRef;
            subpass.colorAttachmentCount = args.RenderTargetCount;

            VkAttachmentReference depthAttachmentRef{};

            if (args.DepthStencilFormat != PixelFormat::UNKNOWN)
            {
                attachments[args.RenderTargetCount].format = VKGetPixelFormat(args.DepthStencilFormat);
                attachments[args.RenderTargetCount].samples = VK_SAMPLE_COUNT_1_BIT;
                attachments[args.RenderTargetCount].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                attachments[args.RenderTargetCount].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
                attachments[args.RenderTargetCount].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                attachments[args.RenderTargetCount].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
                attachments[args.RenderTargetCount].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
                attachments[args.RenderTargetCount].finalLayout = VK_IMAGE_LAYOUT_GENERAL;

                depthAttachmentRef.attachment = args.RenderTargetCount;
                depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

                subpass.pDepthStencilAttachment = &depthAttachmentRef;
                ++attachmentCount;
            }

            VkRenderPassCreateInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            renderPassInfo.attachmentCount = attachmentCount;
            renderPassInfo.pAttachments = attachments;
            renderPassInfo.subpassCount = 1;
            renderPassInfo.pSubpasses = &subpass;

            GPU_VK_VALIDATE(vkCreateRenderPass(
                m_Device,
                &renderPassInfo,
                nullptr,
                &handle_render_pass
            ));
        }

        VkPipelineLayoutCreateInfo pipelineLayout{};
        pipelineLayout.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayout.setLayoutCount = 1;
        pipelineLayout.pSetLayouts = &layoutHandle;

        VkPipelineLayout pipelineLayoutHandle{ VK_NULL_HANDLE };
        GPU_VK_VALIDATE(vkCreatePipelineLayout(
            m_Device,
            &pipelineLayout,
            nullptr,
            &pipelineLayoutHandle
        ));

        VkPipelineTessellationStateCreateInfo tessCi{};
        tessCi.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;

        VkPipelineViewportStateCreateInfo vpCi{};
        vpCi.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        vpCi.viewportCount = 1;
        vpCi.scissorCount = 1;

        VkGraphicsPipelineCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.stageCount = static_cast<uint32_t>(std::size(shaderStageInfo));
        createInfo.pStages = std::data(shaderStageInfo);
        createInfo.pVertexInputState = &vertexInputInfo;
        createInfo.pInputAssemblyState = &inputAssembly;
        createInfo.pTessellationState = &tessCi;
        createInfo.pViewportState = &vpCi;
        createInfo.pRasterizationState = &rasterizer;
        createInfo.pMultisampleState = &multisampling;
        createInfo.pDepthStencilState = &depthStencil;
        createInfo.pColorBlendState = &colorBlending;
        createInfo.pDynamicState = &dynamicStateInfo;
        createInfo.layout = pipelineLayoutHandle;
        createInfo.renderPass = handle_render_pass;
        createInfo.subpass = 0;
        createInfo.basePipelineHandle = VK_NULL_HANDLE;
        createInfo.basePipelineIndex = 0;

        auto result = new VulkanGpuGraphicsPipelineState{};

        GPU_VK_VALIDATE(vkCreateGraphicsPipelines(
            m_Device,
            VK_NULL_HANDLE,
            1,
            &createInfo,
            allocator,
            &result->m_Pipeline
        ));

        return result;
    }

    void VulkanGpuDevice::DestroyGraphicsPipelineState(
        GpuGraphicsPipelineStateHandle handle
    ) noexcept
    {
        (void)handle;
    }
}
