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
        void loadModels();
        void recreateSwapChain();
        void createPipelineLayout();
        void createPipeline();

        void createCommandBuffers();
        void freeCommandBuffers();
        void recordCommandBuffer(int imageIndex);

        void drawFrame();

    private:
        enum { WIDTH = 800, HEIGHT = 600 };

        Window mWindow;
        Device mDevice;
        std::unique_ptr<SwapChain> mSwapChain;
        std::unique_ptr<Pipeline> mPipeline;
        VkPipelineLayout mPipelineLayout;
        std::vector<VkCommandBuffer> mCommandBuffers;

        std::unique_ptr<Model> mModel;
    };
}

