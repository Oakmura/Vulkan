#include "Precompiled.h"

#include "Application.h"

Application::Application()
    : mWindow(WIDTH, HEIGHT, "Hello Vulkan!")
    , mPipeline("Resources/Shaders/SimpleShaderVert.spv", "Resources/Shaders/SimpleShaderFrag.spv")
{   
}

void Application::Run()
{
    while (!mWindow.ShouldClose()) 
    {
        glfwPollEvents();
    }
}
