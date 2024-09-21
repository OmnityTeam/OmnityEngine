#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>
#include <vulkan_backend/vulkan_backend.h>
#include <graphic_backend/graphic_backend.h>
#include <vulkan/vulkan.hpp>

namespace omnity::graphic::backend::vulkan {
	class vulkan_context final : public graphic_context {
		vk::Instance instance_;

	public:
		vulkan_context(vulkan_context&) = delete;
		vulkan_context(vulkan_context&&) = delete;
		vulkan_context& operator=(vulkan_context&) = delete;
		vulkan_context& operator=(vulkan_context&&) = delete;
		vulkan_context() = default;
		bool setup_context() override;

		~vulkan_context() override {
			instance_.destroy();
			instance_ = nullptr;
		}
	};

	bool vulkan_backend::setup() {
		uint32_t version;
		if (vk::enumerateInstanceVersion(&version) != vk::Result::eSuccess)
			return false;
		if (VK_API_VERSION_MAJOR(version) < 1 || VK_API_VERSION_MINOR(version) < 2)
			return false;
		context_ = std::make_shared<vulkan_context>();
		if (!context_->setup_context())
			return false;
		return true;
	}

	std::weak_ptr<graphic_context> vulkan_backend::get_context() {
		return context_;
	}

	bool vulkan_context::setup_context() {
		vk::ApplicationInfo app_info("Game", 1, "Omnity", 1, VK_API_VERSION_1_2);
		vk::InstanceCreateInfo instance_create_info({}, &app_info, {}, {});
		instance_ = createInstance(instance_create_info);
		return true;
	}

	vulkan_backend::~vulkan_backend() = default;
}
