# Resources
omnity_add_target(Resources)
target_sources(Resources PRIVATE "Src/resources_manager.cpp"  )
target_link_libraries(Resources Base)