#pragma once
#include <resources/resource_package.h>
namespace omnity {
    class local_raw_resource_provider final : public base_resource_provider {
        std::u16string path_;
    public:
        explicit local_raw_resource_provider(std::u16string_view name);
        resource_package_manifest get_manifest() override;
    };

    std::unique_ptr<omnity::base_resource_provider> create_resource_package_provider(resource_provider_type provider_type, std::u16string_view name);
}