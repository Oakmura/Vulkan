#include "Precompiled.h"

#include "TriangleApp.h"

namespace lve
{
    void TriangleApp::Run()
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
        createInstance();
    }

    void TriangleApp::createInstance()
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

        // global extensions. VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR flag + PORTABILITY extension on MAC
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        LOG_INFO("-----GLFW Required Extensions-----");
        for (uint32_t i = 0; i < glfwExtensionCount; ++i)
        {
            LOG_INFO("{0}", glfwExtensions[i]);
        }
        printf("\n");

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        VkExtensionProperties* extensions = new VkExtensionProperties[extensionCount];
        {
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions);
            LOG_INFO("-----Available Required Extensions-----");
            for (uint32_t i = 0; i < extensionCount; ++i)
            {
                LOG_INFO("{0}", extensions[i].extensionName);
            }
            printf("\n");
        }
        delete extensions;

        // global validation layers
        createInfo.enabledLayerCount = 0;

        VK_ASSERT(vkCreateInstance(&createInfo, nullptr, &mInstance), "vkCreateInstance() : failed to create VkInstance")
    }

    void TriangleApp::mainLoop()
    {
        while (!glfwWindowShouldClose(mpWindow))
        {
            glfwPollEvents();
        }
    }

    void TriangleApp::cleanup()
    {
        vkDestroyInstance(mInstance, nullptr);

        glfwDestroyWindow(mpWindow);

        glfwTerminate();
    }
} // namespace lve