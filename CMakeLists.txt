# Initialize the project
cmake_minimum_required(VERSION 3.0)
project(run_code)
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

# Check if the file and out argument is provided
if(NOT DEFINED file)
    set(file "server.cpp")
endif()

if(NOT DEFINED out)
    set(out "server.out")
endif()

# Add the executable
add_executable(${out} ${file})

# Include directories
target_include_directories(${out} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Linked libraries
target_link_libraries(${out} PRIVATE /usr/local/lib/libmupdf.a)
target_link_libraries(${out} PRIVATE /usr/local/lib/libmupdf-third.a)
target_link_libraries(${out} PRIVATE m)