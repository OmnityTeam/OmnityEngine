#if WIN32
#define OMNITY_API extern "C" __declspec(dllimport)
#else
#error TODO...
#endif
OMNITY_API int OmnityMain(int argc, const char* argv[]);
OMNITY_API int WOmnityMain(int argc, const wchar_t* argv[]);

#if WIN32
#pragma runtime_checks("", off)
extern "C" {
#include <Windows.h>
	int __stdcall main() {
		LPWSTR cmdLine = GetCommandLineW();
		int argc;
		LPWSTR* argv = CommandLineToArgvW(cmdLine, &argc);
		return WOmnityMain(argc, (const wchar_t**)argv);
	}
}
#else
int main(int argc, const char* argv[]) {
	OmnityMain(argc, argv);
}
#endif