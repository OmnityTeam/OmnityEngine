#pragma once
#include <graphic/texture.h>

namespace omnity {
	inline void import_texture(importer_context& ctx, [[maybe_unused]] std::u16string_view path) {
		ctx.add<texture>(1);
	}
}