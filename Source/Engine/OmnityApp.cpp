#define OMNITY_API extern "C"
OMNITY_API int OmnityMain(int argc, const char* argv[]);
OMNITY_API int WOmnityMain(int argc, const char16_t* argv[]);

int main(int argc, const char* argv[]) {
	return OmnityMain(argc, argv);
}