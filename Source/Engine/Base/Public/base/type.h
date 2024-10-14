#pragma once
#include <array>
#include <source_location>
#include <map>
#include <vector>
#include <ranges>
#include <cassert>
#include <base/type_metadata.h>

#define GET_METADATA_FUNC_NAME get_metadata
#define GET_METADATA_GLOBAL_FUNC_NAME(TYPE_NAME) __get_class_##TYPE_NAME##_metadata

#define DECLARE_BASIC_TYPE(NAME, ID)\
const type_metadata& GET_METADATA_GLOBAL_FUNC_NAME(NAME)();\
template <>\
constexpr inline size_t type_count_before<std::source_location::current().line()> = type_count_before<std::source_location::current().line() - 1> + 1;\
template <>\
constexpr inline type_id_t type_id<NAME> = ID;\
template <>\
constexpr inline size_t type_index<NAME> = type_count_before<std::source_location::current().line()> - 1;\
template <>\
constexpr inline type_id_t type_id_by_index<type_index<NAME>> = type_id<NAME>;\
template <>\
constexpr inline size_t type_index_by_id<type_id<NAME>> = type_index<NAME>;\
template <>\
inline const type_metadata* type_metadata_ptr_by_id<type_id<NAME>> = &GET_METADATA_GLOBAL_FUNC_NAME(NAME)();\
template <>\
inline const type_metadata* type_metadata_ptr_by_index<type_index<NAME>> = &GET_METADATA_GLOBAL_FUNC_NAME(NAME)();\
template <>\
inline const type_metadata* type_metadata_ptr<NAME> = &GET_METADATA_GLOBAL_FUNC_NAME(NAME)()

#define DECLARE_TYPE(NAME, ID)\
class NAME;\
DECLARE_BASIC_TYPE(NAME, ID)

#define DEFINE_TYPE(TYPE_NAME)\
const type_metadata& GET_METADATA_GLOBAL_FUNC_NAME(TYPE_NAME)() {\
	return TYPE_NAME::GET_METADATA_FUNC_NAME();\
}\

namespace omnity {
	// Type definitions
	template <typename T>
	constexpr inline type_id_t type_id = []() constexpr { static_assert(false, "Unknown type"); };
	template <typename T>
	constexpr inline size_t type_index = []() constexpr { static_assert(false, "Unknown type"); };
	template <typename T>
	inline const type_metadata* type_metadata_ptr = nullptr;
	template <size_t Index>
	constexpr inline type_id_t type_id_by_index = []() constexpr { static_assert(false, "Unknown type"); };
	template <size_t Index>
	inline const type_metadata* type_metadata_ptr_by_index = nullptr;
	template <type_id_t Id>
	constexpr inline size_t type_index_by_id = []() constexpr { static_assert(false, "Unknown type"); };
	template <type_id_t Id>
	inline const type_metadata* type_metadata_ptr_by_id = nullptr;
	template <uint_least32_t Line>
	constexpr inline size_t type_count_before = type_count_before<Line - 1>;
	template <>
	constexpr inline size_t type_count_before<0> = 0;

	// Begin internal type definition
	// cpp types
	DECLARE_BASIC_TYPE(bool, 1);
	DECLARE_BASIC_TYPE(int8_t, 2);
	DECLARE_BASIC_TYPE(int16_t, 3);
	DECLARE_BASIC_TYPE(int32_t, 4);
	DECLARE_BASIC_TYPE(int64_t, 5);
	DECLARE_BASIC_TYPE(uint8_t, 6);
	DECLARE_BASIC_TYPE(uint16_t, 7);
	DECLARE_BASIC_TYPE(uint32_t, 8);
	DECLARE_BASIC_TYPE(uint64_t, 9);
	DECLARE_BASIC_TYPE(float, 10);
	DECLARE_BASIC_TYPE(double, 11);
	using serializable_u16string_view = std::u16string_view;
	DECLARE_BASIC_TYPE(serializable_u16string_view, 12);

	// basic types
	DECLARE_TYPE(binary_block_t, 101);

	// basic asset
	DECLARE_TYPE(scene, 1001);
	DECLARE_TYPE(scene_node, 1002);
	// 10000: rendering asset
	DECLARE_TYPE(texture, 10001);
	DECLARE_TYPE(material, 10002);
	DECLARE_TYPE(shader, 10003);
	DECLARE_TYPE(mesh, 10004);
	DECLARE_TYPE(particle, 10005);
	// 20000: resource
	DECLARE_TYPE(text_asset, 20001);
	// End internal type definition
	constexpr inline uint32_t type_count = type_count_before<std::source_location::current().line()>;

	// Type table
	class type_table {
	public:
		using type_cache_t = std::array<const type_metadata*, type_count>;
		using type_map_t = std::unordered_map<type_id_t, size_t>;
	private:
		type_cache_t type_cache_;
		type_map_t type_map_;
	public:
		type_table();
		template<typename T>
		constexpr const type_metadata* get_type_metadata() const {
			return get_type_metadata_by_index(type_index<T>);
		}
		constexpr const type_metadata* get_type_metadata_by_index(size_t type_index) const {
			return type_cache_[type_index];
		}
		const type_metadata* try_get_type_metadata_by_id(type_id_t type_id) const {
			const auto ret = type_map_.find(type_id);
			assert(ret != type_map_.end());
			return type_cache_[ret->second];
		}
	};
	extern const type_table type_table_instance;
	inline const type_metadata* field_metadata::get_type_metadata() const {
		return type_table_instance.get_type_metadata_by_index(field_type_index);
	}
}