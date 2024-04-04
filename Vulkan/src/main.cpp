#include "Precompiled.h"

#include "TriangleApp.h"

int main()
{
    lve::Logger::Init();

    lve::TriangleApp app;

    app.Run();

    return EXIT_SUCCESS;
}