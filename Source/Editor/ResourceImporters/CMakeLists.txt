# Asset Importer
omnity_add_target(ResourceImporters)
target_sources(ResourceImporters PRIVATE "Src/resource_importers.cpp")
target_link_libraries(ResourceImporters Engine::Base Engine::Resources)