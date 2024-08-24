#include "Core.h"

#if WIN32
#define OMNITY_API extern "C" __declspec(dllexport)
#else
#error TODO...
#endif

OMNITY_API void OmnityMain(int argc, char* argv[])
{
	Application app;
	app.Run();
}