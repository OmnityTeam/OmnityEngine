#pragma once

namespace Omnity {
	class Texture {
		uint32_t _w, _h;
	public:
		Texture(const Texture&) = delete;
		Texture(const Texture&&) = delete;
		Texture(uint32_t width, uint32_t height) :
			_w(width), _h(height) {}
		uint32_t Width() const {
			return _w;
		}
		uint32_t Height() const {
			return _w;
		}
	};
}