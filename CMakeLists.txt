cmake_minimum_required(VERSION 3.20)
project(Miriya)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    add_compile_definitions(NOMINMAX)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# Dependencies.cmake in modules folder
#include(Dependencies)

# set(CMAKE_GENERATOR_PLATFORM x64)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# set_property(GLOBAL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Set output directories for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Dependencies
#add_subdirectory(Miriya/vendor/Box2D)
add_subdirectory(Miriya/vendor/glfw-3.4)
add_subdirectory(Miriya/vendor/glm-1.0.2)
add_subdirectory(Miriya/vendor/GLAD)
add_subdirectory(Miriya/vendor/imgui)
add_subdirectory(Miriya/vendor/entt-3.16)
add_subdirectory(Miriya/vendor/spdlog-1.15.3)
#add_subdirectory(Miriya/vendor/yaml-cpp)

# core
add_subdirectory(Miriya)
# editor
add_subdirectory(Editor)
# Misc
add_subdirectory(Sandbox)

add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)

