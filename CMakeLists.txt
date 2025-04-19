cmake_minimum_required(VERSION 3.10)

project(Software_Udvikling)


# Automatically find all .cpp files
file(GLOB SRC_FILES "*.cpp")

# Create the executable with all source files
add_executable(main ${SRC_FILES})
