#pragma once
#include <memory>
#include <graphic_backend/graphic_backend.h>

namespace omnity::graphic::backend::vulkan {
    class vulkan_context;
    class vulkan_backend final : public graphic_backend {
        std::shared_ptr<vulkan_context> context_;
    public:
        bool setup() override;
        std::weak_ptr<graphic_context> get_context() override;
        ~vulkan_backend() override;
    };
}