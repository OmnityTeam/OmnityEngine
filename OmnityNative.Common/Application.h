#pragma once
#include "OmnityApi.h"

OMNITY_BEGIN

class Application : OmnityObject
{
public:
	Bool Init();
	UShort GetPlatformId();
	ULong GetEngineVersion();

	virtual ~Application()
	{
	}
};

OMNITY_END