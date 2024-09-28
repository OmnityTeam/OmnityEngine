# Resources
omnity_add_target(Resources)
target_sources(Resources PRIVATE "Src/resources_manager.cpp"  )
target_link_libraries(Resources Base)
find_package(cereal CONFIG REQUIRED)
target_link_libraries(Base PRIVATE cereal::cereal)