#pragma once
#include <memory>
#include <GraphicBackend/GraphicBackend.h>

namespace Omnity::Graphic::Backend::Vulkan {
	class VulkanContext;
	class VulkanBackend final : public GraphicBackend {
		std::shared_ptr<VulkanContext> _context;
	public:
		bool Setup() override;
		std::weak_ptr<GraphicContext> GetContext() override;
		~VulkanBackend();
	};
}