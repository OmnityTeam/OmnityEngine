# Graphic Backend Vulkan
omnity_add_target(GraphicBackendVulkan)
target_sources(GraphicBackendVulkan PRIVATE src/VulkanBackend.cpp)
target_link_libraries(GraphicBackendVulkan PRIVATE GraphicBackend)

find_package(Vulkan)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
target_link_libraries(GraphicBackendVulkan PRIVATE Vulkan::Vulkan GPUOpen::VulkanMemoryAllocator)