#pragma once
#include "OmnityApi.h"

/***********************************/
// 
// Define OMNITY_USE_VULKAN if vulkan is supported in current platform
//
/***********************************/
OMNITY_BEGIN

enum GraphicApi
{
	Vulkan = 0,
	Directx = 1
};

class IGpuDevice;
class IBuffer;
class ITexture;
class ITexture2D;
class IRenderTarget;
class IShader;
class IRenderPipeline;
class IDescriptor;

class GraphicHost : public OmnityObject
{
private:
	ObjectRef<IGpuDevice> _device;

public:
	GraphicHost(GraphicApi api);
};

class IGpuDevice : public OmnityObject
{
protected:
	IGpuDevice() {}
	~IGpuDevice() {}
};

class IBuffer : public OmnityObject
{

};

class ITexture : public OmnityObject
{

};

class ITexture2D : public ITexture
{

};

class IRenderTarget : public OmnityObject
{

};

class IShader : public OmnityObject
{

};

class IRenderPipeline : public OmnityObject
{

};

class IDescriptor : public OmnityObject
{

};

OMNITY_END


#ifdef OMNITY_USE_VULKAN
#include <vulkan/vulkan.hpp>
OMNITY_BEGIN
class VkGpuDevice : IGpuDevice
{
	vk::Instance _instance;
public:
	VkGpuDevice();
	~VkGpuDevice();
};
OMNITY_END
#endif