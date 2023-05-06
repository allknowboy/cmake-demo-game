cmake_minimum_required(VERSION 3.10)

project(myGame)

set (CMAKE_CXX_STAND 11)

set (3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)
set(CMAKE_MODULE_PATH ${3RD_DIR})

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
set (EASY_PROFILER_DIR ${3RD_DIR}/easy_profiler)
# 保证easy_profiler被编译
add_subdirectory (${EASY_PROFILER_DIR})
# 添加头文件搜索路径
include_directories (${EASY_PROFILER_DIR}/easy_profiler_core/include)

# glm
set (GLM_DIR ${3RD_DIR}/glm)
# 添加头文件搜索路径
include_directories (${GLM_DIR})


# 设置MSVC编译编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

add_executable(${PROJECT_NAME} src/VertexData.h src/main.cpp)

# 添加链接库
target_link_libraries(${PROJECT_NAME} OpenGL32 glfw glad easy_profiler)
