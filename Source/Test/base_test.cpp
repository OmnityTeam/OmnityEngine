#include <gtest/gtest.h>
#include <graphic/graphic.h>
#include <base/scene.h>
#include <base/types.h>
#include <cereal/archives/binary.hpp>

template <typename... TArgs>
static std::unique_ptr<void> type_instantiate([[maybe_unused]] TArgs&&... args) {
	return std::make_unique<omnity::texture, TArgs&&>(std::forward<TArgs&&>(args)...);
}

TEST(base, type_system) {
	ASSERT_EQ(omnity::type_index<omnity::texture>, omnity::type_index_by_id<omnity::type_id<omnity::texture>>);
	ASSERT_EQ(omnity::type_id<omnity::texture>, omnity::type_id_by_index<omnity::type_index<omnity::texture>>);
	ASSERT_EQ(omnity::type_index<omnity::material>, omnity::type_index_by_id<omnity::type_id<omnity::material>>);
	ASSERT_EQ(omnity::type_id<omnity::material>, omnity::type_id_by_index<omnity::type_index<omnity::material>>);
	ASSERT_EQ(omnity::type_index<omnity::shader>, omnity::type_index_by_id<omnity::type_id<omnity::shader>>);
	ASSERT_EQ(omnity::type_id<omnity::shader>, omnity::type_id_by_index<omnity::type_index<omnity::shader>>);
	GTEST_LOG_(INFO) << omnity::type_index<omnity::texture>;
	GTEST_LOG_(INFO) << omnity::type_index<omnity::material>;
	GTEST_LOG_(INFO) << omnity::type_index<omnity::shader>;
	auto table = omnity::type_table_global();
	omnity::type_table_global().ctor[omnity::type_index<omnity::texture>]();
	//omnity::type_serializer<omnity::type_id<omnity::texture>>::type_instance_load(ar, 1920, 1080);
}