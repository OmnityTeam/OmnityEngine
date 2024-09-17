#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <any>
#include <Base/OmnityUUID.h>

namespace Omnity {
	class ResourcesManager;
	class AnyResource {
	public:

	};

	class ResourceRef {
	public:
		uuids::uuid id;
	};

	class ResourcesManager final {
		using ResourceSet = std::unordered_map<uuids::uuid, AnyResource>;
		ResourceSet _assetDict;
	public:

		
		static void Initialize();
		static void Destroy();
		static ResourcesManager* GetInstance();
	};
}