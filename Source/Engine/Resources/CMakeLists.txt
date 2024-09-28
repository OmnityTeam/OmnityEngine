# Resources
omnity_add_target(Resources)
target_sources(Resources PRIVATE "Src/resources_manager.cpp"  )
target_link_libraries(Resources Base)
find_path(REFL_CPP_INCLUDE_DIRS "refl.hpp")
target_include_directories(Resources PRIVATE ${REFL_CPP_INCLUDE_DIRS})
find_package(cereal CONFIG REQUIRED)
target_link_libraries(Base PRIVATE cereal::cereal)