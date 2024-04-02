#pragma once

#include "Window.h"

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
};

