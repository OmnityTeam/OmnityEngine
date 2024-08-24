# Graphic
omnity_define_module()
omnity_module_dependencies(RHI)

set(RHI_USE_VULKAN ON CACHE BOOL "Enable Vulkan support?")

if ($CACHE{RHI_USE_VULKAN})
	message("Enable Vulkan support")
	omnity_module_dependencies(RHIVulkan)
	omnity_add_compile_definitions(GRAPHIC_RHI_VULKAN)
endif()