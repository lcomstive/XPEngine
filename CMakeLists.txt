cmake_minimum_required(VERSION 3.21)
project(XPEngine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Get the engine version from Version.txt & git revision
include(${CMAKE_CURRENT_SOURCE_DIR}/Platform/VersionInfo.cmake)

# Detect which platform currently compiling from
include(${CMAKE_CURRENT_SOURCE_DIR}/Platform/DetectPlatforms.cmake)

add_subdirectory(Engine)
add_subdirectory(App)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)

# Enable folders in solution
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
