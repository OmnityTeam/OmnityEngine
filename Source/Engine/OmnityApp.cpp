#if WIN32
#define OMNITY_API extern "C" __declspec(dllimport)
#else
#error TODO...
#endif
OMNITY_API void OmnityMain(int argc, char* argv[]);
int main(int argc, char* argv[])
{
	OmnityMain(argc, argv);
}