#pragma once
#include <concepts>
#include <type_traits>
#include <functional>
#include <memory>
#include <map>

namespace omnity::graphic::backend {
    class graphic_context;
    class graphic_backend;

    class graphic_backend {
    public:
        graphic_backend(graphic_backend&) = delete;
        graphic_backend(graphic_backend&&) = delete;
        graphic_backend& operator=(graphic_backend&) = delete;
        graphic_backend& operator=(graphic_backend&&) = delete;
        graphic_backend() = default;
        virtual bool setup() = 0;
        virtual std::weak_ptr<graphic_context> get_context() = 0;
        virtual ~graphic_backend() = default;
    };
    class graphic_context {
    public:
        graphic_context(graphic_context&) = delete;
        graphic_context(graphic_context&&) = delete;
        graphic_context& operator=(graphic_context&) = delete;
        graphic_context& operator=(graphic_context&&) = delete;
        graphic_context() = default;
        virtual bool setup_context() = 0;
        virtual ~graphic_context() = default;
    };

    using graphic_backend_factory = std::function<std::unique_ptr<graphic_backend>()>;
    void register_graphic_backend_factory_impl(uint8_t id, const graphic_backend_factory& factory);
    template<class T>
    concept graphic_backend_type = std::is_base_of_v<graphic_backend, T>;
    template<short Id, graphic_backend_type T, typename ...Args>
    void register_graphic_backend(Args... args) {
        register_graphic_backend_factory_impl(Id,
            [&args...]()
            {
                return std::unique_ptr<graphic_backend>(static_cast<graphic_backend*>(new T(args...)));
            });
    }

    const graphic_backend_factory& get_graphic_backend_factory(uint8_t id);
}