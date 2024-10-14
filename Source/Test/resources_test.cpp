#include <resource_database/resource_database.h>
#include <graphic/texture.h>
#include <gtest/gtest.h>
#include <base/string_utils.h>

TEST(resource, serialize) {
	constexpr omnity::field_metadata fields[]{ omnity::field_metadata{u"123",0,0, 0,false, 0} };
	std::initializer_list(std::begin(fields), std::end(fields));

	omnity::texture tex(1, 2);
	tex.set_data({ 1,2,3,4 });
	omnity::serialize_ctx ctx;
	ctx.begin_object = []() { GTEST_LOG_(INFO) << "{"; };
	ctx.end_object = []() { GTEST_LOG_(INFO) << "}"; };
	ctx.begin_array = [](size_t& size) { GTEST_LOG_(INFO) << size << "["; };
	ctx.end_array = []() { GTEST_LOG_(INFO) << "]"; };
	ctx.set_key = [](std::u16string_view key) { GTEST_LOG_(INFO) << omnity::string_utils::to_utf8(key) << "="; };
	ctx.value_bool = [](bool& num) { GTEST_LOG_(INFO) << num; };
	ctx.value_int8 = [](int8_t& num) { GTEST_LOG_(INFO) << (int)num; };
	ctx.value_int16 = [](int16_t& num) { GTEST_LOG_(INFO) << num; };
	ctx.value_int32 = [](int32_t& num) { GTEST_LOG_(INFO) << num; };
	ctx.value_int64 = [](int64_t& num) { GTEST_LOG_(INFO) << num; };
	ctx.value_uint8 = [](uint8_t& num) { GTEST_LOG_(INFO) << (int)num; };
	ctx.value_uint16 = [](uint16_t& num) { GTEST_LOG_(INFO) << num; };
	ctx.value_uint32 = [](uint32_t& num) { GTEST_LOG_(INFO) << num; };
	ctx.value_uint64 = [](uint64_t& num) { GTEST_LOG_(INFO) << num; };
	ctx.value_float = [](float& num) { GTEST_LOG_(INFO) << num; };
	ctx.value_double = [](double& num) { GTEST_LOG_(INFO) << num; };

	omnity::serialize(ctx, tex);
}

TEST(resource, register_and_get) {
	auto& db = omnity::resource_database::get_instance();
	db.refresh_resource(u"123.png");
}