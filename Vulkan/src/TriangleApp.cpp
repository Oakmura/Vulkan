#include "Precompiled.h"

#include "TriangleApp.h"

TriangleApp::Run()
{
    initWindow();
    initVulkan();

    mainLoop();

    cleanup();
}

void TriangleApp::initWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    mpWindow = glfwCreateWindow(WIDTH, HEIGHT, "VULKAN", nullptr, nullptr);
}

void TriangleApp::initVulkan()
{

}

void TriangleApp::mainLoop()
{
    while (!glfwWindowShouldClose())
    {
        glfwPollEvents();
    }
}

void TriangleApp::cleanup()
{
    glfwDestroyWindow(mpWindow);

    glfwTerminate();
}
