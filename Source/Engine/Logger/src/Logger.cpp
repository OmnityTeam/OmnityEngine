#include "Logger.h"
#include "OmnityString.h"
#if WIN32
#include <Windows.h>
#include <locale.h>
#include <iostream>
#endif

namespace Omnity {
	class ConsoleLogSink : public LogSink {
		inline void PrintW(StringRef str) {
#if WIN32
			WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str.data(), (DWORD)str.length(), nullptr, nullptr);
#else
			for (auto iter = str.WordBegin(); iter != str.WordEnd(); ++iter) {
				putwchar((wchar_t)*iter);
			}
#endif
		}
	public:
		ConsoleLogSink() {
			setlocale(LC_CTYPE, "");
		}
		void Log(StringRef category, StringRef message) override {
			PrintW(u"[");
			PrintW(category);
			PrintW(u"] ");
			PrintW(message);
			PrintW(u"\n");
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
	void Logger::Log(StringRef category, StringRef message) {
		for (const auto& sink : GetInstance()._logSinks)
			sink->Log(category, message);
	}
}