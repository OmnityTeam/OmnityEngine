#include <exception>
#include <base/type.h>
#include <base/serialize.h>

#define DEFINE_BASIC_TYPE(TYPE_NAME)\
const type_metadata& GET_METADATA_GLOBAL_FUNC_NAME(TYPE_NAME)() {\
	static type_metadata meta(\
		u""#TYPE_NAME,\
		::omnity::type_index<TYPE_NAME>,\
		::omnity::type_id<TYPE_NAME>,\
		::omnity::serializer_t(\
			[](serialize_ctx* ctx, void* ptr) { omnity::serialize<TYPE_NAME>(*ctx, *reinterpret_cast<TYPE_NAME*>(ptr)); }),\
		::omnity::create_vector_impl<TYPE_NAME>(),\
		{});\
	return meta;\
}\

namespace {
	template<int Cur = 0>
	void build_type_cache(omnity::type_table::type_cache_t& type_cache) {
		if constexpr (Cur != omnity::type_count) {
			type_cache[Cur] = omnity::type_metadata_ptr_by_index<Cur>;
			build_type_cache<Cur + 1>(type_cache);
		}
	}
	void build_type_map(const omnity::type_table::type_cache_t& type_cache, omnity::type_table::type_map_t& type_map) {
		for (size_t i = 0; i < omnity::type_count; ++i)
			type_map.emplace(type_cache[i]->type_id, i);
	}
}
namespace omnity{
	type_table::type_table() {
		build_type_cache(type_cache_);
		build_type_map(type_cache_, type_map_);
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

	const type_table type_table_instance;
}