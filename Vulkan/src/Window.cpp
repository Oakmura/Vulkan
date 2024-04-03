#include "Precompiled.h"

#include "Window.h"

namespace lve
{
Window::Window(int width, int height, const char *name) 
    : mWidth(width)
    , mHeight(height)
    , mbFramebufferResized(false)
    , mpWindowName(name)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    mpWindow = glfwCreateWindow(mWidth, mHeight, mpWindowName, nullptr, nullptr);
}

void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
{
    VK_ASSERT(glfwCreateWindowSurface(instance, mpWindow, nullptr, surface), "glfwCreateWindowSurface() : Failed to create window surface")
    glfwSetWindowUserPointer(mpWindow, this);
    glfwSetFramebufferSizeCallback(mpWindow, framebufferResizeCallback);
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) 
{
    Window* myWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    myWindow->mbFramebufferResized = true;
    myWindow->mWidth = width;
    myWindow->mHeight = height;
}

Window::~Window()
{
    glfwDestroyWindow(mpWindow);
    glfwTerminate();
}
} // namespace lve