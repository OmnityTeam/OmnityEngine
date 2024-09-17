# Resources
omnity_add_target(Resources)
target_sources(Resources PRIVATE src/ResourcesManager.cpp "src/ResourceProvider.cpp" "src/ResourcePackage.cpp")
target_link_libraries(Resources Base)