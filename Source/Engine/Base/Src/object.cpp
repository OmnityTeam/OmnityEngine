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
	const type_metadata* type_table::get_type_metadata_by_index(int type_index) const {
		return type_cache[type_index];
	}
	const type_metadata* type_table::get_type_metadata_by_id(int type_id) const {
		const auto ret = type_map.find(type_id);
		if (ret == type_map.end()) throw std::exception("Unknown type");
		return type_cache[ret->second];
	}
}