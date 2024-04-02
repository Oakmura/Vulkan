#include "Precompiled.h"

#include "Application.h"

namespace lve
{
    Application::Application()
        : mWindow(WIDTH, HEIGHT, "Hello Vulkan!")
        , mDevice(mWindow)
        , mPipeline(mDevice, "Resources/Shaders/SimpleShaderVert.spv", "Resources/Shaders/SimpleShaderFrag.spv", Pipeline::CreateDefaultPipelineConfigInfo(WIDTH, HEIGHT))
    {
    }

    void Application::Run()
    {
        while (!mWindow.ShouldClose())
        {
            glfwPollEvents();
        }
    }
}