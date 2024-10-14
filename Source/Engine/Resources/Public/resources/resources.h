#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <any>
#include <atomic>
#include <base/type.h>
#include <fstream>

namespace omnity {
	struct resource_package_ptr;
	using resource_inner_id_t = uint32_t;
	struct resource_info {
		std::u16string path;
		uint32_t type;
		uint64_t size;
		uint64_t offset;
	};
	struct resource_package_manifest {
		std::vector<std::u16string> depends;
		std::vector<resource_info> infos;
	};
	class resource_package {
		std::map<resource_inner_id_t, resource_package_ptr> _map;
	public:
		resource_package(std::u16string_view path);
	};
	struct resource_package_ptr {
		std::streamoff off;
	};
}
