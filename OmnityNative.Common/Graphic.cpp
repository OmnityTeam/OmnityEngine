#include "OmnityApi.h"
#include "Graphic.h"

OMNITY_BEGIN


OMNITY_END

OMNITY_API_EXPORT OMNITY_API_CTOR(Graphic, OMNITY_NAMESPACE::GraphicApi api)
{
	return OMNITY_API_CTOR_CREATE_OBJECT(Graphic, api);
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::CObjectRef OMNITY_API_METHOD(Graphic, CreateBuffer)
{
	OMNITY_DEFINE_THIS(Graphic);
	return This->CreateBuffer().RequireManagedRef();
}
