# Graphic
omnity_add_target(Graphic)
target_sources(Graphic PRIVATE "Src/graphic.cpp" "Src/material.cpp" "Src/mesh.cpp" "Src/particle.cpp" "Src/shader.cpp" "Src/texture.cpp")
target_link_libraries(Graphic PRIVATE GraphicBackend)

set(GRAPHIC_USE_VULKAN ON CACHE BOOL "Enable Vulkan support?")
set(GRAPHIC_USE_DX12 OFF CACHE BOOL "Enable DX12 support?")

target_link_libraries(Graphic PRIVATE Base)

if ($CACHE{GRAPHIC_USE_VULKAN})
	message("Enable Vulkan support")
	target_link_libraries(Graphic PRIVATE GraphicBackendVulkan)
	target_compile_definitions(Graphic PRIVATE GRAPHIC_BACKEND_VULKAN)
endif()

if ($CACHE{GRAPHIC_USE_DX12})
	message("Enable DX12 support")
	target_link_libraries(Graphic PRIVATE GraphicBackendDX12)
	target_compile_definitions(Graphic PRIVATE GRAPHIC_BACKEND_DX12)
endif()