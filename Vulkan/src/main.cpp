#include "Precompiled.h"

#include "Application.h"

int main()
{
    Logger::Init();
    lve::Application app;

    app.Run();

    return EXIT_SUCCESS;
}