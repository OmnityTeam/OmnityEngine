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
public:
	virtual ObjectRef<IBuffer> CreateBuffer(int size) = 0;

protected:
	IGpuDevice() {}
	~IGpuDevice() {}
};

class GpuResource : public OmnityObject
{
private:
	ObjectRef<IGpuDevice> _owner;
};

class IBuffer : public GpuResource
{
public:
	virtual void CopyTo(ObjectRef<IBuffer> dest) = 0;

protected:
	IBuffer() {}
	~IBuffer() {}
};

class ITexture : public GpuResource
{

};

class ITexture2D : public ITexture
{

};

class IRenderTarget : public GpuResource
{

};

class IShader : public GpuResource
{

};

class IRenderPipeline : public GpuResource
{

};

class IDescriptor : public GpuResource
{

};

OMNITY_END