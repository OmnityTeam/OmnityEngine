#include <map>
#include "Rhi.h"

class RhiFactoryDict
{
	std::map<short, RhiFactory> _factories;
public:
	void inline AddFactory(int id, RhiFactory factory)
	{
		_factories[id] = factory;
	}
	auto GetFirstFactory()
	{
		return _factories.begin();
	}
};
RhiFactoryDict factoryDict;
std::unique_ptr<Rhi> currentRhi;

void RegisterRhiFactoryImpl(int id, RhiFactory factory)
{
	factoryDict.AddFactory(id, factory);
}

std::map<short, RhiFactory>::iterator EnumRhiFactory()
{
	return factoryDict.GetFirstFactory();
}

void Rhi::Test()
{

}