#pragma once
#include <string>
#include <base/type_metadata.h>
#include <base/type.h>

#define METADATA_BEGIN(TYPE_NAME)\
static const ::omnity::type_metadata& GET_METADATA_FUNC_NAME() {\
	using __this_type = TYPE_NAME;\
	static_assert(type_id<__this_type> != std::numeric_limits<type_id_t>::max(), "Type is not registered in object.h");\
	[[maybe_unused]] field_id_t field_index = 0;\
	static ::omnity::type_metadata meta(u""#TYPE_NAME, ::omnity::type_index<__this_type>, ::omnity::type_id<__this_type>, \
	::omnity::serializer_t(\
		[](serialize_ctx* ctx, void* ptr) { ::omnity::serialize<TYPE_NAME>(*ctx, *reinterpret_cast<TYPE_NAME*>(ptr)); }), \
	::omnity::create_vector_impl<TYPE_NAME>(),\
		{

#define FIELD(FIELD_NAME) \
{::omnity::field_metadata(\
	u""#FIELD_NAME,\
	field_index++,\
	get_field_type_id<decltype(__this_type::FIELD_NAME)>(),\
	get_field_type_index<decltype(__this_type::FIELD_NAME)>(),\
	::omnity::is_array_v<decltype(__this_type::FIELD_NAME)>,\
	offsetof(__this_type, FIELD_NAME))},

#define METADATA_END() \
}); return meta; }

namespace omnity {
	template<typename T>
	constexpr bool is_vector_v = false;
	template<typename... T>
	constexpr bool is_vector_v<std::vector<T...>> = true;
	template<typename T>
	constexpr bool is_array_v = is_vector_v<T>;
	template<typename T>
	constexpr type_id_t get_field_type_id() {
		if constexpr (is_array_v<T>)
			return type_id<typename T::value_type>;
		else
			return type_id<T>;
	}
	template<typename T>
	constexpr type_id_t get_field_type_index() {
		if constexpr (is_array_v<T>)
			return type_index<typename T::value_type>;
		else
			return type_index<T>;
	}
	struct serialize_ctx {
		using begin_object_f = void(*)();
		using end_object_f = void(*)();
		using begin_array_f = void(*)(size_t&);
		using end_array_f = void(*)();
		using write_key_f = void(*)(std::u16string_view key);
		using value_bool_f = void(*)(bool&);
		using value_int8_f = void(*)(int8_t&);
		using value_int16_f = void(*)(int16_t&);
		using value_int32_f = void(*)(int32_t&);
		using value_int64_f = void(*)(int64_t&);
		using value_uint8_f = void(*)(uint8_t&);
		using value_uint16_f = void(*)(uint16_t&);
		using value_uint32_f = void(*)(uint32_t&);
		using value_uint64_f = void(*)(uint64_t&);
		using value_float_f = void(*)(float&);
		using value_double_f = void(*)(double&);
		begin_object_f begin_object;
		end_object_f end_object;
		begin_array_f begin_array;
		end_array_f end_array;
		write_key_f set_key;
		value_bool_f value_bool;
		value_int8_f value_int8;
		value_int16_f value_int16;
		value_int32_f value_int32;
		value_int64_f value_int64;
		value_uint8_f value_uint8;
		value_uint16_f value_uint16;
		value_uint32_f value_uint32;
		value_uint64_f value_uint64;
		value_float_f value_float;
		value_double_f value_double;
	};
	serialize_ctx get_debug_serializer_ctx();
	inline void default_object_serialize(serialize_ctx& ctx, const type_metadata* type_meta, void* ptr) {
		ctx.begin_object();
		for (auto& field : type_meta->get_fields()) {
			ctx.set_key(field.name);
			void* field_value_ptr = static_cast<char*>(ptr) + field.offset;
			if (field.is_array) {
				auto& vector_impl = field.get_type_metadata()->vector_impl;
				auto size = vector_impl.get_size(field_value_ptr);
				ctx.begin_array(size);
				for (size_t i=0;i<size;++i) {
					auto elem = vector_impl.get_element(field_value_ptr, i);
					field.get_type_metadata()->serializer.serialize(&ctx, elem);
				}
				ctx.end_array();
			}
			else {
				field.get_type_metadata()->serializer.serialize(&ctx, field_value_ptr);
			}
		}
		ctx.end_object();
	}
	template <typename T>
	void serialize(serialize_ctx& ctx, T& obj) {
		const type_metadata* type_meta = type_metadata_ptr<T>;
		default_object_serialize(ctx, type_meta, reinterpret_cast<void*>(&obj));
	}
	template <>
	inline void serialize<bool>(serialize_ctx& ctx, bool& obj) {
		ctx.value_bool(obj);
	}
	template <>
	inline void serialize<int8_t>(serialize_ctx& ctx, int8_t& obj) {
		ctx.value_int8(obj);
	}
	template <>
	inline void serialize<int16_t>(serialize_ctx& ctx, int16_t& obj) {
		ctx.value_int16(obj);
	}
	template <>
	inline void serialize<int32_t>(serialize_ctx& ctx, int32_t& obj) {
		ctx.value_int32(obj);
	}
	template <>
	inline void serialize<int64_t>(serialize_ctx& ctx, int64_t& obj) {
		ctx.value_int64(obj);
	}
	template <>
	inline void serialize<uint8_t>(serialize_ctx& ctx, uint8_t& obj) {
		ctx.value_uint8(obj);
	}
	template <>
	inline void serialize<uint16_t>(serialize_ctx& ctx, uint16_t& obj) {
		ctx.value_uint16(obj);
	}
	template <>
	inline void serialize<uint32_t>(serialize_ctx& ctx, uint32_t& obj) {
		ctx.value_uint32(obj);
	}
	template <>
	inline void serialize<uint64_t>(serialize_ctx& ctx, uint64_t& obj) {
		ctx.value_uint64(obj);
	}
}
