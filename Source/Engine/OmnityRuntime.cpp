#include <Core/Core.h>
#if WIN32
#define OMNITY_API extern "C" __declspec(dllexport)
#else
#define OMNITY_API extern "C" __attribute__ ((visibility("default")))
#endif

OMNITY_API int OmnityMain(int argc, const char* argv[]) {
	Omnity::Core::Application app;
	app.Run(argc, argv);
	return 0;
}

OMNITY_API int WOmnityMain(int argc, const char16_t* argv[]) {
	Omnity::Core::Application app;
	app.Run(argc, argv);
	return 0;
}