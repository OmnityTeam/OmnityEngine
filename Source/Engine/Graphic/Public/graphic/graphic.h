#pragma once

namespace omnity::graphic {
    constexpr int unknown_backend = 0;
    constexpr int vulkan_backend = 1;
    constexpr int dx12_backend = 2;

    bool check_backend(uint8_t backend_id);
    void init_graphic();
    bool setup_graphic_backend(uint8_t backend_id);
    bool setup_graphic_backend();
}