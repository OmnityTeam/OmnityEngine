# Graphic Backend Vulkan
omnity_add_target(GraphicBackendVulkan)
target_sources(GraphicBackendVulkan PRIVATE "Src/vulkan_backend.cpp")
target_link_libraries(GraphicBackendVulkan PRIVATE GraphicBackend)

set(ENV{VULKAN_SDK} "F:/AndroidSDK/ndk/28.0.12433566/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/")
find_package(Vulkan)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
target_link_libraries(GraphicBackendVulkan PRIVATE Vulkan::Vulkan GPUOpen::VulkanMemoryAllocator)