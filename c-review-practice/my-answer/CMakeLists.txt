cmake_minimum_required(VERSION 3.16)
project(my_answer LANGUAGES C)

add_executable(my_answer src/main.c)
add_executable(p01 src/c-review-practice/p01.c)

set_target_properties(my_answer p01 PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
