# Resources
omnity_add_target(Resources)
target_sources(Resources PRIVATE "Src/resources_manager.cpp" "Src/resource_provider.cpp" "Src/resource_package.cpp")
target_link_libraries(Resources Base)