#pragma once

#include "Window.h"
#include "SwapChain.h"
#include "Device.h"
#include "Model.h"
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
        void freeCommandBuffers();

        void loadModels();
        void recreateSwapChain();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();

    private:
        enum { WIDTH = 800, HEIGHT = 600 };

        Window mWindow;
        Device mDevice;

        std::unique_ptr<Model> mModel;

        VkPipelineLayout mPipelineLayout;
        std::unique_ptr<SwapChain> mSwapChain;
        std::unique_ptr<Pipeline> mPipeline;
        std::vector<VkCommandBuffer> mCommandBuffers;
    };
}

