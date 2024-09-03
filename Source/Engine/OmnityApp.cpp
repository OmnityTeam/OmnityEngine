#if WIN32
#define OMNITY_API extern "C" __declspec(dllimport)
#else
#define OMNITY_API extern "C"
#endif
OMNITY_API int OmnityMain(int argc, const char* argv[]);
OMNITY_API int WOmnityMain(int argc, const char16_t* argv[]);

#if WIN32
#pragma runtime_checks("", off)
extern "C" {
#include <Windows.h>
	int __stdcall main() {
		LPWSTR cmdLine = GetCommandLineW();
		int argc;
		LPWSTR* argv = CommandLineToArgvW(cmdLine, &argc);
		return WOmnityMain(argc, (const char16_t**)argv);
	}
}
#else
int main(int argc, const char* argv[]) {
	OmnityMain(argc, argv);
}
#endif