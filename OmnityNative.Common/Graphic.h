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
class IIndexBuffer;
class ITexture;
class ITexture2D;
class IRenderTarget;
class IShader;
class IRenderPipeline;
class IDescriptor;

class GraphicContext
{
private:
	ObjectRef<IGpuDevice> _device;

public:
	ObjectRef<IIndexBuffer> CreateIndexBuffer(int size);
	GraphicContext(GraphicApi api);
	~GraphicContext() {}
};

class IGpuDevice
{
public:
	virtual ObjectRef<IIndexBuffer> CreateIndexBuffer(int size) = 0;
};

class IGpuResources
{
};

class IBuffer : virtual public IGpuResources
{
public:
	virtual UInt GetSize() = 0;
};

class IIndexBuffer : virtual public IBuffer
{
};


OMNITY_END