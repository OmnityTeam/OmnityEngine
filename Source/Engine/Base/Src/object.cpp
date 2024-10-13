#include <exception>
#include "base/object.h"

namespace {
	std::array<const omnity::type_metadata*, omnity::type_count> type_cache;
	std::unordered_map<omnity::type_id_t, size_t> type_map;
	template<int Cur = 0>
	void build_type_cache() {
		if constexpr (Cur != omnity::type_count) {
			type_cache[Cur] = omnity::type_metadata_ptr_by_index<Cur>;
			build_type_cache<Cur + 1>();
		}
	}
	void build_type_map() {
		for (size_t i = 0; i < omnity::type_count; ++i)
			type_map.emplace(type_cache[i]->type_id, i);
	}
}
namespace omnity{
	const type_table* get_type_table() {
		static type_table type_table;
		return &type_table;
	}
	type_table::type_table() {
		build_type_cache();
		build_type_map();
	}
	const type_metadata* type_table::get_type_metadata_by_index(size_t type_index) const {
		return type_cache[type_index];
	}
	const type_metadata* type_table::try_get_type_metadata_by_id(type_id_t type_id) const {
		const auto ret = type_map.find(type_id);
		if (ret == type_map.end()) return nullptr;
		return type_cache[ret->second];
	}
	const type_metadata* field_metadata::get_type_metadata() const {
		return get_type_table()->try_get_type_metadata_by_id(field_type_id);
	}
	DEFINE_BASIC_TYPE(int);
	DEFINE_BASIC_TYPE(bool);
	DEFINE_BASIC_TYPE(int8_t);
	DEFINE_BASIC_TYPE(int16_t);
	DEFINE_BASIC_TYPE(int32_t);
	DEFINE_BASIC_TYPE(int64_t);
	DEFINE_BASIC_TYPE(uint8_t);
	DEFINE_BASIC_TYPE(uint16_t);
	DEFINE_BASIC_TYPE(uint32_t);
	DEFINE_BASIC_TYPE(uint64_t);
	DEFINE_BASIC_TYPE(float);
	DEFINE_BASIC_TYPE(double);
	DEFINE_BASIC_TYPE(serializable_u16string_view);
}