if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/adizzle-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

set(package adizzle)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Set up export components
install(
    TARGETS adizzle_adizzle
    EXPORT adizzleTargets
    RUNTIME COMPONENT adizzle_Runtime
    LIBRARY COMPONENT adizzle_Runtime
    NAMELINK_COMPONENT adizzle_Development
    ARCHIVE COMPONENT adizzle_Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Write package file for installations
write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    adizzle_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(adizzle_INSTALL_CMAKEDIR)

# Install config file to the install directory
# Config file is used by find_package() (I assume)
install(
    FILES cmake/install-config.cmake
    DESTINATION "${adizzle_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT adizzle_Development
)

# Install ConfigVersion file
# More package install info
install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${adizzle_INSTALL_CMAKEDIR}"
    COMPONENT adizzle_Development
)

# Install the dev component from targets defined above (I think)
install(
    EXPORT adizzleTargets
    NAMESPACE adizzle::
    DESTINATION "${adizzle_INSTALL_CMAKEDIR}"
    COMPONENT adizzle_Development
)

# Include CPack
if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()