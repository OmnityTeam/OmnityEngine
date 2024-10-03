#pragma once
#include <base/types.h>

namespace omnity {
	class texture {
	public:
		METADATA_BEGIN(texture)
			FIELD(w_)
			FIELD(h_)
		METADATA_END()
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
}
