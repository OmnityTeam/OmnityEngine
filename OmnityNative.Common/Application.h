#pragma once
#include "OmnityApi.h"

OMNITY_BEGIN

class Graphic;

class Application : OmnityObject
{
public:
	UShort GetPlatformId();
	ULong GetEngineVersion();

	Application();

	virtual ~Application()
	{
	}
};

OMNITY_END