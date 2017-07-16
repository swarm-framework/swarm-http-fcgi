# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.8)

# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(swarm-http-fcgi VERSION 0.1.0)

# Include config
include(Config/config.cmake)

# Find Curl
find_package(CURL REQUIRED)

# Find fastcgi
find_path(LibFCGI_Include fcgio.h)
find_library(LibFCGI NAMES fcgi)
find_library(LibFCGI++ NAMES fcgi++)

if (${LibFCGI++})
    message(--\ FCGI\ \ \ ${LibFCGI})
    message(--\ FCGI++\ ${LibFCGI++})
endif()

# Include sub projects
find_dependencies(cxx-log)
find_dependencies(swarm-commons)
find_dependencies(swarm-mapping)
find_dependencies(swarm-http-api)
find_dependencies(swarm-http-server)

# Create targets
add_library(swarm-http-fcgi

    Sources/swarm/http/fcgi/FastCGIServerDelegate.cxx Sources/swarm/http/fcgi/FastCGIServerDelegate.hxx
    Sources/swarm/http/fcgi/FastCGISession.cxx Sources/swarm/http/fcgi/FastCGISession.hxx
    Sources/swarm/http/fcgi/FastCGIRequestDecoder.cxx Sources/swarm/http/fcgi/FastCGIRequestDecoder.hxx
)

# Target includes
target_include_directories(
    swarm-http-fcgi
        
    PRIVATE
        ${cxx-log_INCLUDE_DIR}
        ${swarm-commons_INCLUDE_DIR}
        ${swarm-mapping_INCLUDE_DIR}
        ${swarm-http-api_INCLUDE_DIR}
        ${swarm-http-server_INCLUDE_DIR}
)

# Target link
target_link_libraries(
    swarm-http-fcgi
    
    swarm-commons
    swarm-mapping
    swarm-http-api
    swarm-http-server
    ${CURL_LIBRARIES}
    ${LibFCGI}
    ${LibFCGI++}
)

# Include build
include(Config/build.cmake)

# Include test
add_subdirectory(Tests)
