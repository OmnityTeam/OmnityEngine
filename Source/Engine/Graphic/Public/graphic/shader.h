#pragma once
#include <base/internal_types.h>

namespace omnity {
	class shader {
	public:
		template <class Archive>
		void save([[maybe_unused]] Archive& ar) const
		{
		}
		template <class Archive>
		void load([[maybe_unused]] Archive& ar)
		{
		}
	};
	DEFINE_CTOR(shader) {
		return std::make_any<shader>();
	}
	ENABLE_SERIALIZE(shader, BinaryOutputArchive);
	ENABLE_DESERIALIZE(shader, BinaryInputArchive);
}