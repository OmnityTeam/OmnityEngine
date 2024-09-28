#pragma once
#include <base/internal_types.h>

namespace omnity {
	class texture {
	private:
		uint32_t w_, h_;
	public:
		texture() = default;
		texture(uint32_t w, uint32_t h) : w_(w), h_(h) {}
		template <class Archive>
		void save(Archive& ar) const
		{
			ar& w_;
			ar& h_;
		}

		template <class Archive>
		void load(Archive& ar)
		{
			ar& w_;
			ar& h_;
		}
	};
	DEFINE_CTOR(texture) {
		return std::make_any<texture>();
	}
	ENABLE_SERIALIZE(texture, BinaryOutputArchive);
	ENABLE_DESERIALIZE(texture, BinaryInputArchive);
	
}
