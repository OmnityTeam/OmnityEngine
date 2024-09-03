#pragma once
#include <memory>
#include <vector>
#include "OmnityTypes.h"

namespace Omnity {
	class LogSink {
	public:
		virtual void Log(StringRef category, StringRef message) = 0;
		virtual ~LogSink() = default;
	};
	class Logger final {
		std::vector<std::unique_ptr<LogSink>> _logSinks;
		Logger();
		Logger(const Logger&) = delete;
		Logger(const Logger&&) = delete;
		Logger& operator =(const Logger& str) = delete;
		~Logger();
		static Logger& GetInstance();
	public:
		static void Log(StringRef category, StringRef message);
		template <class T, typename... Args>
		static void AddLogSink(Args... args) {
			GetInstance()._logSinks.emplace_back(std::unique_ptr<LogSink>(static_cast<LogSink*>(new T(args...))));
		}
		static void LogInfo(StringRef message) {
			Log(u"Info", message);
		}
	};
}