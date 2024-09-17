#pragma once
#include <functional>
#include <memory>
#include <Base/OmnityString.h>

namespace Omnity {
	class ResourcePackageManifest {
	public:

	};
	enum ResourceProviderType : uint8_t {
		LocalRaw
	};
	class IResourceProvider {
	public:
		virtual ResourcePackageManifest GetManifest() = 0;
		virtual ~IResourceProvider() = default;
	};

	class ResourcePackage {
		std::unique_ptr<Omnity::IResourceProvider> _provider;
	public:
		ResourcePackage(ResourceProviderType type, std::u16string_view name);
	};
}