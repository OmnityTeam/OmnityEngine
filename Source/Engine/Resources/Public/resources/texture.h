#pragma once

namespace omnity {
    class texture {
        uint32_t w_, h_;
    public:
        texture(const texture&) = delete;
        texture(const texture&&) = delete;
        texture(const uint32_t width, const uint32_t height) :
            w_(width), h_(height) {}
        uint32_t width() const {
            return w_;
        }
        uint32_t height() const {
            return w_;
        }
    };
}