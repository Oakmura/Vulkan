#include "Precompiled.h"

#include "Application.h"

namespace lve
{
Application::Application()
    : mWindow(WIDTH, HEIGHT, "Hello Vulkan!")
    , mDevice(mWindow)
    , mSwapChain(mDevice, mWindow.GetExtent())
{
    loadModels();
    createPipelineLayout();
    createPipeline();
    createCommandBuffers();
}

Application::~Application() 
 { 
     vkDestroyPipelineLayout(mDevice.Get(), mPipelineLayout, nullptr);
 }

void Application::Run()
{
    while (!mWindow.ShouldClose())
    {
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(mDevice.Get());
}

void Application::loadModels() 
{
    std::vector<Model::Vertex> vertices
    {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}}, 
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}, 
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };
    mModel = std::make_unique<Model>(mDevice, vertices);
}

void Application::createPipelineLayout() 
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    VK_ASSERT(vkCreatePipelineLayout(mDevice.Get(), &pipelineLayoutInfo, nullptr, &mPipelineLayout), "vkCreatePipelineLayout() : Failed to create pipeline layout")
}

void Application::createPipeline() 
{
    PipelineConfigInfo pipelineConfig{};
    Pipeline::CreateDefaultPipelineConfigInfo(&pipelineConfig, mSwapChain.GetWidth(), mSwapChain.GetHeight());
    pipelineConfig.RenderPass = mSwapChain.GetRenderPass();
    pipelineConfig.PipelineLayout = mPipelineLayout;

    mPipeline = std::make_unique<Pipeline>(mDevice, "Resources/Shaders/SimpleShaderVert.spv", "Resources/Shaders/SimpleShaderFrag.spv", pipelineConfig);
}

void Application::createCommandBuffers() 
{
    mCommandBuffers.resize(mSwapChain.GetImageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mDevice.GetCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());

    VK_ASSERT(vkAllocateCommandBuffers(mDevice.Get(), &allocInfo, mCommandBuffers.data()), "vkAllocateCommandBuffers() : Failed to allocate command buffers")

    for (int i = 0; i < mCommandBuffers.size(); i++)
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        VK_ASSERT(vkBeginCommandBuffer(mCommandBuffers[i], &beginInfo), "vkBeginCommandBuffer() : Failed to begin command buffer")

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = mSwapChain.GetRenderPass();
        renderPassInfo.framebuffer = mSwapChain.GetFrameBuffer(i);

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = mSwapChain.GetSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
        clearValues[1].depthStencil = {1.0f, 0};
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(mCommandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        mPipeline->Bind(mCommandBuffers[i]);
        mModel->Bind(mCommandBuffers[i]);
        mModel->Draw(mCommandBuffers[i]);

        vkCmdEndRenderPass(mCommandBuffers[i]);
        VK_ASSERT(vkEndCommandBuffer(mCommandBuffers[i]), "vkEndCommandBuffer() : Failed to end command buffer")
    }
}

void Application::drawFrame()
{
    uint32_t imageIndex;
    auto result = mSwapChain.AcquireNextImage(&imageIndex);
    ASSERT(result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR, "failed to acquire swap chain image")

    VK_ASSERT(mSwapChain.SubmitCommandBuffers(&mCommandBuffers[imageIndex], &imageIndex), "SubmitCommandBuffers() : Failed to submit command buffers");
}

} // namespace lve