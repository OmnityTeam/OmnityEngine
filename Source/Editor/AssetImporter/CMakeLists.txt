# Asset Importer
omnity_add_target(AssetImporter)
target_sources(AssetImporter PRIVATE "Src/asset_importer.cpp")
target_link_libraries(AssetImporter Engine::Base)