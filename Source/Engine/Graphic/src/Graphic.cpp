#include <memory>
#include "GraphicBackend.h"
#include "Graphic.h"
#ifdef GRAPHIC_BACKEND_VULKAN
#include "VulkanBackend.h"
#endif

namespace Omnity::Graphic {
	std::unique_ptr<Backend::GraphicBackend> backend;
	bool CheckBackend(uint8_t backendId) {
		switch (backendId) {
			case VulkanBackend:
#ifdef GRAPHIC_BACKEND_VULKAN
				return true;
#else
				return false;
#endif
			case DX12Backend:
#ifdef GRAPHIC_BACKEND_DX12
				return true;
#else
				return false;
#endif
			default:
				return false;
		}
	}

	void InitGraphic() {
#ifdef GRAPHIC_BACKEND_VULKAN
		Backend::RegisterGraphicBackend<VulkanBackend, Backend::Vulkan::VulkanBackend>();
#endif
#ifdef GRAPHIC_BACKEND_DX12
		Backend::RegisterGraphicBackend<DX12Backend, Backend::Vulkan::DX12Backend>();
#endif
	}
	bool SetupGraphicBackend(uint8_t id) {
		backend = Backend::GetGraphicBackendFactory(id)();
		if (!backend->Setup()) {
			backend = nullptr;
			return false;
		}
		return true;
	}
	bool SetupGraphicBackend() {
		if (CheckBackend(VulkanBackend) && SetupGraphicBackend(VulkanBackend)) return true;
		return false;
	}
}