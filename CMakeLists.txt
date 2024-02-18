cmake_minimum_required(VERSION 3.27)

project(
    adizzle
    VERSION 0.1.0
    DESCRIPTION "Utility library for personal projects"
    LANGUAGES NONE
)

# Include utilities
include(cmake/options.cmake)
include(cmake/warning-guard.cmake)
include(cmake/dependencies.cmake)

# Declare library
add_library(adizzle_adizzle INTERFACE)
add_library(adizzle::adizzle ALIAS adizzle_adizzle)

set_target_properties(adizzle_adizzle
    PROPERTIES
        EXPORT_NAME adizzle
)

# Add include directory
# warning_guard adds SYSTEM modifier if the project isn't top level
target_include_directories(
    adizzle_adizzle ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

# Install rules
if(NOT ADIZZLE_SKIP_INSTALL)
  include(cmake/install-rules.cmake)
endif()

# Enable testing
if(BUILD_TESTING)
    include(CTest)
    include(cmake/compile-options.cmake)
    add_subdirectory(tests)
endif()