#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <any>
#include <atomic>
#include <base/types.h>
#include <fstream>

namespace omnity {
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
		std::filebuf buf_;
	public:
		resource_package(std::u16string_view path);
	};
}
