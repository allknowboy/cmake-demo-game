cmake_minimum_required(VERSION 3.10)

project(cmake-demo-game)

set (CMAKE_CXX_STAND 11)

set (SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set (3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)
set(CMAKE_MODULE_PATH ${3RD_DIR})

include_directories (${SRC_DIR})

# tiny_obj_loader
include_directories (${3RD_DIR}/tinyobjloader/include)

# glfw
set (GLFW_DIR ${3RD_DIR}/glfw)
# 保证glfw dir被编译
add_subdirectory (${GLFW_DIR})
# 添加头文件搜索路径
include_directories (${GLFW_DIR}/include)

# glad
set (GLAD_DIR ${3RD_DIR}/glad)
# 保证glfw dir被编译
add_subdirectory (${GLAD_DIR})
# 添加头文件搜索路径
include_directories (${GLAD_DIR}/include)

# easy_profiler
set (EASY_PROFILER_DIR ${3RD_DIR}/easyprofiler)
# 保证easy_profiler被编译
add_subdirectory (${EASY_PROFILER_DIR})
# 添加头文件搜索路径
include_directories (${EASY_PROFILER_DIR}/easy_profiler_core/include)

# glm
set (GLM_DIR ${3RD_DIR}/glm)
# 添加头文件搜索路径
include_directories (${GLM_DIR})

# stb
set (STB_DIR ${3RD_DIR}/stb)
# 添加头文件搜索路径
include_directories (${STB_DIR})

# yaml
set (YAML_CPP_DIR ${3RD_DIR}/yaml)
# 保证easy_profiler被编译
add_subdirectory (${YAML_CPP_DIR})
# 添加头文件搜索路径
include_directories (${YAML_CPP_DIR}/include)

# fmt
set(FMT_DIR ${3RD_DIR}/fmt)
add_subdirectory(${FMT_DIR})
include_directories(${FMT_DIR}/include)

# rttr
set(RTTR_DIR ${3RD_DIR}/rttr)
add_subdirectory(${RTTR_DIR})
include_directories(${RTTR_DIR}/src)


add_subdirectory(${PROJECT_SOURCE_DIR}/tools/compress)
add_subdirectory(${PROJECT_SOURCE_DIR}/examples)

# 设置MSVC编译编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

add_executable(${PROJECT_NAME}
src/vertex_data.h
src/component/component.cpp
src/component/component.h
src/component/game_object.cpp
src/component/game_object.h
src/component/transform.cpp
src/component/transform.h
src/control/input.cpp
src/control/input.h
src/control/key_code.h
src/renderer/mesh_filter.h
src/renderer/mesh_filter.cpp
src/renderer/shader.h
src/renderer/shader.cpp
src/renderer/material.h
src/renderer/material.cpp
src/renderer/texture2d.h
src/renderer/texture2d.cpp
src/renderer/mesh_renderer.h
src/renderer/mesh_renderer.cpp
src/renderer/camera.cpp
src/renderer/camera.h
src/utils/application.h
src/utils/application.cpp
src/main.cpp
)

# 添加链接库
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL32 glfw glad easy_profiler yaml-cpp fmt::fmt rttr_core_lib)
