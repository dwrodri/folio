
cmake_minimum_required(VERSION 3.12)

project(
    Folio
    VERSION 0.1
    DESCRIPTION "Please Hire me"
    LANGUAGES CXX
)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # add FetchContent support
    include(FetchContent)

    # add testing support
    include(CTest)

    # set standards
    set(CMAKE_CXX_STANDARD 17)

    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Add fmtlib and spdlog for logging
    find_package(spdlog REQUIRED)
    find_package(fmt REQUIRED)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# export compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# add platform flag
add_compile_definitions(DARCH=${CMAKE_SYSTEM_PROCESSOR})

# facilitate perf tracing by preserving frame pointers
add_compile_options(-fno-omit-frame-pointer)

# make build type visible from C++ as a preprocessor macro
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_definitions(REL_WITH_DEB_INFO_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    add_compile_definitions(MIN_SIZE_REL_BUILD)
else()
    add_compile_definitions(RELEASE_BUILD=1)
endif()

# library code here
add_subdirectory(src/containers)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
    AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

# log config
message("Folio C++ ${PROJECT_VERSION}")
message("CXX: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message("Platform: ${CMAKE_SYSTEM_PROCESSOR}")
message("Build Type: ${CMAKE_BUILD_TYPE}")
