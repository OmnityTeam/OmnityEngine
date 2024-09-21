#define OMNITY_API extern "C"
OMNITY_API int omnity_main(int argc, const char* argv[]);
OMNITY_API int w_omnity_main(int argc, const char16_t* argv[]);

int main(const int argc, const char* argv[]) {
    return omnity_main(argc, argv);
}