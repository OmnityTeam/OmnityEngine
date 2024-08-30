#include "OmnityTypes.h"
#include <vector>
#include "Core.h"
#include "Graphic.h"
#include "Logger.h"
#include "OmnityString.h"

namespace Omnity::Core {
	void Setup(const std::vector<ImmutableString>& args) {

		String str(u"1234");
		auto sub = str.SubString(1, 2);
		auto dymn = sub.ToDynamic();

		Logger::LogInfo(u"Started!🌹");
		Logger::LogInfo(u"Started!2");
		for (const auto& arg : args)
			Logger::LogInfo(arg);
		Omnity::Graphic::InitGraphic();
		Omnity::Graphic::SetupGraphicBackend();
	}
	void Application::Run(int argc, const char* argv[]) {
		std::vector<ImmutableString> args;
		for (int i = 0; i < argc; ++i)
			args.emplace_back(String(argv[i]));
		Setup(args);
	}
	void Application::Run(int argc, const char16_t* argv[]) {
		std::vector<ImmutableString> args;
		for (int i = 0; i < argc; ++i)
		{
			String str(argv[i]);
			args.emplace_back(std::move(str));
		}
		Setup(args);
	}
}