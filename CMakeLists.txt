cmake_minimum_required(VERSION 3.10)

project(Software_Udvikling)

find_package(Qt6 REQUIRED COMPONENTS Core Sql)

# Automatically find all .cpp files
file(GLOB SRC_FILES "*.cpp" CMAKE_CONFIGURE_DEPENDS)

# Create the executable with all source files
add_executable(main ${SRC_FILES})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main Qt6::Core Qt6::Sql)
