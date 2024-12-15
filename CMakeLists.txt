set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

cmake_minimum_required(VERSION 3.30)

project(VesselAudioPlugin)

set(CMAKE_CXX_STANDARD 23)
if (APPLE)
    # On Mac, we need to wait for a new JUCE version that fixes the compilation issue
    set(CMAKE_CXX_STANDARD 20)
endif()

set(PACKAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/packages)
set(DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)
set(CPM_SOURCE_CACHE ${CMAKE_CURRENT_SOURCE_DIR}/packages)
set(CPM_USE_LOCAL_PACKAGES ON)

include(cmake/cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    # TODO: Uncomment when OSX Sonoma issue is fixed
    # GIT_TAG 8.0.0
    # VERSION v8.0.0
    GIT_TAG develop
    SOURCE_DIR ${PACKAGE_DIR}/juce
)

CPMAddPackage(
    NAME GOOGLETEST
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.15.2
    VERSION 1.15.2
    SOURCE_DIR ${PACKAGE_DIR}/googletest
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

enable_testing()

add_compile_definitions(DATA_DIR="${DATA_DIR}")

add_subdirectory(plugin)
add_subdirectory(tests)
