cmake_minimum_required(VERSION 3.5)

project(icseqgen)

# set(CMAKE_CXX_STANDARD 11)

add_library(icse_question_generator
library/icse_question_free.c
library/random_number_aarav_version.c
library/quadratic_examine_roots.c
library/compare_number.c
)
# anyways gtg eat
set(CMAKE_C_FLAGS, "${CMAKE_C_FLAGS} -march=native")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -ggdb")
add_executable(icseqgen main.c)

target_link_libraries(icseqgen icse_question_generator)
target_link_libraries(icseqgen arithmetica)
target_link_libraries(icseqgen basic_math_operations)