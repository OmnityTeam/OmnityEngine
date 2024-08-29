# Graphic Backend Vulkan
omnity_define_module()
omnity_module_dependencies(GraphicBackend)

find_package(Vulkan)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
omnity_module_link_libraries(Vulkan::Vulkan GPUOpen::VulkanMemoryAllocator)