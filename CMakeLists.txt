cmake_minimum_required(VERSION 3.30)

project(VesselAudioPlugin)

set(CMAKE_CXX_STANDARD 23)
if (APPLE)
    # On Mac, we need to wait for a new JUCE version that fixes the compilation issue
    set(CMAKE_CXX_STANDARD 20)
endif()

set(PACKAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/packages)

include(cmake/cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 8.0.0
    VERSION v8.0.0
    SOURCE_DIR ${PACKAGE_DIR}/juce
)

add_subdirectory(plugin)
