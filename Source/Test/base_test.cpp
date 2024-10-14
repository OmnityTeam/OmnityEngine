#include <gtest/gtest.h>
#include <graphic/graphic.h>
#include <base/scene.h>
#include <base/type.h>
#include <chrono>

#include "base/string_utils.h"

TEST(base, type_system) {
	ASSERT_EQ(omnity::type_index<omnity::texture>, omnity::type_index_by_id<omnity::type_id<omnity::texture>>);
	ASSERT_EQ(omnity::type_id<omnity::texture>, omnity::type_id_by_index<omnity::type_index<omnity::texture>>);
	ASSERT_EQ(omnity::type_index<omnity::material>, omnity::type_index_by_id<omnity::type_id<omnity::material>>);
	ASSERT_EQ(omnity::type_id<omnity::material>, omnity::type_id_by_index<omnity::type_index<omnity::material>>);
	ASSERT_EQ(omnity::type_index<omnity::shader>, omnity::type_index_by_id<omnity::type_id<omnity::shader>>);
	ASSERT_EQ(omnity::type_id<omnity::shader>, omnity::type_id_by_index<omnity::type_index<omnity::shader>>);
	
	auto type_metadata = omnity::type_table_instance.try_get_type_metadata_by_id(omnity::type_id<omnity::texture>);
	ASSERT_EQ(omnity::type_id<omnity::texture>, type_metadata->type_id);
	ASSERT_EQ(omnity::type_table_instance.get_type_metadata<omnity::texture>()->type_id, type_metadata->type_id);
	auto first_field = type_metadata->get_field(0);
	auto start = std::chrono::steady_clock::now();
	std::u16string_view name;
	for (int i = 0; i < 1000000; ++i) {
		auto field = type_metadata->try_get_field(first_field->name);
		name = field->name;
	}
	auto stop = std::chrono::steady_clock::now();
	GTEST_LOG_(INFO) << static_cast<double>(duration_cast<std::chrono::nanoseconds>(stop - start).count()) / 1e6 << "ms 1000000 times"; \
	GTEST_LOG_(INFO) << omnity::string_utils::to_utf8(name);
	//omnity::type_serializer<omnity::type_id<omnity::texture>>::type_instance_load(ar, 1920, 1080);
}