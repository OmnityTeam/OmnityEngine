#include "Core.h"

#if WIN32
#define OMNITY_API extern "C" __declspec(dllexport)
#else
#error TODO...
#endif

OMNITY_API void OmnityMain(int argc, const char* argv[]) {
	Omnity::Core::Application app;
	app.Run(argc, argv);
}