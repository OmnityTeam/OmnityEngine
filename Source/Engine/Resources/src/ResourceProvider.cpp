#include "ResourceProviderImpl.h"

std::unique_ptr<Omnity::IResourceProvider> Omnity::CreateResourcePackageProvider(ResourceProviderType providerType, std::u16string_view name) {
	switch (providerType) {
	case ResourceProviderType::LocalRaw:
		return std::make_unique<LocalRawResourceProvider>(name);
	default:
		return nullptr;
	}
}

Omnity::LocalRawResourceProvider::LocalRawResourceProvider(std::u16string_view name) {
	_path = name;
}
Omnity::ResourcePackageManifest Omnity::LocalRawResourceProvider::GetManifest() {
	return Omnity::ResourcePackageManifest();
}