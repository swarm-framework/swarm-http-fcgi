# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.8)

# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(swarm-http-fcgi VERSION 0.1.0)

# Include config
include(Config/config.cmake)

# Include build
include(Config/build.cmake)

# Include test
add_subdirectory(Tests)
