cmake_minimum_required(VERSION 3.10)

project(compress)

set (CMAKE_CXX_STAND 11)

# 添加头文件搜索路径
include_directories (
    ${SRC_DIR}
    ${GLFW_DIR}/include
    ${GLAD_DIR}/include
    ${STB_DIR}
)

# 设置MSVC编译编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

add_executable(${PROJECT_NAME}
    main.cpp
    ${SRC_DIR}/Texture2D.cpp
)

# 添加链接库
target_link_libraries(${PROJECT_NAME} OpenGL32 glfw glad)