#pragma once
#include "OmnityApi.h"

OMNITY_BEGIN

class Graphic;

class Application
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