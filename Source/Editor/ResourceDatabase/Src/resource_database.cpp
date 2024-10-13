#include <resource_database/resource_database.h>

namespace omnity {
	static void export_resource_package(const importer_context& ctx, std::basic_ostream<char>& os) {
		for (const auto& val : ctx.get_cache() | std::views::values) {
			const auto type_info = get_type_table()->try_get_type_metadata_by_id(val.type_id);
			for (auto field : type_info->get_fields()) {
				[[maybe_unused]] auto field_type_meta = field.get_type_metadata();
				os.write((char*)&field.name[0], field.name.size() * 2);
			}
		}
	}
	void resource_database::refresh_resource(const std::u16string_view path) {
		const auto ret = _resDb.find(path);
		if (ret != _resDb.end()) _resDb.erase(ret);
		const auto dotPos = path.rfind('.');
		if (dotPos == std::string_view::npos || dotPos == 0)
			return;
		const auto ext = path.substr(dotPos);
		const auto importer = importer_get(ext);
		if (importer == nullptr) return;
		importer_context ctx;
		importer(ctx, path);
		// TODO: gen guid and save to specific resource database path
		std::stringstream ss;
		export_resource_package(ctx, ss);
	}
}
