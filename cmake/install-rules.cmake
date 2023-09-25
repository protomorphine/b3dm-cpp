if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/b3dm-cpp-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package b3dm-cpp)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT b3dm-cpp_Development
)

install(
    TARGETS b3dm-cpp_b3dm-cpp
    EXPORT b3dm-cppTargets
    RUNTIME #
    COMPONENT b3dm-cpp_Runtime
    LIBRARY #
    COMPONENT b3dm-cpp_Runtime
    NAMELINK_COMPONENT b3dm-cpp_Development
    ARCHIVE #
    COMPONENT b3dm-cpp_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    b3dm-cpp_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(b3dm-cpp_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${b3dm-cpp_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT b3dm-cpp_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${b3dm-cpp_INSTALL_CMAKEDIR}"
    COMPONENT b3dm-cpp_Development
)

install(
    EXPORT b3dm-cppTargets
    NAMESPACE b3dm-cpp::
    DESTINATION "${b3dm-cpp_INSTALL_CMAKEDIR}"
    COMPONENT b3dm-cpp_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
