#pragma once
#include <base/internal_types.h>

namespace omnity {
	class mesh {
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
	DEFINE_CTOR(mesh) {
		return std::make_any<mesh>();
	}
	ENABLE_SERIALIZE(mesh, BinaryOutputArchive);
	ENABLE_DESERIALIZE(mesh, BinaryInputArchive);
}