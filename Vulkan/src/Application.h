#pragma once

#include "Window.h"
#include "Device.h"
#include "Pipeline.h"

namespace lve
{
    class Application final
    {
    public:
        Application();
        ~Application() = default;
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        void Run();

    private:
        enum { WIDTH = 800, HEIGHT = 600 };

        Window mWindow;
        Device mDevice;
        Pipeline mPipeline;
    };
}

