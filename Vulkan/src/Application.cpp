#include "Precompiled.h"

#include "Application.h"

namespace lve
{
Application::Application()
    : mWindow(WIDTH, HEIGHT, "Hello Vulkan!")
    , mDevice(mWindow)
{
    loadModels();
    createPipelineLayout();
    recreateSwapChain();
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

void Application::recreateSwapChain() 
{
    auto extent = mWindow.GetExtent();
    while (extent.width == 0 || extent.height == 0)
    {
        extent = mWindow.GetExtent();
        glfwWaitEvents();
    }
    vkDeviceWaitIdle(mDevice.Get());

    if (mSwapChain == nullptr)
    {
        mSwapChain = std::make_unique<SwapChain>(mDevice, extent);
    }
    else
    {
        mSwapChain = std::make_unique<SwapChain>(mDevice, extent, std::move(mSwapChain));
        if (mSwapChain->GetImageCount() != mCommandBuffers.size())
        {
            freeCommandBuffers();
            createCommandBuffers();
        }
    }

    createPipeline();
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
    ASSERT(mSwapChain != nullptr, "Cannot create pipeline before swap chain");
    ASSERT(mPipelineLayout != nullptr, "Cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfig{};
    Pipeline::CreateDefaultPipelineConfigInfo(&pipelineConfig);
    pipelineConfig.RenderPass = mSwapChain->GetRenderPass();
    pipelineConfig.PipelineLayout = mPipelineLayout;

    mPipeline = std::make_unique<Pipeline>(mDevice, "Resources/Shaders/SimpleShaderVert.spv", "Resources/Shaders/SimpleShaderFrag.spv", pipelineConfig);
}

void Application::createCommandBuffers() 
{
    mCommandBuffers.resize(mSwapChain->GetImageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = mDevice.GetCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());

    VK_ASSERT(vkAllocateCommandBuffers(mDevice.Get(), &allocInfo, mCommandBuffers.data()), "vkAllocateCommandBuffers() : Failed to allocate command buffers")
}

void Application::freeCommandBuffers() 
{
    vkFreeCommandBuffers(mDevice.Get(), mDevice.GetCommandPool(), static_cast<uint32_t>(mCommandBuffers.size()), mCommandBuffers.data()); 
    mCommandBuffers.clear();
}

void Application::recordCommandBuffer(int imageIndex) 
{
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    VK_ASSERT(vkBeginCommandBuffer(mCommandBuffers[imageIndex], &beginInfo), "vkBeginCommandBuffer() : Failed to begin command buffer")

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = mSwapChain->GetRenderPass();
    renderPassInfo.framebuffer = mSwapChain->GetFrameBuffer(imageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = mSwapChain->GetSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(mCommandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(mSwapChain->GetSwapChainExtent().width);
    viewport.height = static_cast<float>(mSwapChain->GetSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = mSwapChain->GetSwapChainExtent();

    vkCmdSetViewport(mCommandBuffers[imageIndex], 0, 1, &viewport);
    vkCmdSetScissor(mCommandBuffers[imageIndex], 0, 1, &scissor);

    mPipeline->Bind(mCommandBuffers[imageIndex]);
    mModel->Bind(mCommandBuffers[imageIndex]);
    mModel->Draw(mCommandBuffers[imageIndex]);

    vkCmdEndRenderPass(mCommandBuffers[imageIndex]);
    VK_ASSERT(vkEndCommandBuffer(mCommandBuffers[imageIndex]), "vkEndCommandBuffer() : Failed to end command buffer")
}

void Application::drawFrame()
{
    uint32_t imageIndex;
    auto result = mSwapChain->AcquireNextImage(&imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        recreateSwapChain();
        return;
    }

    ASSERT(result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR, "failed to acquire swap chain image")
    
    recordCommandBuffer(imageIndex);
    result = mSwapChain->SubmitCommandBuffers(&mCommandBuffers[imageIndex], &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || mWindow.WasWindowResized())
    {
        mWindow.ResetWindowResizedFlag();
        recreateSwapChain();
        return;
    }
    
    ASSERT(result == VK_SUCCESS, "SubmitCommandBuffers() : failed to present swap chain images!")
}

} // namespace lve