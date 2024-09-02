#include "Logger.h"
#include "OmnityString.h"
#if WIN32
#include <Windows.h>
#include <locale.h>
#endif

namespace Omnity {
	class ConsoleLogSink : public LogSink {
	public:
		ConsoleLogSink() {
#if WIN32
			setlocale(LC_CTYPE, "");
#endif
		}
		void Log(StringRef category, StringRef message) override {
			auto cat = category.AsString();
			auto msg = message.AsString();
#if WIN32
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD n_written;
			WriteConsoleW(handle, L"[", 1, &n_written, NULL);
			WriteConsoleW(handle, cat.CStr(), (DWORD)cat.Length(), &n_written, NULL);
			WriteConsoleW(handle, L"] ", 2, &n_written, NULL);
			WriteConsoleW(handle, msg.CStr(), (DWORD)msg.Length(), &n_written, NULL);
			WriteConsoleW(handle, L"\n", 1, &n_written, NULL);
#else
			wprintf(L"[%ls] %ls", 
				category.GetCStr(),
				message.GetCStr());
#endif
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