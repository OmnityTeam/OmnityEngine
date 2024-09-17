#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <any>

namespace Omnity {
	class ResourcesManager;

	class Resource final {
		friend class ResourcesManager;
		std::any _ptr;
		uint32_t _id;
		template <typename TResource, typename... TArgs>
		void Initialize(uint32_t id, TArgs&&... args) {
			_ptr = std::make_any<TResource>(std::forward<TArgs>(args)...);
			_id = id;
		}
	public:
		Resource() noexcept : _ptr(nullptr), _id(-1) {}
		template<typename TResource> const TResource& Content() const {
			return std::any_cast<const TResource&>(_ptr);
		}
	};

	class ResourcesManager final {
		using ResourceSet = std::unordered_map<uint32_t, Resource>;
		ResourceSet _assetDict;
	public:
		template <typename TResource, typename... TArgs>
		const Resource& RegisterResource(uint32_t id, TArgs&&... args) {
			_assetDict.emplace(id, Resource());
			auto& ret = _assetDict.at(id);
			ret.Initialize<TResource>(id, std::forward<TArgs>(args)...);
			return ret;
		}
		inline const Resource* GetResource(uint32_t id) const {
			auto it = _assetDict.find(id);
			if (it == _assetDict.end()) return nullptr;
			return &it->second;
		}
		static void Initialize();
		static void Destroy();
		static ResourcesManager* GetInstance();
	};
}