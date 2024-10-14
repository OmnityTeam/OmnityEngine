#include <iostream>
#include <base/serialized_basic_types.h>

#include "base/string_utils.h"

namespace omnity {
	DEFINE_TYPE(binary_block_t);

	serialize_ctx get_debug_serializer_ctx() {
		omnity::serialize_ctx ctx;
		ctx.begin_object = []() { std::cout << "{"; };
		ctx.end_object = []() { std::cout << "}"; };
		ctx.begin_array = [](size_t& size) { std::cout << size << "["; };
		ctx.end_array = []() { std::cout << "]"; };
		ctx.set_key = [](std::u16string_view key) { std::cout << omnity::string_utils::to_utf8(key) << "="; };
		ctx.value_bool = [](bool& num) { std::cout << num; };
		ctx.value_int8 = [](int8_t& num) { std::cout << (int)num; };
		ctx.value_int16 = [](int16_t& num) { std::cout << num; };
		ctx.value_int32 = [](int32_t& num) { std::cout << num; };
		ctx.value_int64 = [](int64_t& num) { std::cout << num; };
		ctx.value_uint8 = [](uint8_t& num) { std::cout << (int)num; };
		ctx.value_uint16 = [](uint16_t& num) { std::cout << num; };
		ctx.value_uint32 = [](uint32_t& num) { std::cout << num; };
		ctx.value_uint64 = [](uint64_t& num) { std::cout << num; };
		ctx.value_float = [](float& num) { std::cout << num; };
		ctx.value_double = [](double& num) { std::cout << num; };
		return ctx;
	}
}
