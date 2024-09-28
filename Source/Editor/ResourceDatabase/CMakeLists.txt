# Asset Importer
omnity_add_target(ResourceDatabase)
target_sources(ResourceDatabase PRIVATE "Src/resource_database.cpp")
target_link_libraries(ResourceDatabase Engine::Base)