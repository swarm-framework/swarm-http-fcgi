cmake_minimum_required(VERSION 3.0.0)

# Define project name
project(swarm-http-fcgi)

# enable tests
enable_testing()

# Include dependencies
add_subdirectory(Dependencies)

# Include sources
add_subdirectory(Sources)

# Include test
add_subdirectory(Tests)
