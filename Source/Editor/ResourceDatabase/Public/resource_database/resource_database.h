#pragma once
#include <base/types.h>
#include <filesystem>
#include <resources/resources.h>
#include <resource_importers/importers.h>

namespace omnity {
	class resource_database {
		resource_database() = default;
		~resource_database() = default;
		std::map<std::u16string_view, resource_package> _resDb;
	public:
		resource_database(const resource_database&) = delete;
		resource_database(const resource_database&&) = delete;
		resource_database& operator =(const resource_database&) = delete;
		resource_database& operator =(const resource_database&&) = delete;
		static resource_database& get_instance() {
			static resource_database db;
			return db;
		}
		void refresh_resource(std::u16string_view path);
	};
}
