#include "Application.h"
#include "OmnityApi.h"
#include "Graphic.h"

OMNITY_BEGIN

ULong Application::GetEngineVersion()
{
	return OMNITY_VERSION;
}

UShort Application::GetPlatformId()
{
	return OMNITY_PLATFORM_ID;
}

OMNITY_END

OMNITY_API_EXPORT OMNITY_NAMESPACE::ULong OMNITY_API_STATIC_METHOD(Application, GetEngineVersion)
{
	return OMNITY_NAMESPACE::Application::GetEngineVersion();
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::UShort OMNITY_API_STATIC_METHOD(Application, GetPlatformId)
{
	return OMNITY_NAMESPACE::Application::GetPlatformId();
}
