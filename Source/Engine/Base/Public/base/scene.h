#pragma once
#include <base/types.h>

namespace omnity {
	class scene {
	public:
		METADATA_BEGIN(scene)
		METADATA_END()
	};
	DEFINE_TYPE(scene);
	class scene_node {
	public:
		METADATA_BEGIN(scene_node)
		METADATA_END()
	};
	DEFINE_TYPE(scene_node);
}