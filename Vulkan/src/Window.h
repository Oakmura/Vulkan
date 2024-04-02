#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Window final
{
public:
    Window() = delete;
    Window(int width, int height, const char* name);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    inline bool ShouldClose() { return glfwWindowShouldClose(mpWindow); }

private:
    int mWidth;
    int mHeight;

    GLFWwindow* mpWindow;
    const char* mpWindowName;
};

