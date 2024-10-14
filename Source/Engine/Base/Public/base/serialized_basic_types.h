#pragma once
#include <base/serialize.h>

namespace omnity {
	template <>
	inline void serialize<binary_block_t>(serialize_ctx& ctx, binary_block_t& obj);
	class binary_block_t {
	public:
		METADATA_BEGIN(binary_block_t)
		METADATA_END()
		std::vector<uint8_t> data;
		binary_block_t& operator=(const std::vector<uint8_t>& d) {
			data = d;
			return *this;
		}
		binary_block_t& operator=(std::vector<uint8_t>&& d) {
			data = std::move(d);
			return *this;
		}
	};
	template <>
	inline void serialize<binary_block_t>([[maybe_unused]] serialize_ctx& ctx, [[maybe_unused]] binary_block_t& obj) {
		// TODO binary block serialization
	}
}