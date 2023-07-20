cmake_minimum_required(VERSION 3.14)
project(Fixed_Unit_Test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# fetch Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  casting
  src/casting.cpp
)
target_link_libraries(
  casting
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(casting)