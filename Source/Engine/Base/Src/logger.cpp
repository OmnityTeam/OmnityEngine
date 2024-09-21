#include <base/logger.h>
#include <base/omnity_string.h>
#if WIN32
#include <Windows.h>
#include <clocale>
#include <iostream>
#endif

namespace omnity {
    class console_log_sink final : public log_sink {
        inline static void print(std::u16string_view str) {
            //std::u16string s = fmt::format(u"{The answer is {}.}", 42);
#if WIN32
            WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str.data(), static_cast<DWORD>(str.length()), nullptr, nullptr);
#else
            Words words(str);
            for (const auto& word : words)
                putwchar((wchar_t)word);
#endif
        }
    public:
        console_log_sink(console_log_sink&) = delete;
        console_log_sink(console_log_sink&&) = delete;
        console_log_sink& operator =(console_log_sink& str) = delete;
        console_log_sink& operator =(console_log_sink&& str) = delete;
        console_log_sink() {
            std::setlocale(LC_CTYPE, "");
        }
        void log(const std::u16string_view category, const std::u16string_view message) override {
            print(u"[");
            print(category);
            print(u"] ");
            print(message);
            print(u"\n");
        }
        ~console_log_sink() override {}
    };
    logger::logger() {
        log_sinks_.emplace_back(std::make_unique<console_log_sink>());
    }
    logger::~logger() = default;
    inline logger& logger::get_instance() {
        static logger logger;
        return logger;
    }
    void logger::log(const std::u16string_view category, const std::u16string_view message) {
        for (const auto& sink : get_instance().log_sinks_)
            sink->log(category, message);
    }
}