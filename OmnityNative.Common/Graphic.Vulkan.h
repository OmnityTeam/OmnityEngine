#include "OmnityApi.h"
#include "Graphic.h"

#ifdef OMNITY_USE_VULKAN
#include <vulkan/vulkan.hpp>

OMNITY_BEGIN

class VkGpuDevice;
class VkIndexBuffer;

class VkResource : virtual public IGpuResources
{
	ObjectRef<VkGpuDevice> _owner;
protected:
	VkResource(ObjectRef<VkGpuDevice> device) : _owner(device) {}
	~VkResource() = default;

	const vk::Instance& CurrentInstance() const;
	const vk::Device& CurrentDevice() const;
};

class VkGpuDevice : public EnableRefFromThis<VkGpuDevice>, virtual public IGpuDevice
{
	friend class VkResource;
protected:
	vk::Instance _instance;
	vk::Device _device;

public:
	ObjectRef<IIndexBuffer> CreateIndexBuffer(int size) override;

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

		vk::ApplicationInfo appInfo;
		appInfo.setApiVersion(apiVersion);
		appInfo.setApplicationVersion(1);
		appInfo.setEngineVersion(1);
		appInfo.setPApplicationName("OmnityPlayer");
		appInfo.setPEngineName("OmnityEngine");
		vk::InstanceCreateInfo instanceCreateInfo;
		std::vector<const char*> enabledLayer
		{
			"VK_LAYER_KHRONOS_validation"
		};
		instanceCreateInfo.setPEnabledLayerNames(enabledLayer);
		instanceCreateInfo.setPApplicationInfo(&appInfo);
		_instance = vk::createInstance(instanceCreateInfo);
		auto physicalDevices = _instance.enumeratePhysicalDevices();
		
		auto queueInfo = physicalDevices[0].getQueueFamilyProperties();
		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
		auto list = { 1.0f };
		queueCreateInfos.emplace_back(vk::DeviceQueueCreateInfo(vk::DeviceQueueCreateFlags::Flags(0), 0, list, 0));

		vk::DeviceCreateInfo deviceCreateInfo;
		deviceCreateInfo.setQueueCreateInfos(queueCreateInfos);
		_device = physicalDevices[0].createDevice(deviceCreateInfo);
	}
	~VkGpuDevice()
	{
		_device.waitIdle();
		_device.destroy();
		_instance.destroy();
	}
};

class VkBuffer : public VkResource, virtual public IBuffer
{
protected:
	enum BufferType
	{
		UniformTexel,
		StorageTexel,
		UniformBuffer,
		StorageBuffer,
		IndexBuffer,
		VertexBuffer,
		Indirectbuffer
	};

	vk::Buffer _buffer = nullptr;
	bool _isReadable;
	bool _isWritable;
	UInt _size;

	VkBuffer(
		ObjectRef<VkGpuDevice> device, 
		bool isReadable, 
		bool isWritable, 
		UInt size,
		BufferType bufferType) : VkResource(device), _size(size)
	{
		_isReadable = isReadable;
		_isWritable = isWritable;
		vk::BufferCreateInfo bufferCreateInfo;
		vk::BufferUsageFlagBits bufferUsage;
		switch (bufferType)
		{
		case UniformTexel: bufferUsage = vk::BufferUsageFlagBits::eUniformTexelBuffer; break;
		case StorageTexel: bufferUsage = vk::BufferUsageFlagBits::eStorageTexelBuffer; break;
		case UniformBuffer: bufferUsage = vk::BufferUsageFlagBits::eUniformBuffer; break;
		case StorageBuffer: bufferUsage = vk::BufferUsageFlagBits::eUniformTexelBuffer; break;
		case IndexBuffer: bufferUsage = vk::BufferUsageFlagBits::eIndexBuffer; break;
		case VertexBuffer: bufferUsage = vk::BufferUsageFlagBits::eVertexBuffer; break;
		case Indirectbuffer: bufferUsage = vk::BufferUsageFlagBits::eIndirectBuffer; break;
		}
		bufferCreateInfo.setSize(size);
		bufferCreateInfo.setUsage(vk::BufferUsageFlags(bufferUsage));
		_buffer = CurrentDevice().createBuffer(bufferCreateInfo);
	}
	~VkBuffer()
	{
		if (_buffer) CurrentDevice().destroyBuffer(_buffer);
	}
};

class VkIndexBuffer : public VkBuffer, virtual public IIndexBuffer
{
public:
	VkIndexBuffer(ObjectRef<VkGpuDevice> device, bool isReadable, bool isWritable, UInt size) : 
		VkBuffer(device, isReadable, isWritable, size, IndexBuffer)
	{
		
	}	
	UInt GetSize() override
	{
		return _size;
	}
};
OMNITY_END
#endif