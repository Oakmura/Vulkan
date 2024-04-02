#include "Precompiled.h"

#include "Application.h"

int main()
{
    lve::Logger::Init();
    lve::Application app;

    app.Run();

    return EXIT_SUCCESS;
}