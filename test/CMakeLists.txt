add_executable(
  demo_tests
    geom/vector.cpp
  )

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # Use the latest version or a specific tag
)
FetchContent_MakeAvailable(Catch2)

target_link_libraries(demo_tests
  PRIVATE
    Catch2::Catch2WithMain
    demo_lib
  )

include(Catch)
catch_discover_tests(demo_tests)
