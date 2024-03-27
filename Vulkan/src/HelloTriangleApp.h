#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class HelloTriangleApp final
{
public:
    HelloTriangleApp() = default;
    ~HelloTriangleApp() = default;
    HelloTriangleApp(const HelloTriangleApp &rhs) = delete;
    HelloTriangleApp& operator=(const HelloTriangleApp &rhs) = delete;

public:
    void run();

private:
    void initWindow();

    void initVulkan();
    void createInstance();

    void mainLoop();

    void cleanup();

private:
    GLFWwindow *mWindow;
    VkInstance mInstance;
};

