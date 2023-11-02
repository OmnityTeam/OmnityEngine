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

Application::Application()
{

}

OMNITY_END

OMNITY_API_EXPORT OMNITY_API_CTOR(Application)
{
	return OMNITY_API_CTOR_CREATE_OBJECT(Application);
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::ULong OMNITY_API_METHOD(Application, GetEngineVersion)
{
	OMNITY_DEFINE_THIS(Application);
	return This->GetEngineVersion();
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::UShort OMNITY_API_METHOD(Application, GetPlatformId)
{
	OMNITY_DEFINE_THIS(Application);
	return This->GetPlatformId();
}
