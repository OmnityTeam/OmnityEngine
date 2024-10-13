#pragma once
#include <any>
#include <array>
#include <source_location>
#include <map>
#include <typeindex>
#include <ankerl/unordered_dense.h>
#include <ranges>
#include <algorithm>

#define GET_METADATA_FUNC_NAME get_metadata
#define GET_METADATA_GLOBAL_FUNC_NAME(TYPE_NAME) __get_class_##TYPE_NAME##_metadata

#define METADATA_BEGIN(TYPE_NAME)\
static const ::omnity::type_metadata& GET_METADATA_FUNC_NAME() {\
	using __this_type = TYPE_NAME;\
	static_assert(type_id<__this_type> != std::numeric_limits<type_id_t>::max(), "Type is not registered in object.h");\
	[[maybe_unused]] field_id_t field_index = 0;\
	static ::omnity::type_metadata meta(u""#TYPE_NAME, ::omnity::type_index<__this_type>, ::omnity::type_id<__this_type>, {
#define FIELD(FIELD_NAME) \
{::omnity::field_metadata(u""#FIELD_NAME, field_index++, type_id<decltype(__this_type::FIELD_NAME)>, offsetof(__this_type, FIELD_NAME))},

#define METADATA_END() \
}); return meta; }

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

#define DEFINE_BASIC_TYPE(TYPE_NAME)\
const type_metadata& GET_METADATA_GLOBAL_FUNC_NAME(TYPE_NAME)() {\
	static type_metadata meta(u""#TYPE_NAME, ::omnity::type_index<TYPE_NAME>, ::omnity::type_id<TYPE_NAME>, {});\
	return meta;\
}\

#define DEFINE_TYPE(TYPE_NAME)\
const type_metadata& GET_METADATA_GLOBAL_FUNC_NAME(TYPE_NAME)() {\
	return TYPE_NAME::GET_METADATA_FUNC_NAME();\
}\

namespace omnity {
	// Type metadata
	using field_id_t = uint32_t;
	using type_id_t = uint32_t;
	class field_metadata;
	class type_metadata;
	class field_metadata {
		friend class type_metadata;
	public:
		const std::u16string_view name;
		const field_id_t field_id;
		const type_id_t field_type_id;
		const size_t offset;
		constexpr field_metadata(const std::u16string_view n, const field_id_t id, const type_id_t type_id, const size_t off)
			: name(n), field_id(id), field_type_id(type_id), offset(off) {}
		const type_metadata* get_type_metadata() const;
	};
	class type_metadata {
		std::vector<field_metadata> fields_;
		std::map<std::u16string_view, field_id_t> field_map_;
	public:
		const std::u16string_view name;
		const size_t runtime_type_index;
		const type_id_t type_id;
		type_metadata(const std::u16string_view n, const size_t type_index, const type_id_t id, const std::initializer_list<field_metadata> f)
			: fields_(f), name(n), runtime_type_index(type_index), type_id(id) {
			auto kvp = std::views::transform(
				fields_,
				[](const field_metadata& meta) { return std::make_pair(meta.name, meta.field_id); });
			field_map_ = std::map(kvp.begin(), kvp.end());
		}
		const field_metadata* get_field(const field_id_t field_id) const {
			return &fields_[field_id];
		}
		const field_metadata* try_get_field(const std::u16string_view field_name) const {
			const auto ret = field_map_.find(field_name);
			if (ret == field_map_.end()) return nullptr;
			return &fields_[ret->second];
		}
		const std::vector<field_metadata>& get_fields() const {
			return fields_;
		}
	};

	// Type definitions
	template <typename T>
	constexpr inline type_id_t type_id = std::numeric_limits<type_id_t>::max();
	template <typename T>
	constexpr inline size_t type_index = std::numeric_limits<size_t>::max();
	template <typename T>
	inline const type_metadata* type_metadata_ptr = nullptr;
	template <size_t Index>
	constexpr inline type_id_t type_id_by_index = std::numeric_limits<type_id_t>::max();
	template <size_t Index>
	inline const type_metadata* type_metadata_ptr_by_index = nullptr;
	template <type_id_t Id>
	constexpr inline size_t type_index_by_id = std::numeric_limits<size_t>::max();
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
		type_table();
		template<typename T>
		constexpr const type_metadata* get_type_metadata() const {
			return get_type_metadata_by_index(type_index<T>);
		}
		const type_metadata* try_get_type_metadata_by_id(type_id_t type_id) const;
		const type_metadata* get_type_metadata_by_index(size_t type_index) const;
	};
	const type_table* get_type_table();
}