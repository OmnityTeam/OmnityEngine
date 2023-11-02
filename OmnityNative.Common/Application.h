#pragma once
#include "OmnityApi.h"

OMNITY_BEGIN

class Graphic;

class Application : OmnityObject
{
public:
	static UShort GetPlatformId();
	static ULong GetEngineVersion();

	Application() = delete;

	virtual ~Application()
	{
	}
};

OMNITY_END