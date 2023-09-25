cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    b3dm-cpp
    VERSION 0.1.0
    DESCRIPTION "provides API to work with b3dm Cesium files"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    b3dm-cpp_b3dm-cpp
        source/file.cpp
        source/decoder.cpp)

add_library(b3dm-cpp::b3dm-cpp ALIAS b3dm-cpp_b3dm-cpp)

include(GenerateExportHeader)
GENERATE_EXPORT_HEADER(
    b3dm-cpp_b3dm-cpp
    BASE_NAME b3dm-cpp
    EXPORT_FILE_NAME export/b3dm-cpp/b3dm-cpp_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(b3dm-cpp_b3dm-cpp PUBLIC B3DM_CPP_STATIC_DEFINE)
endif()

set_target_properties(
    b3dm-cpp_b3dm-cpp PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME b3dm-cpp
    OUTPUT_NAME b3dm-cpp
)

target_include_directories(
    b3dm-cpp_b3dm-cpp ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    b3dm-cpp_b3dm-cpp SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(b3dm-cpp_b3dm-cpp PUBLIC cxx_std_20)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${b3dm-cpp_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT b3dm-cpp_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of b3dm-cpp"
  )
endif()

include(cmake/dev-mode.cmake)
