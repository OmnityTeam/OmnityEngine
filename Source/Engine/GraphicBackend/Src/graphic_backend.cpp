#include <map>
#include <graphic_backend/graphic_backend.h>

namespace omnity::graphic::backend {
    class graphic_backend_factory_dict {
        std::map<uint8_t, graphic_backend_factory> factories_;
    public:
        void inline add_factory(const uint8_t id, const graphic_backend_factory& factory) {
            factories_[id] = factory;
        }
        inline const graphic_backend_factory* get_factory(const uint8_t id) const {
            const auto ret = factories_.find(id);
            return ret == factories_.end() ? nullptr : &ret->second;
        }
    };
    graphic_backend_factory_dict factory_dict;
    std::unique_ptr<graphic_backend> current_backend;

    void register_graphic_backend_factory_impl(const uint8_t id, const graphic_backend_factory& factory) {
        factory_dict.add_factory(id, factory);
    }

    const graphic_backend_factory& get_graphic_backend_factory(const uint8_t id) {
        return *factory_dict.get_factory(id);
    }
}