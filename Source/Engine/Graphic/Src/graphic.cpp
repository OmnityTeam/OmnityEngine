#include <memory>
#include <graphic_backend/graphic_backend.h>
#include <graphic/graphic.h>
#ifdef GRAPHIC_BACKEND_VULKAN
#include <vulkan_backend/vulkan_backend.h>
#endif

namespace omnity::graphic {
    std::unique_ptr<backend::graphic_backend> backend_instance;
    bool check_backend(const uint8_t backend_id) {
        switch (backend_id) {
        case vulkan_backend:
#ifdef GRAPHIC_BACKEND_VULKAN
            return true;
#else
            return false;
#endif
        case dx12_backend:
#ifdef GRAPHIC_BACKEND_DX12
            return true;
#else
            return false;
#endif
        default:
            return false;
        }
    }

    void init_graphic() {
#ifdef GRAPHIC_BACKEND_VULKAN
        backend::register_graphic_backend<vulkan_backend, backend::vulkan::vulkan_backend>();
#endif
#ifdef GRAPHIC_BACKEND_DX12
        Backend::RegisterGraphicBackend<DX12Backend, Backend::DX12::DX12Backend>();
#endif
    }
    bool setup_graphic_backend(const uint8_t backend_id) {
        backend_instance = backend::get_graphic_backend_factory(backend_id)();
        if (!backend_instance->setup()) {
            backend_instance = nullptr;
            return false;
        }
        return true;
    }
    bool setup_graphic_backend() {
        if (check_backend(vulkan_backend) && setup_graphic_backend(vulkan_backend)) return true;
        return false;
    }
}