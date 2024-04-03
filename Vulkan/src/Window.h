#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace lve
{
    class Window final
    {
    public:
        Window() = delete;
        Window(int width, int height, const char* name);
        ~Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

    public:
        inline bool ShouldClose() { return glfwWindowShouldClose(mpWindow); }
        inline VkExtent2D GetExtent() { return { static_cast<uint32_t>(mWidth), static_cast<uint32_t>(mHeight) }; }
        inline bool WasWindowResized() { return mbFramebufferResized; }
        inline void ResetWindowResizedFlag() { mbFramebufferResized = false; }

        void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

    private:
        static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

    private:
        int mWidth;
        int mHeight;
        bool mbFramebufferResized;

        GLFWwindow* mpWindow;
        const char* mpWindowName;
    };
}