#include "OmnityApi.h"
#include "Graphic.h"
#include <exception>
#ifdef OMNITY_USE_VULKAN
#include "Graphic.Vulkan.h"
#endif

OMNITY_BEGIN

GraphicContext::GraphicContext(GraphicApi api)
{
	switch (api)
	{
#ifdef OMNITY_USE_VULKAN
	case GraphicApi::Vulkan:
		_device = ObjectRef<VkGpuDevice>::New().CastTo<IGpuDevice>();
		break;
#endif

	default:
		throw new std::exception();
	}
}

ObjectRef<IIndexBuffer> GraphicContext::CreateIndexBuffer(int size)
{
	return _device->CreateIndexBuffer(size);
}

OMNITY_END

OMNITY_API_EXPORT OMNITY_API_CTOR(GraphicContext, OMNITY_NAMESPACE::GraphicApi api)
{
	return OMNITY_API_CTOR_CREATE_OBJECT(GraphicContext, api);
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::CObjectRef* OMNITY_API_METHOD(GraphicContext, CreateIndexBuffer, OMNITY_NAMESPACE::UInt size)
{
	OMNITY_DEFINE_THIS(GraphicContext);
	return This->CreateIndexBuffer(size).RequireManagedRef();
}

OMNITY_API_EXPORT OMNITY_NAMESPACE::UInt OMNITY_API_METHOD(IndexBuffer, GetSize)
{
	OMNITY_DEFINE_THIS(IIndexBuffer);
	return This->GetSize();
}