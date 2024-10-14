# Base utils
omnity_add_target(Base)

target_sources(Base PRIVATE "Src/logger.cpp" "Src/string_utils.cpp" "Src/scene.cpp" "Src/type.cpp" "Src/serialize.cpp")
find_package(utf8cpp CONFIG REQUIRED)
find_package(unordered_dense CONFIG REQUIRED)
target_link_libraries(Base PRIVATE utf8cpp::utf8cpp)
target_link_libraries(Base PUBLIC unordered_dense::unordered_dense)