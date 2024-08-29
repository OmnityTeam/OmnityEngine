# Base utils
omnity_define_module()

find_package(utf8cpp CONFIG REQUIRED)
omnity_module_link_libraries(utf8cpp::utf8cpp)