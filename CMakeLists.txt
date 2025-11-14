cmake_minimum_required(VERSION 3.10)
project(FilesystemProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main library
add_library(filesystem_lib src/filesystem.cpp)
target_include_directories(filesystem_lib PUBLIC src)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executable
add_executable(filesystem_tests tests/test_filesystem.cpp)
target_link_libraries(filesystem_tests PRIVATE filesystem_lib gtest_main)

include(GoogleTest)
if(NOT CMAKE_CROSSCOMPILING)
    gtest_discover_tests(filesystem_tests)
endif()
