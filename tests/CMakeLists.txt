cmake_minimum_required(VERSION 3.27)

project(
    adizzleTests
    LANGUAGES CXX
)

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(adizzle REQUIRED)
    enable_testing()
endif()

# Get the testing library
include(FetchContent)
FetchContent_Declare(
    snitch
    GIT_REPOSITORY https://github.com/cschreib/snitch.git
    GIT_TAG        v1.2.2
    GIT_SHALLOW    TRUE
    SYSTEM
    FIND_PACKAGE_ARGS # Use system package if installed
)
FetchContent_MakeAvailable(snitch)

# Add test exe
add_executable(adizzle_tests)

# Add test sources
target_sources(adizzle_tests PRIVATE
    src/cast_test.cpp
    src/string_test.cpp
    src/float_test.cpp
)

# Link libs
target_link_libraries(adizzle_tests 
    PRIVATE
        snitch::snitch
        adizzle::adizzle
)

# Add test
add_test(NAME adizzle_tests COMMAND adizzle_tests)

# Enable test binary to find the DLL if building a shared lib
if(BUILD_SHARED_LIBS)
    set_tests_properties(xyz_tests PROPERTIES
        ENVIRONMENT_MODIFICATION
            "PATH=path_list_append:$<TARGET_FILE_DIR:xyz::xyz>;PATH=path_list_append:$<TARGET_FILE_DIR:snitch::snitch>"
    )
endif()
