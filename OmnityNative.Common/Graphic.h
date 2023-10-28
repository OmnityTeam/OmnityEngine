#pragma once
#include "OmnityApi.h"

OMNITY_BEGIN

enum GraphicApi
{
	Vulkan = 0,
	Directx = 1
};

class Buffer;
class Texture;
class Texture2D;
class RenderTarget;
class Shader;
class RenderPipeline;
class Descriptor;

class Graphic : public OmnityObject
{
public:
	Bool Init(GraphicApi api);
	ObjectRef<Buffer> CreateBuffer();
};

class Buffer : public OmnityObject
{
public:
	void test() {}
};

class Texture : public OmnityObject
{

};

class Texture2D : public Texture
{

};

class RenderTarget : public OmnityObject
{

};

class Shader : public OmnityObject
{

};

class RenderPipeline : public OmnityObject
{

};

class Descriptor : public OmnityObject
{

};

OMNITY_END