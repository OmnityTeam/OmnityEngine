#include <Resources/ResourcePackage.h>
#include "ResourceProviderImpl.h"

Omnity::ResourcePackage::ResourcePackage(ResourceProviderType type, std::u16string_view name) {
	_provider = Omnity::CreateResourcePackageProvider(type, name);
}