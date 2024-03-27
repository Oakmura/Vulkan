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
    void Run();

private:
    void initWindow();

    void initVulkan();
    void createInstance();

    bool checkValidationSupport();
    std::vector<const char*> getRequiredExtensions();

    void setupDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    void mainLoop();

    void cleanup();

private:
    enum { WIDTH = 800, HEIGHT = 600 };

    const std::vector<const char*> mRequiredValidationLayers = { "VK_LAYER_KHRONOS_validation" };

    GLFWwindow *mpWindow;
    VkInstance mInstance;
    VkDebugUtilsMessengerEXT mDebugMessenger;
};

