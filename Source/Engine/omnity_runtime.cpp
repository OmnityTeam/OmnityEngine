#include <core/core.h>
#if WIN32
#define OMNITY_API extern "C" __declspec(dllexport)
#else
#define OMNITY_API extern "C" __attribute__ ((visibility("default")))
#endif

OMNITY_API int omnity_main(const int argc, const char* argv[]) {
    omnity::core::application::run(argc, argv);
    return 0;
}

OMNITY_API int w_omnity_main(const int argc, const char16_t* argv[]) {
    omnity::core::application::run(argc, argv);
    return 0;
}