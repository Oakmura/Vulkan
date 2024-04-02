#include "Precompiled.h"

#include "Application.h"

Application::Application()
    : mWindow(WIDTH, HEIGHT, "Hello Vulkan!")
{
}

void Application::Run()
{
    while (!mWindow.ShouldClose()) 
    {
        glfwPollEvents();
    }
}
