#pragma once
#include <base/internal_types.h>

namespace omnity {
	class particle {
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
	DEFINE_CTOR(particle) {
		return std::make_any<particle>();
	}
	ENABLE_SERIALIZE(particle, BinaryOutputArchive);
	ENABLE_DESERIALIZE(particle, BinaryInputArchive);
}