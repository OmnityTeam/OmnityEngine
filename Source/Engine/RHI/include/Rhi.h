#pragma once
#include <concepts>
#include <type_traits>
#include <functional>
#include <memory>
#include <map>

class Rhi
{
public:
	void Test();
	virtual ~Rhi() = default;
};

using RhiFactory = std::function<std::unique_ptr<Rhi>()>;

void RegisterRhiFactoryImpl(int id, RhiFactory factory);

template<class T>
concept RhiImplType = std::is_base_of_v<Rhi, T>;

template<short id, RhiImplType T, typename ...Args>
void RegisterRhiImpl(Args... args)
{
	RegisterRhiFactoryImpl(id,
		[&args...]()
		{
			return std::unique_ptr<Rhi>((Rhi*)new T(args...));
		});
}

std::map<short, RhiFactory>::iterator EnumRhiFactory();