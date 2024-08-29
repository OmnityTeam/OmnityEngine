# Graphic
omnity_define_module()
omnity_module_dependencies(GraphicBackend)

set(GRAPHIC_USE_VULKAN ON CACHE BOOL "Enable Vulkan support?")
set(GRAPHIC_USE_DX12 OFF CACHE BOOL "Enable DX12 support?")

if ($CACHE{GRAPHIC_USE_VULKAN})
	message("Enable Vulkan support")
	omnity_module_dependencies(GraphicBackendVulkan)
	omnity_add_compile_definitions(GRAPHIC_BACKEND_VULKAN)
endif()

if ($CACHE{GRAPHIC_USE_DX12})
	message("Enable DX12 support")
	omnity_module_dependencies(GraphicBackendDX12)
	omnity_add_compile_definitions(GRAPHIC_BACKEND_DX12)
endif()