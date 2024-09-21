# Base utils
omnity_add_target(Base)

target_sources(Base PRIVATE "Src/logger.cpp" "Src/omnity_string.cpp")
find_package(utf8cpp CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(stduuid CONFIG REQUIRED)
target_link_libraries(Base PRIVATE utf8cpp::utf8cpp)
target_link_libraries(Base PUBLIC fmt::fmt)
target_link_libraries(Base PUBLIC stduuid)