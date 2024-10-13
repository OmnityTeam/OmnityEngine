#pragma once
#include <vector>
#include <base/object.h>
#include <resources/resources.h>

namespace omnity {
	struct imported_object {
		type_id_t type_id;
		std::shared_ptr<void> ptr;
		imported_object(const type_id_t i, const std::shared_ptr<void>& p) : type_id(i), ptr(p) {}
		imported_object(const type_id_t i, std::shared_ptr<void>&& p) : type_id(i), ptr(std::move(p)) {}
	};
	class importer_context {
		std::map<resource_inner_id_t, imported_object> cache_;
	public:
		const std::map<resource_inner_id_t, imported_object>& get_cache() const {
			return cache_;
		}
		template<typename T>
		T& add(resource_inner_id_t id) {
			auto ptr = std::make_shared<T>();
			auto& ref = *ptr;
			cache_.emplace(id, imported_object(type_id<T>, ptr));
			return ref;
		}
	};
	using resource_importer = void(*)(importer_context& ctx, std::u16string_view path);
	resource_importer importer_get(std::u16string_view ext);
	template<typename T>
	void Load(T& obj, std::u16string_view path) {

	}
}