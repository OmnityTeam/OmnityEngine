#pragma once
#include <base/internal_types.h>

namespace omnity {
	class material {
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
	DEFINE_CTOR(material) {
		return std::make_any<material>();
	}
	ENABLE_SERIALIZE(material, BinaryOutputArchive);
	ENABLE_DESERIALIZE(material, BinaryInputArchive);
}