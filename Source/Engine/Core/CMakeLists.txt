# Core
omnity_add_target(Core)
target_sources(Core PRIVATE src/Application.cpp)
target_link_libraries(Core Base Graphic Resources)