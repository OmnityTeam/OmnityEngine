#include "Application.h"
#include "OmnityApi.h"
#include "Graphic.h"

OMNITY_BEGIN

Bool Application::Init()
{
	return true;
}

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
	graphic = ObjectRef(new Graphic());
}

OMNITY_END

OMNITY_API_EXPORT OMNITY_API_CTOR(Application)
{
	return OMNITY_API_CTOR_CREATE_OBJECT(Application);
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::Bool OMNITY_API_METHOD(Application, Init)
{
	OMNITY_DEFINE_THIS(Application);
	return This->Init();
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

OMNITY_API_EXPORT OMNITY_NAMESPACE::CObjectRef OMNITY_API_METHOD(Application, GetGraphic)
{
	OMNITY_DEFINE_THIS(Application);
	return This->graphic.RequireManagedRef();
}
