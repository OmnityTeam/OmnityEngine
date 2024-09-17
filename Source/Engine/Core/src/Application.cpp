#include <Base/OmnityTypes.h>
#include <vector>
#include <Core/Core.h>
#include <Graphic/Graphic.h>
#include <Base/Logger.h>
#include <Base/OmnityString.h>

#include <chrono>
#include <iostream>

namespace Omnity::Core {
	void Setup(const std::vector<std::u16string>& args) {
		auto str = std::u16string(u"12🌹34");
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
		std::vector<std::u16string> args;
		for (int i = 0; i < argc; ++i)
			args.emplace_back(std::u16string(StringUtils::FromUtf8Ptr(argv[i])));
		Setup(args);
	}
	void Application::Run(int argc, const char16_t* argv[]) {
		std::vector<std::u16string> args;
		for (int i = 0; i < argc; ++i)
			args.emplace_back(std::u16string(argv[i]));
		Setup(args);
	}

	Application::~Application() {
	}
}