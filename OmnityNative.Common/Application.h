#pragma once
#include "OmnityApi.h"

OMNITY_BEGIN

class Graphic;

class Application : OmnityObject
{
public:
	Bool Init();
	UShort GetPlatformId();
	ULong GetEngineVersion();

	ObjectRef<Graphic> graphic;

	Application();

	virtual ~Application()
	{
	}
};

OMNITY_END