cmake_minimum_required(VERSION 3.27)

project(
    adizzle
    VERSION 0.1.0
    DESCRIPTION "A short description"
    LANGUAGES CXX
)

# Include utilities
include(cmake/options.cmake)
include(cmake/warning-guard.cmake)
include(cmake/compile-options.cmake)
include(cmake/dependencies.cmake)

# Declare library
add_library(adizzle_adizzle)
add_library(adizzle::adizzle ALIAS adizzle_adizzle)

# Add sources
target_sources(adizzle_adizzle PRIVATE
    src/adizzle.cpp
)

# Add include directory
# warning_guard adds SYSTEM modifier if the project isn't top level
target_include_directories(
    adizzle_adizzle ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

# Include and link dependencies
#target_link_libraries(adizzle_adizzle)

# Add compile options
add_dev_compile_opts(adizzle_adizzle)

# Generate header for export
include(GenerateExportHeader)
generate_export_header(
    adizzle_adizzle
    BASE_NAME adizzle
    EXPORT_FILE_NAME include/adizzle/export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

# Set properties
set_target_properties(
    adizzle_adizzle PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME adizzle
    OUTPUT_NAME adizzle
)

# Install rules
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# Enable testing
if(ADIZZLE_BUILD_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()