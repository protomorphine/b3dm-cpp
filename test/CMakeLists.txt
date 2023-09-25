cmake_minimum_required(VERSION 3.14)

project(b3dm-cppTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(b3dm-cpp REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(b3dm-cpp_test source/b3dm-cpp_test.cpp)
target_link_libraries(b3dm-cpp_test PRIVATE b3dm-cpp::b3dm-cpp)
target_compile_features(b3dm-cpp_test PRIVATE cxx_std_20)

add_test(NAME b3dm-cpp_test COMMAND b3dm-cpp_test)

# ---- End-of-file commands ----

add_folders(Test)
