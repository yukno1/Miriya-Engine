cmake_minimum_required(VERSION 4.2.3)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD 451f2fe2-a8a2-47c3-bc32-94786d8fc91b)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
add_compile_definitions(NOMINMAX)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("/import:std")
endif ()

project(Miriya-Workspace)

# 强制所有目标（含 SPIRV-Cross 静态库与 C++23 std 模块）运行时库一致：
# Debug -> /MDd，Release/RelWithDebInfo/MinSizeRel -> /MD
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
        CACHE STRING "MSVC runtime library for all targets" FORCE)
endif()

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
add_subdirectory(Miriya/vendor/yaml-cpp-0.9.0)
add_subdirectory(Miriya/vendor/box2d-3.1.1)

add_subdirectory(Miriya/vendor/ImGuizmo-1.10)
set_target_properties(imguizmo PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
target_link_libraries(imguizmo PUBLIC imgui)

add_subdirectory(Miriya/vendor/SPIRV-Cross)

# 只构建我们需要的静态库，跳过测试/示例/版权检查/安装
# set(SHADERC_SKIP_TESTS        ON CACHE BOOL "Skip shaderc tests"        FORCE)
# set(SHADERC_SKIP_EXAMPLES     ON CACHE BOOL "Skip shaderc examples"     FORCE)
# set(SHADERC_SKIP_EXECUTABLES  ON CACHE BOOL "Skip shaderc executables"  FORCE)
# set(SHADERC_SKIP_COPYRIGHT_CHECK ON CACHE BOOL "Skip copyright check"   FORCE)
# set(SHADERC_SKIP_INSTALL      ON CACHE BOOL "Skip shaderc install"      FORCE)
# add_subdirectory(Miriya/vendor/shaderc)

# core
add_subdirectory(Miriya)
# editor
add_subdirectory(Editor)
# Misc
add_subdirectory(Sandbox)

add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)

