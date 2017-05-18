# Set catch version
set(CATCH_VERSION v1.9.3)

# Set download file
set(CATCH_FILE_PATH ${PROJECT_SOURCE_DIR}/Dependencies/volatile/${CATCH_VERSION}/catch/catch.hxx)

# Test if file does not exist
if (NOT "${CATCH_FILE_PATH}")
    # Download Catch Unit test
    file(DOWNLOAD "https://github.com/philsquared/Catch/releases/download/${CATCH_VERSION}/catch.hpp" "${CATCH_FILE_PATH}")
endif()

# Includes
include_directories(
    ../Sources  # Project sources
    ${PROJECT_SOURCE_DIR}/Dependencies/volatile/${CATCH_VERSION} # catch directory
)

# Add sources files
set (${PROJECT_NAME}_TEST_SOURCES
    main.cxx
)

# Create create executable
add_executable(${PROJECT_NAME}Tests ${${PROJECT_NAME}_TEST_SOURCES})

# Register test
add_test(${PROJECT_NAME}Tests ${PROJECT_NAME}Tests)
