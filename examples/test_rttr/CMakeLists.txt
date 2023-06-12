cmake_minimum_required(VERSION 3.10)

project(test_rttr)

set(CMAKE_CXX_STANDARD 17)

# fmt
include_directories(${FMT_DIR}/include)

# rttr
include_directories(${RTTR_DIR}/src)

# 设置MSVC编译编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

add_executable(
    ${PROJECT_NAME}
    src/person.h
    src/person.cpp
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt rttr_core_lib)

add_executable(
    "${PROJECT_NAME}2"
    src/test.cpp
)

target_link_libraries("${PROJECT_NAME}2" PRIVATE fmt::fmt rttr_core_lib)