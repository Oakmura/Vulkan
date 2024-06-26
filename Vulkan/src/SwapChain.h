#pragma once

#include "Device.h"

// vulkan headers
#include <vulkan/vulkan.h>

namespace lve
{
    class SwapChain final
    {
    public:
        SwapChain() = delete;
        SwapChain(Device& deviceRef, VkExtent2D windowExtent);
        SwapChain(Device &deviceRef, VkExtent2D windowExtent, std::shared_ptr<SwapChain> previous);
        ~SwapChain();
        SwapChain(const SwapChain& rhs) = delete;
        SwapChain& operator=(const SwapChain& rhs) = delete;

        VkFramebuffer GetFrameBuffer(int index) { return mSwapChainFramebuffers[index]; }
        VkRenderPass GetRenderPass() { return mRenderPass; }
        VkImageView GetImageView(int index) { return mSwapChainImageViews[index]; }
        size_t GetImageCount() { return mSwapChainImages.size(); }
        VkFormat GetSwapChainImageFormat() { return mSwapChainImageFormat; }

        VkExtent2D GetSwapChainExtent() { return mSwapChainExtent; }
        uint32_t GetWidth() { return mSwapChainExtent.width; }
        uint32_t GetHeight() { return mSwapChainExtent.height; }
        float GetExtentAspectRatio() { return static_cast<float>(mSwapChainExtent.width) / static_cast<float>(mSwapChainExtent.height); }
        VkFormat FindDepthFormat();

        VkResult AcquireNextImage(uint32_t *imageIndex);
        VkResult SubmitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

    private:
        void init();

        void createSwapChain();
        void createImageViews();
        void createDepthResources();
        void createRenderPass();
        void createFramebuffers();
        void createSyncObjects();

        // Helper functions
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    private:
        enum { MAX_FRAMES_IN_FLIGHT = 2 };

        Device& mDevice;

        VkSwapchainKHR mSwapChain;
        std::shared_ptr<SwapChain> mOldSwapChain;

        VkExtent2D mWindowExtent;
        VkExtent2D mSwapChainExtent;
        VkFormat mSwapChainImageFormat;

        VkRenderPass mRenderPass;
        std::vector<VkImage> mSwapChainImages;
        std::vector<VkImageView> mSwapChainImageViews;
        std::vector<VkFramebuffer> mSwapChainFramebuffers;
        std::vector<VkImage> mDepthImages;
        std::vector<VkDeviceMemory> mDepthImageMemorys;
        std::vector<VkImageView> mDepthImageViews;

        std::vector<VkSemaphore> mImageAvailableSemaphores;
        std::vector<VkSemaphore> mRenderFinishedSemaphores;
        std::vector<VkFence> mInFlightFences;
        std::vector<VkFence> mImagesInFlight;
        size_t mCurrentFrame = 0;
    };

} // namespace lve