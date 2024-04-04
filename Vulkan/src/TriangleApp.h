#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace lve
{
    class TriangleApp final
    {
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


        void mainLoop();
        void cleanup();



    private:
        enum { WIDTH = 800, HEIGHT = 600 };

        GLFWwindow* mpWindow;
        VkInstance mInstance;
    };
} // namespace lve