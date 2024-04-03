#pragma once

#include "Device.h"

struct PipelineConfigInfo 
{
    PipelineConfigInfo(const PipelineConfigInfo&) = delete;
    PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

    VkPipelineViewportStateCreateInfo ViewportInfo;
    VkPipelineInputAssemblyStateCreateInfo InputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo RasterizationInfo;
    VkPipelineMultisampleStateCreateInfo MultisampleInfo;
    VkPipelineColorBlendAttachmentState ColorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo ColorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo DepthStencilInfo;
    std::vector<VkDynamicState> DynamicStateEnables;
    VkPipelineDynamicStateCreateInfo DynamicStateInfo;
    VkPipelineLayout PipelineLayout = nullptr;
    VkRenderPass RenderPass = nullptr;
    uint32_t Subpass = 0;
};

namespace lve
{
    class Pipeline final
    {
    public:
        Pipeline() = delete;
        Pipeline(Device& device, const char* vertFilename, const char* fragFilename, const PipelineConfigInfo& configInfo);
        ~Pipeline();
        Pipeline(const Pipeline& rhs) = delete;
        Pipeline& operator=(const Pipeline& rhs) = delete;

    public:
        static void CreateDefaultPipelineConfigInfo(PipelineConfigInfo* outConfigInfo);

        void Bind(VkCommandBuffer commandBuffer);

    private:
        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

    private:
        Device& mDevice; // device always outlives pipeline

        VkPipeline mGraphicsPipeline;
        VkShaderModule mVertShaderModule;
        VkShaderModule mFragShaderModule;
    };
}