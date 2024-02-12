cmake_minimum_required(VERSION 3.14)

project(b3dm-cppTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(b3dm-cpp REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(b3dm-cpp_test source/b3dm-cpp_test.cpp source/binary_file_test.cpp)
target_link_libraries(b3dm-cpp_test PRIVATE b3dm-cpp::b3dm-cpp GTest::gtest_main)
target_compile_features(b3dm-cpp_test PRIVATE cxx_std_20)

add_test(NAME MyTest COMMAND b3dm-cpp_test)

include(GoogleTest)
gtest_discover_tests(b3dm-cpp_test)

# ---- End-of-file commands ----

add_folders(Test)
