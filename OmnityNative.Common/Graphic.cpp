#include "OmnityApi.h"
#include "Graphic.h"

OMNITY_BEGIN



OMNITY_END

OMNITY_API_EXPORT OMNITY_NAMESPACE::UShort OMNITY_API_METHOD(Graphic, Init, OMNITY_NAMESPACE::GraphicApi api)
{
	OMNITY_DEFINE_THIS(Graphic);
	return This->Init(api);
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::CObjectRef OMNITY_API_METHOD(Graphic, CreateBuffer)
{
	OMNITY_DEFINE_THIS(Graphic);
	return This->CreateBuffer().RequireManagedRef();
}
