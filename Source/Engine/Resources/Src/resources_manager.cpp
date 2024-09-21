#include <resources/resources_manager.h>

static omnity::resources_manager* builtin_resource_manager;

namespace omnity {
    void resources_manager::initialize() {
        if (builtin_resource_manager == nullptr)
            builtin_resource_manager = new resources_manager();
    }
    void resources_manager::destroy() {
        delete builtin_resource_manager;
    }
    resources_manager* resources_manager::get_instance() {
        return builtin_resource_manager;
    }
}