#include "Application.h"
#include "OmnityApi.h"

#include <memory>

// Object counter
#ifdef OMNITY_ENABLE_OBJECT_COUNTER
std::atomic<OMNITY_NAMESPACE::ULong> OMNITY_NAMESPACE::OmnityObjectCount = 0;
std::atomic<OMNITY_NAMESPACE::ULong> OMNITY_NAMESPACE::OmnitySharedObjectCount = 0;
#endif

OMNITY_API_EXPORT void OMNITY_API_METHOD(CObjectRef, DangerousRelease)
{
#ifdef OMNITY_ENABLE_OBJECT_COUNTER
	--OMNITY_NAMESPACE::OmnitySharedObjectCount;
#endif
	__ThisRef->release(__ThisRef);
	delete __ThisRef;
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::UInt OMNITY_API_METHOD(CObjectRef, GetRefCount)
{
	return __ThisRef->refInfo->count;
}

#ifdef OMNITY_ENABLE_OBJECT_COUNTER
OMNITY_API_EXPORT OMNITY_NAMESPACE::ULong OMNITY_API_METHOD(CObjectRef, GetTotal)
{
	return OMNITY_NAMESPACE::OmnityObjectCount;
}
OMNITY_API_EXPORT OMNITY_NAMESPACE::ULong OMNITY_API_METHOD(CObjectRef, GetSharedTotal)
{
	return OMNITY_NAMESPACE::OmnitySharedObjectCount;
}
#endif