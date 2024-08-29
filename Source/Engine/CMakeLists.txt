omnity_add_library(OmnityRuntime SHARED)
omnity_target_link_module(OmnityRuntime Core)

omnity_add_executable(OmnityApp)
target_link_libraries(OmnityApp OmnityRuntime)
if(WIN32 AND MSVC)
	target_compile_options(OmnityApp PRIVATE /sdl- /GS-)
	target_link_options(OmnityApp PRIVATE /NODEFAULTLIB /ENTRY:main)
endif()