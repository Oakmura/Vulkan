#include "Precompiled.h"

#include "Pipeline.h"
#include "Model.h"

namespace lve
{
    Pipeline::Pipeline(Device& device, const char* vertFilename, const char* fragFilename, const PipelineConfigInfo& configInfo)
        : mDevice(device)
    {
        ASSERT(configInfo.PipelineLayout != VK_NULL_HANDLE && configInfo.RenderPass != VK_NULL_HANDLE, "Pipeline() : Failed to create Pipeline");

        std::vector<char> vertShaderCode = BasicUtils::ReadFile(vertFilename);
        std::vector<char> fragShaderCode = BasicUtils::ReadFile(fragFilename);

        createShaderModule(vertShaderCode, &mVertShaderModule);
        createShaderModule(fragShaderCode, &mFragShaderModule);

        VkPipelineShaderStageCreateInfo shaderStages[2];
        shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
        shaderStages[0].module = mVertShaderModule;
        shaderStages[0].pName = "main";
        shaderStages[0].flags = 0;
        shaderStages[0].pNext = nullptr;
        shaderStages[0].pSpecializationInfo = nullptr;
        shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        shaderStages[1].module = mFragShaderModule;
        shaderStages[1].pName = "main";
        shaderStages[1].flags = 0;
        shaderStages[1].pNext = nullptr;
        shaderStages[1].pSpecializationInfo = nullptr;

        
        // Vertex input state
        auto bindingDescriptions = Model::Vertex::GetBindingDescriptions();
        auto attributeDescriptions = Model::Vertex::GetAttributeDescriptions();

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
        vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &configInfo.InputAssemblyInfo;
        pipelineInfo.pViewportState = &configInfo.ViewportInfo;
        pipelineInfo.pRasterizationState = &configInfo.RasterizationInfo;
        pipelineInfo.pMultisampleState = &configInfo.MultisampleInfo;
        pipelineInfo.pColorBlendState = &configInfo.ColorBlendInfo;
        pipelineInfo.pDepthStencilState = &configInfo.DepthStencilInfo;
        pipelineInfo.pDynamicState = nullptr;

        pipelineInfo.layout = configInfo.PipelineLayout;
        pipelineInfo.renderPass = configInfo.RenderPass;
        pipelineInfo.subpass = configInfo.Subpass;

        pipelineInfo.basePipelineIndex = -1;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        VK_ASSERT(vkCreateGraphicsPipelines(mDevice.Get(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &mGraphicsPipeline), "vkCreateGraphicsPipelines() : Failed to create GraphicsPipelines")
    }

    Pipeline::~Pipeline()
    {
        vkDestroyShaderModule(mDevice.Get(), mVertShaderModule, nullptr);
        vkDestroyShaderModule(mDevice.Get(), mFragShaderModule, nullptr);
        vkDestroyPipeline(mDevice.Get(), mGraphicsPipeline, nullptr);
    }

    void Pipeline::CreateDefaultPipelineConfigInfo(PipelineConfigInfo *outConfigInfo, uint32_t width, uint32_t height) 
    {
        outConfigInfo->InputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        outConfigInfo->InputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        outConfigInfo->InputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

        outConfigInfo->Viewport.x = 0.0f;
        outConfigInfo->Viewport.y = 0.0f;
        outConfigInfo->Viewport.width = static_cast<float>(width);
        outConfigInfo->Viewport.height = static_cast<float>(height);
        outConfigInfo->Viewport.minDepth = 0.0f;
        outConfigInfo->Viewport.maxDepth = 1.0f;

        outConfigInfo->Scissor.offset = {0, 0};
        outConfigInfo->Scissor.extent = {width, height};

        outConfigInfo->ViewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        outConfigInfo->ViewportInfo.viewportCount = 1;
        outConfigInfo->ViewportInfo.pViewports = &outConfigInfo->Viewport;
        outConfigInfo->ViewportInfo.scissorCount = 1;
        outConfigInfo->ViewportInfo.pScissors = &outConfigInfo->Scissor;

        outConfigInfo->RasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        outConfigInfo->RasterizationInfo.depthClampEnable = VK_FALSE;
        outConfigInfo->RasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
        outConfigInfo->RasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
        outConfigInfo->RasterizationInfo.lineWidth = 1.0f;
        outConfigInfo->RasterizationInfo.cullMode = VK_CULL_MODE_NONE;
        outConfigInfo->RasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
        outConfigInfo->RasterizationInfo.depthBiasEnable = VK_FALSE;
        outConfigInfo->RasterizationInfo.depthBiasConstantFactor = 0.0f; // Optional
        outConfigInfo->RasterizationInfo.depthBiasClamp = 0.0f;          // Optional
        outConfigInfo->RasterizationInfo.depthBiasSlopeFactor = 0.0f;    // Optional

        outConfigInfo->MultisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        outConfigInfo->MultisampleInfo.sampleShadingEnable = VK_FALSE;
        outConfigInfo->MultisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        outConfigInfo->MultisampleInfo.minSampleShading = 1.0f;          // Optional
        outConfigInfo->MultisampleInfo.pSampleMask = nullptr;            // Optional
        outConfigInfo->MultisampleInfo.alphaToCoverageEnable = VK_FALSE; // Optional
        outConfigInfo->MultisampleInfo.alphaToOneEnable = VK_FALSE;      // Optional

        outConfigInfo->ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        outConfigInfo->ColorBlendAttachment.blendEnable = VK_FALSE;
        outConfigInfo->ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
        outConfigInfo->ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        outConfigInfo->ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;             // Optional
        outConfigInfo->ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
        outConfigInfo->ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
        outConfigInfo->ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;             // Optional

        outConfigInfo->ColorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        outConfigInfo->ColorBlendInfo.logicOpEnable = VK_FALSE;
        outConfigInfo->ColorBlendInfo.logicOp = VK_LOGIC_OP_COPY; // Optional
        outConfigInfo->ColorBlendInfo.attachmentCount = 1;
        outConfigInfo->ColorBlendInfo.pAttachments = &outConfigInfo->ColorBlendAttachment;
        outConfigInfo->ColorBlendInfo.blendConstants[0] = 0.0f; // Optional
        outConfigInfo->ColorBlendInfo.blendConstants[1] = 0.0f; // Optional
        outConfigInfo->ColorBlendInfo.blendConstants[2] = 0.0f; // Optional
        outConfigInfo->ColorBlendInfo.blendConstants[3] = 0.0f; // Optional

        outConfigInfo->DepthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        outConfigInfo->DepthStencilInfo.depthTestEnable = VK_TRUE;
        outConfigInfo->DepthStencilInfo.depthWriteEnable = VK_TRUE;
        outConfigInfo->DepthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
        outConfigInfo->DepthStencilInfo.depthBoundsTestEnable = VK_FALSE;
        outConfigInfo->DepthStencilInfo.minDepthBounds = 0.0f; // Optional
        outConfigInfo->DepthStencilInfo.maxDepthBounds = 1.0f; // Optional
        outConfigInfo->DepthStencilInfo.stencilTestEnable = VK_FALSE;
        outConfigInfo->DepthStencilInfo.front = {}; // Optional
        outConfigInfo->DepthStencilInfo.back = {};  // Optional
    }

    void Pipeline::Bind(VkCommandBuffer commandBuffer) 
    {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mGraphicsPipeline);
    }

    void Pipeline::createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VK_ASSERT(vkCreateShaderModule(mDevice.Get(), &createInfo, nullptr, shaderModule), "vkCreateShaderModule() : Failed to create Shader Module")
    }
}
