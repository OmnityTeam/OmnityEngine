#pragma once
#include <functional>
#include <memory>
#include <base/omnity_string.h>

namespace omnity {
    class resource_package_manifest {
    public:

    };
    enum resource_provider_type : uint8_t {
        local_raw
    };
    class base_resource_provider {
    public:
        virtual resource_package_manifest get_manifest() = 0;
        virtual ~base_resource_provider() = default;
    };

    class resource_package {
        std::unique_ptr<omnity::base_resource_provider> provider_;
    public:
        resource_package(resource_provider_type type, std::u16string_view name);
    };
}