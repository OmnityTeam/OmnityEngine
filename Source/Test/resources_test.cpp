#include <resource_database/resource_database.h>
#include <graphic/texture.h>
#include <gtest/gtest.h>

TEST(resource, serialize) {
	omnity::texture tex(1, 2);
}

TEST(resource, register_and_get) {
	auto& db = omnity::resource_database::get_instance();
	db.refresh_resource(u"123.png");
}