#include "OmnityTypes.h"
#include <vector>
#include "Core.h"
#include "Graphic.h"
#include "Logger.h"
#include "OmnityString.h"

#include <chrono>
#include <iostream>

namespace Omnity::Core {
	void Setup(const std::vector<String>& args) {
		auto str = String(u"12🌹34");
		auto str2 = std::move(str);
		auto str3 = str2;
		Logger::LogInfo(str2);
		Logger::LogInfo(str3.substr(1, 3));
		Logger::LogInfo(u"🌹Started!");
		Logger::LogInfo(u"Started!2");
		for (const auto& arg : args)
			Logger::LogInfo(arg);
		Omnity::Graphic::InitGraphic();
		Omnity::Graphic::SetupGraphicBackend();
	}
	void Application::Run(int argc, const char* argv[]) {
		std::vector<String> args;
		for (int i = 0; i < argc; ++i)
			args.emplace_back(String(argv[i]));
		Setup(args);
	}
	void Application::Run(int argc, const char16_t* argv[]) {
		std::vector<String> args;
		for (int i = 0; i < argc; ++i)
			args.emplace_back(String(argv[i]));
		Setup(args);
	}
}