#include <resources/resource_package.h>
#include "resource_provider_impl.h"

omnity::resource_package::resource_package(const resource_provider_type type, const std::u16string_view name) {
    provider_ = omnity::create_resource_package_provider(type, name);
}