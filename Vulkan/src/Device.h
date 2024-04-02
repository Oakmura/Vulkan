#pragma once

#include "Window.h"

namespace lve 
{
    struct SwapChainSupportDetails 
    {
        VkSurfaceCapabilitiesKHR Capabilities;
        std::vector<VkSurfaceFormatKHR> Formats;
        std::vector<VkPresentModeKHR> PresentModes;
    };

    struct QueueFamilyIndices 
    {
        bool isComplete() { return GraphicsFamilyHasValue && PresentFamilyHasValue; }

        uint32_t GraphicsFamily;
        uint32_t PresentFamily;
        bool GraphicsFamilyHasValue = false;
        bool PresentFamilyHasValue = false;
    };

    class Device final
    {
    public:
        Device(Window& window);
        ~Device();
        Device(const Device&) = delete;
        Device& operator=(const Device&) = delete;
        Device(Device&&) = delete;
        Device& operator=(Device&&) = delete;

        inline VkDevice Get() { return mDevice; }
        inline VkCommandPool GetCommandPool() { return mCommandPool; }
        inline VkSurfaceKHR GetSurface() { return mSurface; }
        inline VkQueue GetGraphicsQueue() { return mGraphicsQueue; }
        inline VkQueue GetPresentQueue() { return mPresentQueue; }

        inline SwapChainSupportDetails GetSwapChainSupport() { return querySwapChainSupport(mPhysicalDevice); }
        inline QueueFamilyIndices FindPhysicalQueueFamilies() { return findQueueFamilies(mPhysicalDevice); }
        uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        // Buffer Helper Functions
        VkCommandBuffer BeginSingleTimeCommands();
        void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
        void CreateBuffer(VkDeviceSize size,VkBufferUsageFlags usage,VkMemoryPropertyFlags properties,VkBuffer& buffer,VkDeviceMemory& bufferMemory);
        void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);
        void CreateImageWithInfo(const VkImageCreateInfo& imageInfo,VkMemoryPropertyFlags properties,VkImage& image,VkDeviceMemory& imageMemory);

    private:
        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createCommandPool();

        bool isDeviceSuitable(VkPhysicalDevice device);
        std::vector<const char*> getRequiredExtensions();
        bool checkValidationLayerSupport();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void hasGflwRequiredInstanceExtensions();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    private:
#ifdef NDEBUG
        const bool mbEnableValidationLayers = false;
#else
        const bool mbEnableValidationLayers = true;
#endif
        const std::vector<const char*> mDeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
        const std::vector<const char*> mValidationLayers = { "VK_LAYER_KHRONOS_validation" };

        VkInstance mInstance;
        VkDebugUtilsMessengerEXT mDebugMessenger;
        VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceProperties properties;
        Window& mWindow;
        VkCommandPool mCommandPool;

        VkDevice mDevice;
        VkSurfaceKHR mSurface;
        VkQueue mGraphicsQueue;
        VkQueue mPresentQueue;
    };
}  // namespace lve