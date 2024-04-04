#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class TriangleApp final
{
public:
    TriangleApp() = default;
    ~TriangleApp() = default;
    TriangleApp(const TriangleApp& rhs) = delete;
    TriangleApp& operator=(const TriangleApp& rhs) = delete;

public:
    Run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

private:
    enum { WIDTH = 800, HEIGHT = 600 };

    GLFWwindow* mpWindow;
};
