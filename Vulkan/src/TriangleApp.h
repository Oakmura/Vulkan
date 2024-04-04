#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace lve
{
    class TriangleApp final
    {
    public:
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

    public:
        TriangleApp() = default;
        ~TriangleApp() = default;
        TriangleApp(const TriangleApp& rhs) = delete;
        TriangleApp& operator=(const TriangleApp& rhs) = delete;

    public:
        void Run();

    private:
        void initWindow();

        void initVulkan();

        void createInstance();
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();

        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);


        void mainLoop();
        void cleanup();



    private:
        enum { WIDTH = 800, HEIGHT = 600 };

#ifdef NDEBUG
        const bool mbEnableValidationLayers = false;
#else
        const bool mbEnableValidationLayers = true;
#endif

        const char* mpValidationLayers[1] = { "VK_LAYER_KHRONOS_validation" };

        GLFWwindow* mpWindow;

        VkInstance mInstance;
        VkDebugUtilsMessengerEXT mDebugMessenger;
        


    };
} // namespace lve