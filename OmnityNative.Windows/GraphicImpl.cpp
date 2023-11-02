#include "Graphic.h"
#include "Graphic.h"

OMNITY_BEGIN

Graphic::Graphic(GraphicApi api)
{

}

ObjectRef<Buffer> Graphic::CreateBuffer()
{
	auto ptr = ObjectRef<Buffer>(new Buffer());
	ptr->test();
	auto ptr2 = std::move(ptr);
	return ptr2;
}

OMNITY_END