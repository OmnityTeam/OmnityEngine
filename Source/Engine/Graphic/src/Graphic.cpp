#include <memory>
#include "Rhi.h"
#include "Graphic.h"
#ifdef GRAPHIC_RHI_VULKAN
#include "RhiVulkan.h"
#endif

std::unique_ptr<Rhi> rhi;

void InitGraphic()
{
#ifdef GRAPHIC_RHI_VULKAN
	RegisterRhiImpl<1, VulkanRhi>();
#endif
}

void SetupRhi()
{
	rhi = EnumRhiFactory()->second();
}