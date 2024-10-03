#pragma once
#include <base/types.h>

namespace omnity {
	class scene {
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
	ENABLE_SERIALIZE(scene, BinaryOutputArchive);
	ENABLE_DESERIALIZE(scene, BinaryInputArchive);
	DEFINE_CTOR(scene) {
		return std::make_any<scene>();
	}

	class scene_node {
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
	ENABLE_SERIALIZE(scene_node, BinaryOutputArchive);
	ENABLE_DESERIALIZE(scene_node, BinaryInputArchive);
	DEFINE_CTOR(scene_node) {
		return std::make_any<scene_node>();
	}
}