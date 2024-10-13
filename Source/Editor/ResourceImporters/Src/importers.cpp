#include <resource_importers/importers.h>
#include "texture_importers.h"

namespace omnity {
	namespace {
		std::map<std::u16string_view, resource_importer> importer_map = {
			{u".png",import_texture}
		};
	}
	resource_importer importer_get(const std::u16string_view ext) {
		const auto ret = importer_map.find(ext);
		if (ret == importer_map.end()) return nullptr;
		return ret->second;
	}
}