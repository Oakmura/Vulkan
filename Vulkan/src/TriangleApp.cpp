#include "Precompiled.h"

#include "TriangleApp.h"

namespace lve
{
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL TriangleApp::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
    {
        LOG_INFO("validation layer: {0}", pCallbackData->pMessage);

        return VK_FALSE;
    }

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
        setupDebugMessenger();
    }

    void TriangleApp::createInstance()
    {
        ASSERT(mbEnableValidationLayers && checkValidationLayerSupport(), "Validation layer is not supported")

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

        // required global extensions.
        std::vector<const char*> extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        // available global extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

        LOG_INFO("-----Available Required Extensions-----");
        for (const auto& availableExtension : availableExtensions)
        {
            LOG_TRACE("{0}", availableExtension.extensionName);
        }
        printf("\n");

        // required global validation layers
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (mbEnableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(ARRAY_SIZE(mpValidationLayers));
            createInfo.ppEnabledLayerNames = mpValidationLayers;

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VK_ASSERT(vkCreateInstance(&createInfo, nullptr, &mInstance), "vkCreateInstance() : failed to create VkInstance")
    }

    bool TriangleApp::checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        LOG_INFO("-----Available Validation Layers-----");
        for (const auto& availableLayer : availableLayers)
        {
            LOG_TRACE("{0}", availableLayer.layerName);
        }
        printf("\n");

        for (const char* layerName : mpValidationLayers)
        {
            bool bLayerFound = false;
            for (const auto& availableLayer : availableLayers)
            {
                if (strcmp(layerName, availableLayer.layerName) == 0)
                {
                    bLayerFound = true;
                    break;
                }
            }

            if (!bLayerFound)
            {
                return false;
            }
        }

        return true;
    }

    std::vector<const char*> TriangleApp::getRequiredExtensions()
    {
        // Enable VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR flag + PORTABILITY extension if on MAC

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        if (mbEnableValidationLayers)
        {
            extensions.push_back("VK_EXT_debug_utils");
        }

        LOG_INFO("-----GLFW Required Extensions-----");
        for (const char* extension : extensions)
        {
            LOG_TRACE("{0}", extension);
        }
        printf("\n");

        return extensions;
    }

    void TriangleApp::setupDebugMessenger()
    {
        if (!mbEnableValidationLayers)
        {
            return;
        }

        VkDebugUtilsMessengerCreateInfoEXT createInfo{}; 
        populateDebugMessengerCreateInfo(createInfo);

        VK_ASSERT(CreateDebugUtilsMessengerEXT(mInstance, &createInfo, nullptr, &mDebugMessenger), "CreateDebugUtilsMessengerEXT() : failed to create debug messenger");
    }

    void TriangleApp::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = DebugCallback;
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
        if (mbEnableValidationLayers)
        {
            DestroyDebugUtilsMessengerEXT(mInstance, mDebugMessenger, nullptr);
        }

        vkDestroyInstance(mInstance, nullptr);

        glfwDestroyWindow(mpWindow);

        glfwTerminate();
    }
} // namespace lve