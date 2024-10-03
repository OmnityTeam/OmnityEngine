#include <gtest/gtest.h>
#include <graphic/graphic.h>
#include <base/scene.h>
#include <base/types.h>
#include <chrono>

TEST(base, type_system) {
	ASSERT_EQ(omnity::type_index<omnity::texture>, omnity::type_index_by_id<omnity::type_id<omnity::texture>>);
	ASSERT_EQ(omnity::type_id<omnity::texture>, omnity::type_id_by_index<omnity::type_index<omnity::texture>>);
	ASSERT_EQ(omnity::type_index<omnity::material>, omnity::type_index_by_id<omnity::type_id<omnity::material>>);
	ASSERT_EQ(omnity::type_id<omnity::material>, omnity::type_id_by_index<omnity::type_index<omnity::material>>);
	ASSERT_EQ(omnity::type_index<omnity::shader>, omnity::type_index_by_id<omnity::type_id<omnity::shader>>);
	ASSERT_EQ(omnity::type_id<omnity::shader>, omnity::type_id_by_index<omnity::type_index<omnity::shader>>);

	auto type_metadata = omnity::get_type_table()->get_type_metadata_by_id(omnity::type_id<omnity::texture>);
	ASSERT_EQ(omnity::type_id<omnity::texture>, type_metadata->type_id);
	ASSERT_EQ(omnity::get_type_table()->get_type_metadata<omnity::texture>()->type_id, type_metadata->type_id);
	auto first_field = type_metadata->get_field(0);
	auto start = std::chrono::steady_clock::now();
	const omnity::field_metadata* a = nullptr;
	for (int i = 0; i < 1000000; ++i) {
		a = type_metadata->try_get_field(first_field->name);
	}
	auto stop = std::chrono::steady_clock::now();
	GTEST_LOG_(INFO) << stop - start;
	GTEST_LOG_(INFO) << a;
	//omnity::type_serializer<omnity::type_id<omnity::texture>>::type_instance_load(ar, 1920, 1080);
}