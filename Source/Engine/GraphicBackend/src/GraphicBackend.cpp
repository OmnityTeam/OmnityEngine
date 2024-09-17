#include <map>
#include <GraphicBackend/GraphicBackend.h>

namespace Omnity::Graphic::Backend {
	class GraphicBackendFactoryDict {
		std::map<uint8_t, GraphicBackendFactory> _factories;
	public:
		void inline AddFactory(uint8_t id, GraphicBackendFactory factory) {
			_factories[id] = factory;
		}
		inline const GraphicBackendFactory* GetFactory(uint8_t id) const {
			const auto ret = _factories.find(id);
			return ret == _factories.end() ? nullptr : &ret->second;
		}
	};
	GraphicBackendFactoryDict factoryDict;
	std::unique_ptr<GraphicBackend> currentBackend;

	void RegisterGraphicBackendFactoryImpl(uint8_t id, GraphicBackendFactory factory) {
		factoryDict.AddFactory(id, factory);
	}

	const GraphicBackendFactory& GetGraphicBackendFactory(uint8_t id) {
		return *factoryDict.GetFactory(id);
	}
}