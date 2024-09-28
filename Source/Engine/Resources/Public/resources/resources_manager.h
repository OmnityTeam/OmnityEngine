#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <any>
#include <atomic>
#include <base/omnity_types.h>
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
	class resource_ref_ctrl_block : noncopyable {
		friend class resource_ref;
		std::any res_;
		std::atomic_bool valid_;
		std::atomic_size_t ref_count_;
		template <typename TRes>
		explicit resource_ref_ctrl_block(TRes res) : res_(res), valid_(true), ref_count_(0) {}
		void increase_ref() {
			++ref_count_;
		}
		void decrease_ref() {
			--ref_count_;
		}
	};
	class resource_ref {
	private:
		resource_ref_ctrl_block* ctrl_;
    };
	template <typename TRes, typename... TArgs>
	resource_ref make_resource(TArgs... args) {
		auto ctrl = new resource_ref_ctrl_block(std::make_any<TRes>(std::forward<TArgs>(args)...));
	}
    class resources_manager final {
        using resource_set = std::unordered_map<std::u16string_view, resource_ref>;
        resource_set asset_dict_;
    public:
		void a() {
			std::shared_ptr<int> a;
		}

        static void initialize();
        static void destroy();
        static resources_manager* get_instance();
    };
	template <typename T>
	void resource_binary_serialize(std::ostream out) {
		
	}
}
