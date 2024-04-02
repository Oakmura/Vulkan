#include "Precompiled.h"

#include "Window.h"

namespace lve
{
    Window::Window(int width, int height, const char* name)
        : mWidth(width)
        , mHeight(height)
        , mpWindowName(name)
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        mpWindow = glfwCreateWindow(mWidth, mHeight, mpWindowName, nullptr, nullptr);
    }

    void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
    {
        VK_ASSERT(glfwCreateWindowSurface(instance, mpWindow, nullptr, surface), "glfwCreateWindowSurface() : Failed to create window surface")
    }

    Window::~Window()
    {
        glfwDestroyWindow(mpWindow);
        glfwTerminate();
    }
}