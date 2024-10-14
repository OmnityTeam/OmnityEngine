#pragma once
#include <base/serialize.h>
#include <base/serialized_basic_types.h>

namespace omnity {
	class texture {
	public:
		METADATA_BEGIN(texture)
			FIELD(w_)
			FIELD(h_)
			FIELD(data_)
		METADATA_END()
	private:
		uint32_t w_, h_;
		binary_block_t data_;
	public:
		texture() = default;
		texture(uint32_t w, uint32_t h) : w_(w), h_(h) {}
		void set_data(const std::vector<uint8_t>& data) {
			data_ = data;
		}
	};
}
