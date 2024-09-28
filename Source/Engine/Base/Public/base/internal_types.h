#pragma once
#include <any>
#include <array>
#include <source_location>
#include <map>
#include <typeindex>
#include <cereal/archives/binary.hpp>

#define ENABLE_SERIALIZE(NAME, ARCHIVE)\
static inline type_enable_serializer<NAME, cereal::ARCHIVE> __##NAME##_##ARCHIVE
#define ENABLE_DESERIALIZE(NAME, ARCHIVE)\
static inline type_enable_deserializer<NAME, cereal::ARCHIVE> __##NAME##_##ARCHIVE

#define DEFINE_CTOR(NAME)\
inline std::any __##NAME##_ctor();\
struct __##NAME##_ctor_t {\
    __##NAME##_ctor_t() {\
		type_table_global().ctor[type_index<NAME>] = &__##NAME##_ctor;\
	}\
};\
static inline __##NAME##_ctor_t __##NAME##_ctor_define;\
inline std::any __##NAME##_ctor()

#define DECLARE_TYPE(NAME, ID)\
class NAME;\
template <>\
constexpr inline uint32_t type_count_before<std::source_location::current().line()> = type_count_before<std::source_location::current().line() - 1> + 1;\
template <>\
constexpr inline uint32_t type_id<NAME> = ID;\
template <>\
constexpr inline uint32_t type_index<NAME> = type_count_before<std::source_location::current().line()> - 1;\
template <>\
constexpr inline uint32_t type_id_by_index<type_index<NAME>> = type_id<NAME>;\
template <>\
constexpr inline uint32_t type_index_by_id<type_id<NAME>> = type_index<NAME>;\
template <>\
struct type_info<type_id<NAME>> {\
}

namespace omnity {
	template <uint32_t Id>
	struct type_info {
		template <typename... Args>
		static constexpr bool can_constructible_from = false;
		template <typename TArchive, typename... TArgs>
		static constexpr std::any instantiate_from([[maybe_unused]] TArchive& ar, [[maybe_unused]] TArgs&&... args) {
			throw std::exception("Unknown type");
		}
		template <typename... TArgs>
		static constexpr std::any instantiate([[maybe_unused]] TArgs&&... args) {
			throw std::exception("Unknown type");
		}
		template <typename TArchive>
		static constexpr void save([[maybe_unused]] void* ptr, [[maybe_unused]] TArchive& ar) {
			throw std::exception("Unknown type");
		}
	};
	template <typename T>
	constexpr inline uint32_t type_id = std::numeric_limits<uint32_t>::max();
	template <typename T>
	constexpr inline uint32_t type_index = std::numeric_limits<uint32_t>::max();
	template <int Index>
	constexpr inline uint32_t type_id_by_index = std::numeric_limits<uint32_t>::max();
	template <int Id>
	constexpr inline uint32_t type_index_by_id = std::numeric_limits<uint32_t>::max();
	template <uint_least32_t Line>
	constexpr inline uint32_t type_count_before = type_count_before<Line - 1>;
	template <>
	constexpr inline uint32_t type_count_before<0> = 0;

	// Begin internal type definition
	// basic asset
	DECLARE_TYPE(scene, 1);
	DECLARE_TYPE(scene_node, 2);
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
	struct type_table {
		std::array<std::any(*)(), type_count> ctor;
		std::map<std::type_index, std::array<void*, type_count>> load;
		std::map<std::type_index, std::array<void*, type_count>> save;
	};
	inline type_table& type_table_global() {
		static type_table table;
		return table;
	}
	template <typename T, typename TArchive>
	struct type_enable_deserializer {
		static void load(T* obj, TArchive ar) {
			obj->template load<TArchive>(ar);
		}
		explicit type_enable_deserializer() {
			type_table_global().load[std::type_index(typeid(TArchive))][type_index<T>] = reinterpret_cast<void*>(&load);
		}
	};
	template <typename T, typename TArchive>
	struct type_enable_serializer {
		static void save(T* obj, TArchive ar) {
			obj->template save<TArchive>(ar);
		}
		explicit type_enable_serializer() {
			type_table_global().save[std::type_index(typeid(TArchive))][type_index<T>] = reinterpret_cast<void*>(&save);
		}
	};
}