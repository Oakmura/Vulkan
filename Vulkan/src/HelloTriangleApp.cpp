#include "Precompiled.h"

#include "HelloTriangleApp.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

void HelloTriangleApp::run() 
{
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void HelloTriangleApp::initWindow() 
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    mWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void HelloTriangleApp::initVulkan() 
{
    createInstance();
}

void HelloTriangleApp::createInstance() 
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // query available extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions:\n";
    for (const auto& extension : extensions) 
    {
        std::cout << '\t' << extension.extensionName << '\n';
    }

    // register required extensions
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> requiredExtensions;
    requiredExtensions.reserve(glfwExtensionCount + 1);
    for (uint32_t i = 0; i < glfwExtensionCount; i++)
    {
        requiredExtensions.emplace_back(glfwExtensions[i]);
    }
    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME); // for Mac portability
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    // validation layers
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &mInstance) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create instance!");
    }
}

void HelloTriangleApp::mainLoop() 
{
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
    }
}

void HelloTriangleApp::cleanup() 
{
    vkDestroyInstance(mInstance, nullptr);

    glfwDestroyWindow(mWindow);

    glfwTerminate();
}
