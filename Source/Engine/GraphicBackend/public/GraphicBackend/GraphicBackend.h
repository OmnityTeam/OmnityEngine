#pragma once
#include <concepts>
#include <type_traits>
#include <functional>
#include <memory>
#include <map>

namespace Omnity::Graphic::Backend {
	class GraphicContext;
	class GraphicBackend;

	class GraphicBackend {
	public:
		virtual bool Setup() = 0;
		virtual std::weak_ptr<GraphicContext> GetContext() = 0;
		virtual ~GraphicBackend() = default;
	};
	class GraphicContext {
	public:
		virtual bool SetupContext() = 0;
		virtual ~GraphicContext() = default;
	};

	using GraphicBackendFactory = std::function<std::unique_ptr<GraphicBackend>()>;
	void RegisterGraphicBackendFactoryImpl(uint8_t id, GraphicBackendFactory factory);
	template<class T>
	concept GraphicBackendType = std::is_base_of_v<GraphicBackend, T>;
	template<short id, GraphicBackendType T, typename ...Args>
	void RegisterGraphicBackend(Args... args) {
		RegisterGraphicBackendFactoryImpl(id,
			[&args...]()
			{
				return std::unique_ptr<GraphicBackend>(static_cast<GraphicBackend*>(new T(args...)));
			});
	}

	const GraphicBackendFactory& GetGraphicBackendFactory(uint8_t id);
}