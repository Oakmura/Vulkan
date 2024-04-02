#include "Precompiled.h"

#include "Window.h"

Window::Window(int width, int height, const char* name)
    : mWidth(width)
    , mHeight(height)
    , mpWindowName(name)
{
    initWindow();
}

Window::~Window()
{
    glfwDestroyWindow(mpWindow);
    glfwTerminate();
}

void Window::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    mpWindow = glfwCreateWindow(mWidth, mHeight, mpWindowName, nullptr, nullptr);
    glfwSetWindowUserPointer(mpWindow, this);
}