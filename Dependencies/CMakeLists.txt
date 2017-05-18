
# Enable ExternalProject CMake module
include(ExternalProject)

# cxxlog core version
set(cxxlog-VERSION master)

# Download and install murmuration-core
ExternalProject_Add(
    cxxlog
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/volatile
    GIT_REPOSITORY git@github.com:swarm-framework/swarm-http-api.git
    GIT_TAG "${cxxlog-VERSION}"
    INSTALL_COMMAND ""
)

# Find lib FCGI
find_path(LibFCGI_Include fcgio.h)
find_library(LibFCGI NAMES fcgi)
find_library(LibFCGI++ NAMES fcgi++)

message(--\ FCGI\ \ \ ${LibFCGI})
message(--\ FCGI++\ ${LibFCGI++})
