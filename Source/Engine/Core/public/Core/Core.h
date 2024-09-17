#pragma once

namespace Omnity::Core {
	class Application {
	public:
		void Run(int argc, const char* argv[]);
		void Run(int argc, const char16_t* argv[]);
		~Application();
	};
}