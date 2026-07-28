cmake_minimum_required(VERSION 4.2.3)

# if (MSVC)
#     add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
#     add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
#     add_compile_options("/import:std")
# endif ()

# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_SCAN_FOR_MODULES ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD 451f2fe2-a8a2-47c3-bc32-94786d8fc91b)
# set(CMAKE_CXX_MODULE_STD ON)

project(Miriya)
set(ENABLE_CPP20_MODULE ON)

#option(BOX2D_BUILD_UNIT_TESTS "Build the Box2D unit tests" OFF)
#option(BOX2D_BUILD_TESTBED "Build the Box2D testbed" OFF)
#option(BOX2D_BUILD_DOCS "Build the Box2D documentation" OFF)
#option(BOX2D_USER_SETTINGS "Override Box2D settings with b2UserSettings.h" OFF)
#option(BUILD_SHARED_LIBS "Build Box2D as a shared library" ON)



# Collect source files
file(GLOB_RECURSE MIRIYA_SOURCES
        "src/*.cpp"
        "vendor/stb_image/*.cpp"
        "vendor/glm/glm/*.inl"
#        "vendor/ImGuizmo/ImGuizmo.cpp"
)

file(GLOB_RECURSE MIRIYA_HEADERS
        "src/*.h"
        "include/*.h"
        # "vendor/stb_image/*.h"
#        "vendor/ImGuizmo/ImGuizmo.h"
)

# Create the static library
add_library(Miriya STATIC ${MIRIYA_SOURCES} ${MIRIYA_HEADERS})

target_precompile_headers(${PROJECT_NAME} PUBLIC "src/mirpch.h")

# add_compile_definitions(MIR_PLATFORM_WINDOWS)
add_compile_definitions(MIR_BUILD_DLL)
# add_compile_definitions(MIR_ENABLE_ASSERTS)

#target_compile_definitions(${PROJECT_NAME} PRIVATE
#        _CRT_SECURE_NO_WARNINGS
#        GLFW_INCLUDE_NONE
#)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/Miriya/include 
        ${CMAKE_SOURCE_DIR}/Miriya/src   
#        ${IncludeDir_Box2D}
#        ${IncludeDir_filewatch}
        vendor/stb_image
#        ${IncludeDir_mono}
#        ${IncludeDir_yaml_cpp}
#        ${IncludeDir_ImGuizmo}
#        ${IncludeDir_VulkanSDK}
)

# vulkan
find_package(Vulkan REQUIRED)
add_library(VulkanCppModule)
add_library(Vulkan::cppm ALIAS VulkanCppModule)
target_compile_definitions(VulkanCppModule PUBLIC
        VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
        VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1
        VULKAN_HPP_CXX_MODULE_EXPERIMENTAL_WARNING=1
)
target_include_directories(VulkanCppModule PRIVATE "${Vulkan_INCLUDE_DIR}")

target_link_libraries(VulkanCppModule PUBLIC Vulkan::Vulkan)

target_sources(VulkanCppModule
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES
        BASE_DIRS 
            "${Vulkan_INCLUDE_DIR}"
        FILES "${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm"
              "${Vulkan_INCLUDE_DIR}/vulkan/vulkan_video.cppm"
)

# Vulkan SDK 的 shaderc_combined.lib 是 Release(MD) 静态库，与 Debug(MDd) 混链会 LNK2038。
# 因此 Debug 改用动态库 shaderc_shared(导入库，运行时不冲突)；其余配置仍用静态 combined 库。
# 注意：VS 是 multi-config 生成器，CMAKE_BUILD_TYPE 为空，必须用 generator expression 区分配置。
find_library(SHADERC_LIB_DEBUG   NAMES shaderc_shared   HINTS "$ENV{VULKAN_SDK}/Lib")
find_library(SHADERC_LIB_RELEASE NAMES shaderc_combined HINTS "$ENV{VULKAN_SDK}/Lib")
# Debug 依赖 shaderc_shared.dll，构建后复制到可执行文件目录
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$ENV{VULKAN_SDK}/Bin/shaderc_shared.dll"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        box2d
        glad
        glfw
        glm::glm
        spdlog
        imgui
        EnTT::EnTT
        yaml-cpp::yaml-cpp
        imguizmo
        # ${Library_mono}

    PRIVATE
        Vulkan::cppm
        # shaderc
        $<IF:$<CONFIG:Debug>,${SHADERC_LIB_DEBUG},${SHADERC_LIB_RELEASE}>
        spirv-cross-core
        spirv-cross-glsl
)


if(MSVC)
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${Library_WinSock}
                ${Library_WinMM}
                ${Library_WinVersion}
                ${Library_BCrypt}
                opengl32.lib
        )
    endif()

    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:/EHsc>
    )

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DEBUG)
        target_compile_options(${PROJECT_NAME} PRIVATE /Od)
        # target_link_libraries(${PROJECT_NAME} PRIVATE
        #         ${Library_ShaderC_Debug}
        #         ${Library_SPIRV_Cross_Debug}
        #         ${Library_SPIRV_Cross_GLSL_Debug}
        # )
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_RELEASE)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
        # target_link_libraries(${PROJECT_NAME} PRIVATE
        #         ${Library_ShaderC_Release}
        #         ${Library_SPIRV_Cross_Release}
        #         ${Library_SPIRV_Cross_GLSL_Release}
        # )
    elseif (CMAKE_BUILD_TYPE STREQUAL "Dist")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DIST)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
        # target_link_libraries(${PROJECT_NAME} PRIVATE
        #         ${Library_ShaderC_Release}
        #         ${Library_SPIRV_Cross_Release}
        #         ${Library_SPIRV_Cross_GLSL_Release}
        # )
    endif()
else ()

    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${Library_WinSock}
                ${Library_WinMM}
                ${Library_WinVersion}
                ${Library_BCrypt}
                opengl32.lib
        )
    endif()

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DEBUG)
        #    target_link_libraries(${PROJECT_NAME} PRIVATE
        #            ${Library_ShaderC_Debug}
        #            ${Library_SPIRV_Cross_Debug}
        #            ${Library_SPIRV_Cross_GLSL_Debug}
        #    )
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_RELEASE)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
        #    target_link_libraries(${PROJECT_NAME} PRIVATE
        #            ${Library_ShaderC_Release}
        #            ${Library_SPIRV_Cross_Release}
        #            ${Library_SPIRV_Cross_GLSL_Release}
        #    )
    elseif (CMAKE_BUILD_TYPE STREQUAL "Dist")
        target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DIST)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
        #    target_link_libraries(${PROJECT_NAME} PRIVATE
        #            ${Library_ShaderC_Release}
        #            ${Library_SPIRV_Cross_Release}
        #            ${Library_SPIRV_Cross_GLSL_Release}
        #    )
    endif()

endif ()