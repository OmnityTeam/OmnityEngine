#include "OmnityApi.h"
#include "Graphic.h"
#include <exception>
#ifdef OMNITY_USE_VULKAN
#include <vulkan/vulkan.hpp>
#endif

OMNITY_BEGIN

#ifdef OMNITY_USE_VULKAN
class VkGpuDevice : IGpuDevice
{
	vk::Instance _instance;
public:
	ObjectRef<IBuffer> CreateBuffer(int size)
	{
		return ObjectRef<IBuffer>();
	}
	VkGpuDevice()
	{
		auto apiVersion = vk::enumerateInstanceVersion();
		auto major = VK_VERSION_MAJOR(apiVersion);
		auto minor = VK_VERSION_MINOR(apiVersion);
		auto patch = VK_VERSION_PATCH(apiVersion);
		if (major < 1 || minor < 1)
			throw new std::exception("require vulkan 1.1");

		auto instanceLayer = vk::enumerateInstanceLayerProperties();
		auto instanceExtension = vk::enumerateInstanceExtensionProperties();

		vk::InstanceCreateInfo instanceCreateInfo;
		_instance = vk::createInstance(instanceCreateInfo);

		auto physicalDevices = _instance.enumeratePhysicalDevices();
		for (const auto& device : physicalDevices)
		{
			
		}
	}
	~VkGpuDevice()
	{
		_instance.destroy();
	}
};

class VkBuffer : IBuffer
{
	vk::Buffer _buffer;
public:

};

#endif


GraphicHost::GraphicHost(GraphicApi api)
{
	switch (api)
	{
#ifdef OMNITY_USE_VULKAN
	case GraphicApi::Vulkan:
		_device = ObjectRef<IGpuDevice>((IGpuDevice*)new VkGpuDevice());
		break;
#endif

	default:
		throw new std::exception("Unsupported api");
	}
}

OMNITY_END

OMNITY_API_EXPORT OMNITY_API_CTOR(GraphicHost, OMNITY_NAMESPACE::GraphicApi api)
{
	return OMNITY_API_CTOR_CREATE_OBJECT(GraphicHost, api);
}
