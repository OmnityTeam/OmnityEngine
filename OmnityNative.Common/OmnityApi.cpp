#include "Application.h"
#include "OmnityApi.h"

#include <memory>


OMNITY_API_EXPORT void OMNITY_API_METHOD(ObjectRefState, DangerousRelease)
{
	OmnityNative::ObjectRef<OmnityNative::OmnityObject>::DangerousRelease(__ThisRef);
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::UInt OMNITY_API_METHOD(ObjectRefState, GetRefCount)
{
	return __ThisRef->count;
}