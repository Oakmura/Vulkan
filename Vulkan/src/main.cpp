#include "Precompiled.h"

#include "TriangleApp.h"

int main()
{
#ifdef _DEBUG
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    lve::Logger::Init();

    lve::TriangleApp app;

    app.Run();

    return EXIT_SUCCESS;
}