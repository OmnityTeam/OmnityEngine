#if WIN32
#define OMNITY_API extern "C" __declspec(dllimport)
#else
#error TODO...
#endif
OMNITY_API void OmnityMain(int argc, const char* argv[]);

int main(int argc, const char* argv[]) {
	OmnityMain(argc, argv);
}