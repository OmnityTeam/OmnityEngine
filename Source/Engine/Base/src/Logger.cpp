#include <Base/Logger.h>
#include <Base/OmnityString.h>
#if WIN32
#include <Windows.h>
#include <locale.h>
#include <iostream>
#endif

namespace Omnity {
	class ConsoleLogSink : public LogSink {
		inline void Print(std::u16string_view str) {
			//std::u16string s = fmt::format(u"{The answer is {}.}", 42);
#if WIN32
			WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str.data(), (DWORD)str.length(), nullptr, nullptr);
#else
			Words words(str);
			for (const auto& word : words)
				putwchar((wchar_t)word);
#endif
		}
	public:
		ConsoleLogSink() {
			setlocale(LC_CTYPE, "");
		}
		void Log(std::u16string_view category, std::u16string_view message) override {
			Print(u"[");
			Print(category);
			Print(u"] ");
			Print(message);
			Print(u"\n");
		}
		~ConsoleLogSink() {}
	}; 
	Logger::Logger() {
		_logSinks.emplace_back(std::make_unique<ConsoleLogSink>());
	}
	Logger::~Logger() = default;
	inline Logger& Logger::GetInstance() {
		static Logger logger;
		return logger;
	}
	void Logger::Log(std::u16string_view category, std::u16string_view message) {
		for (const auto& sink : GetInstance()._logSinks)
			sink->Log(category, message);
	}
}