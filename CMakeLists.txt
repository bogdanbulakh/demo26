cmake_minimum_required(VERSION 3.10.0)
project(demo VERSION 0.1.0 LANGUAGES C CXX)
enable_testing()

set(demo_src_list
  src/vector.cpp
)

add_executable(
  demo_out
    src/main.cpp
  )

add_library(
  demo_lib
    ${demo_src_list}
  )

add_subdirectory(test)

target_link_libraries(demo_out PRIVATE demo_lib)

include(CTest)

