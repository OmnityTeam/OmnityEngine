#pragma once
#include <Resources/ResourcePackage.h>
namespace Omnity {
	class LocalRawResourceProvider : public IResourceProvider {
		std::u16string _path;
	public:
		LocalRawResourceProvider(std::u16string_view name);
		ResourcePackageManifest GetManifest() override;
	};

	std::unique_ptr<Omnity::IResourceProvider> CreateResourcePackageProvider(ResourceProviderType providerType, std::u16string_view name);
}