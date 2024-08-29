#include "OmnityTypes.h"
#include <vector>
#include "Core.h"
#include "Graphic.h"
#include "Logger.h"
#include "OmnityString.h"

namespace Omnity::Core {
	void Setup(const std::vector<String>& args) {

		Logger::LogInfo(L"Started!🌹");
		Logger::LogInfo(L"Started!2");
		for (const auto& arg : args)
			Logger::LogInfo(arg);
		Omnity::Graphic::InitGraphic();
		Omnity::Graphic::SetupGraphicBackend();
	}
	void Application::Run(int argc, const char* argv[]) {
		std::vector<String> args;
		for (int i = 0; i < argc; ++i)
			args.push_back(String(argv[i]));
		Setup(args);
	}
	void Application::Run(int argc, const wchar_t* argv[]) {
		std::vector<String> args;
		for (int i = 0; i < argc; ++i)
			args.push_back(String(argv[i]));
		Setup(args);
	}
}