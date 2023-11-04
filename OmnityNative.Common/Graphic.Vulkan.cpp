#include "OmnityApi.h"
#include "Graphic.h"
#include "Graphic.Vulkan.h"

#ifdef OMNITY_USE_VULKAN
#include <vulkan/vulkan.hpp>

OMNITY_BEGIN
const vk::Instance& VkResource::CurrentInstance() const
{
	return _owner->_instance;
}
const vk::Device& VkResource::CurrentDevice() const
{
	return _owner->_device;
}

ObjectRef<IIndexBuffer> VkGpuDevice::CreateIndexBuffer(int size)
{
	auto vkBuffer = ObjectRef<VkIndexBuffer>(new VkIndexBuffer(GetObjectRef(), true, true, 1024));
	auto result = vkBuffer.CastTo<IIndexBuffer>();
	return result;
}
OMNITY_END
#endif