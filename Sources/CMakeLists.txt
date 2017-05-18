
# Add sources files
set (${PROJECT_NAME}_SOURCES
    main.cxx
)

# Create library
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

# Install exec in bin directory
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
