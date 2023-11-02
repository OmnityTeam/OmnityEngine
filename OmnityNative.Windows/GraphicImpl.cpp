#include "Graphic.h"

OMNITY_BEGIN

GraphicHost::GraphicHost(GraphicApi api)
{
	switch (api)
	{
	case GraphicApi::Vulkan:
		_device = ObjectRef((IGpuDevice*)new VkGpuDevice());
	}
}

OMNITY_END