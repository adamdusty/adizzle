if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/adizzle-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

# Define install dir since no language set
set(CMAKE_INSTALL_LIBDIR CACHE PATH "")

set(package adizzle)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT adizzle_Development
)

install(
    TARGETS adizzle_adizzle
    EXPORT adizzleTargets
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Write package file for installations
write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

# Allow package maintainers to freely override the path for the configs
set(
    adizzle_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
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