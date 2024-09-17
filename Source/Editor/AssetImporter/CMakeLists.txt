# Asset Importer
omnity_add_target(AssetImporter)
target_sources(AssetImporter PRIVATE src/AssetImporter.cpp)
target_link_libraries(AssetImporter Engine::Base)