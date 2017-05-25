# Add sources files
set (${PROJECT_NAME}_SOURCES
    swarm/http/fcgi/FastCGIServerDelegate.cxx swarm/http/fcgi/FastCGIServerDelegate.hxx
    swarm/http/fcgi/FastCGISession.cxx swarm/http/fcgi/FastCGISession.hxx
    swarm/http/fcgi/FastCGIRequestDecoder.cxx swarm/http/fcgi/FastCGIRequestDecoder.hxx
)

# Set includes
include_directories(
    .       # Current project
) 

# Create library
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

# Link library
target_link_libraries(${PROJECT_NAME}
    swarm-http-server
)

# Install exec in bin directory
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
