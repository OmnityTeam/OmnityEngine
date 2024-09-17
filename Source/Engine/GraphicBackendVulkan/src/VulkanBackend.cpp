#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>
#include <VulkanBackend/VulkanBackend.h>
#include <GraphicBackend/GraphicBackend.h>
#include <vulkan/vulkan.hpp>

namespace Omnity::Graphic::Backend::Vulkan {
	class VulkanContext final : public GraphicContext {
		vk::Instance _instance;
	public:
		bool SetupContext() override;
		~VulkanContext() override {
			_instance.destroy();
			_instance = nullptr;
		}
	};
	bool VulkanBackend::Setup() {
		uint32_t version;
		if (vk::enumerateInstanceVersion(&version) != vk::Result::eSuccess)
			return false;
		if (VK_API_VERSION_MAJOR(version) < 1 || VK_API_VERSION_MINOR(version) < 2)
			return false;
		_context = std::make_shared<VulkanContext>();
		if (!_context->SetupContext())
			return false;
		return true;
	}
	std::weak_ptr<GraphicContext> VulkanBackend::GetContext() {
		return _context;
	}
	bool VulkanContext::SetupContext() {
		vk::ApplicationInfo appInfo("Game", 1, "Omnity", 1, VK_API_VERSION_1_2);
		vk::InstanceCreateInfo instanceCreateInfo({}, &appInfo, {}, {});
		_instance = vk::createInstance(instanceCreateInfo);
		return true;
	}
	VulkanBackend::~VulkanBackend() {}
}