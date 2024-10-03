# Core
omnity_add_target(Core)
target_sources(Core PRIVATE "Src/application.cpp")
target_link_libraries(Core Base Graphic Resources)