#include "Graphic.h"

OMNITY_BEGIN

Bool Graphic::Init(GraphicApi api)
{
	return true;
}

ObjectRef<Buffer> Graphic::CreateBuffer()
{
	auto ptr = ObjectRef<Buffer>(new Buffer());
	ptr->test();
	auto ptr2 = std::move(ptr);
	return ptr2;
}

OMNITY_END