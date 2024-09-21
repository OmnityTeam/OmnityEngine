#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <any>
#include <base/omnity_uuid.h>

namespace omnity {
    class resources_manager;
    class any_resource {
    public:

    };

    class resource_ref {
    public:
        uuids::uuid id;
    };

    class resources_manager final {
        using resource_set = std::unordered_map<uuids::uuid, any_resource>;
        resource_set asset_dict_;
    public:


        static void initialize();
        static void destroy();
        static resources_manager* get_instance();
    };
}