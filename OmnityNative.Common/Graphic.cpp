#include "OmnityApi.h"
#include "Graphic.h"

OMNITY_BEGIN

#ifdef OMNITY_USE_VULKAN
VkGpuDevice::VkGpuDevice()
{
	auto apiVersion = vk::enumerateInstanceVersion();
	auto major = VK_VERSION_MAJOR(apiVersion);
	auto minor = VK_VERSION_MINOR(apiVersion);
	auto patch = VK_VERSION_PATCH(apiVersion);
	if (major < 1 || minor < 1)
		throw new std::exception("require vulkan 1.1");
	vk::InstanceCreateInfo instanceCreateInfo;
	_instance = vk::createInstance(instanceCreateInfo);
}
VkGpuDevice::~VkGpuDevice()
{
	_instance.destroy();
}

#endif

OMNITY_END

OMNITY_API_EXPORT OMNITY_API_CTOR(GraphicHost, OMNITY_NAMESPACE::GraphicApi api)
{
	return OMNITY_API_CTOR_CREATE_OBJECT(GraphicHost, api);
}
