#pragma once

#include "Window.h"
#include "SwapChain.h"
#include "Device.h"
#include "GameObject.h"
#include "Pipeline.h"

namespace lve
{
    class Application final
    {
    public:
        Application();
        ~Application();
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

    public:
        void Run();

    private:
        void drawFrame();
        void recordCommandBuffer(int imageIndex);
        void renderGameObjects(VkCommandBuffer commandBuffer);
        void freeCommandBuffers();

        void loadGameObjects();
        void recreateSwapChain();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();

    private:
        enum { WIDTH = 800, HEIGHT = 600 };

        Window mWindow;
        Device mDevice;
        
        std::vector<GameObject> mGameObjects;

        VkPipelineLayout mPipelineLayout;
        std::unique_ptr<SwapChain> mSwapChain;
        std::unique_ptr<Pipeline> mPipeline;
        std::vector<VkCommandBuffer> mCommandBuffers;
    };
}

