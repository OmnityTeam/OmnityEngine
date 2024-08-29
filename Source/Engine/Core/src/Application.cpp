#include "OmnityTypes.h"
#include <vector>
#include "Core.h"
#include "Graphic.h"
#include "Logger.h"
#include "OmnityString.h"

namespace Omnity::Core {
	void Application::Run(int argc, const char* argv[]) {
		std::vector<String> args;
		for (int i = 1; i < argc; ++i)
			args.push_back(String(argv[i]));
		Logger::LogInfo(L"Started!🌹");
		Logger::LogInfo(L"Started!2");
		for (const auto& arg : args)
			Logger::LogInfo(arg);
		Omnity::Graphic::InitGraphic();
		Omnity::Graphic::SetupGraphicBackend();
	}
}