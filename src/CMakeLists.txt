cmake_minimum_required(VERSION 3.5)

project(icseqgen)

set(CMAKE_CXX_STANDARD 11)

add_executable(icseqgen main.cpp)

target_link_libraries(icseqgen arithmetica)
target_link_libraries(icseqgen basic_math_operations)