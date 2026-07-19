cmake_minimum_required(VERSION 3.20)
project(Ruslan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


file(GLOB_RECURSE RUSLAN_SOURCES
    src/*.cpp
)

file(GLOB_RECURSE RUSLAN_HEADERS
    src/*.h
    ${CMAKE_SOURCE_DIR}/Miriya/vendor/entt/*.hpp
)

add_executable(${PROJECT_NAME} ${RUSLAN_SOURCES} ${RUSLAN_HEADERS})

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Miriya/include
    ${CMAKE_SOURCE_DIR}/Miriya/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Miriya/vendor
    ${CMAKE_SOURCE_DIR}/Miriya/vendor/entt
    ${IncludeDir_filewatch}
    ${CMAKE_SOURCE_DIR}/Miriya/vendor/glm
    ${IncludeDir_ImGuizmo}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Miriya
)

# if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
#     target_compile_definitions(${PROJECT_NAME} PRIVATE
#         MIR_PLATFORM_WINDOWS
#     )
# endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE /Od /Zi)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${Library_ShaderC_Debug}
        ${Library_SPIRV_Cross_Debug}
        ${Library_SPIRV_Cross_GLSL_Debug}
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_RELEASE)
    target_compile_options(${PROJECT_NAME} PRIVATE /O2)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${Library_ShaderC_Release}
        ${Library_SPIRV_Cross_Release}
        ${Library_SPIRV_Cross_GLSL_Release}
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Dist")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MIR_DIST)
    target_compile_options(${PROJECT_NAME} PRIVATE /O2)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${Library_ShaderC_Release}
        ${Library_SPIRV_Cross_Release}
        ${Library_SPIRV_Cross_GLSL_Release}
    )
endif()