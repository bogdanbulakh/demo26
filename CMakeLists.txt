cmake_minimum_required(VERSION 4.4.3 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(WIN32)
    set(CMAKE_MANIFEST_LINKS CHARACTER_SET "UTF-8")
    # Forces absolute instead of relative tracking inside ninja rules
    set(CMAKE_NINJA_OUTPUT_PATH_PREFIX "")
endif()

project(demo VERSION 0.1.0 LANGUAGES CXX)

enable_testing()
add_subdirectory(test)
include(CTest)

set(modules_list
  src/geom/vector.cppm
)

set(src_list
  src/geom/vector.cpp
)

add_library(demo_lib STATIC)

target_sources(demo_lib
  PUBLIC
    FILE_SET CXX_MODULES FILES
      ${modules_list}
  PRIVATE
    ${src_list}
  )

add_executable(demo_app)

target_compile_features(demo_app
  PRIVATE
    cxx_std_23
  )

target_sources(demo_app
  PRIVATE
    src/main.cpp
  )

target_link_libraries(demo_app
  PRIVATE
    demo_lib
  )

