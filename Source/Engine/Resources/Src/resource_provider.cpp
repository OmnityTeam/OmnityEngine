#include "resource_provider_impl.h"

std::unique_ptr<omnity::base_resource_provider> omnity::create_resource_package_provider(
    const resource_provider_type provider_type, std::u16string_view name)
{
    switch (provider_type)
    {
    case local_raw:
        return std::make_unique<local_raw_resource_provider>(name);
    default:
        return nullptr;
    }
}

omnity::local_raw_resource_provider::local_raw_resource_provider(const std::u16string_view name)
{
    path_ = name;
}

omnity::resource_package_manifest omnity::local_raw_resource_provider::get_manifest()
{
    return {};
}
