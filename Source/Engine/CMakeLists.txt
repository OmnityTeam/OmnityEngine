project(Engine)
add_subdirectory(Base)
add_subdirectory(Core)
add_subdirectory(Graphic)
add_subdirectory(GraphicBackend)
add_subdirectory(GraphicBackendVulkan)
add_subdirectory(Resources)

add_library(OmnityRuntime "omnity_runtime.cpp")
target_link_libraries(OmnityRuntime Core)

add_executable(OmnityApp "omnity_app.cpp" OmnityApp.rc)
target_link_libraries(OmnityApp OmnityRuntime)