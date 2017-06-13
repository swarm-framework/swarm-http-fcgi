# Set C++ compatibility
set(CMAKE_CXX_STANDARD 17)

# Enable testing capability
enable_testing()

# Define CXX flags
set(CXX_FLAGS -Wall -pedantic)

# Create test coverage target (gcov)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
	set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
    set(CXX_FLAGS ${CXX_FLAGS} --coverage  -fprofile-arcs -ftest-coverage)
	set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " --coverage  -fprofile-arcs -ftest-coverage")
endif()

# Set compilation flags
add_definitions(${CXX_FLAGS})

# Define find depenedencies
function(find_dependencies packagName)

    # Test if target is defined
    if(NOT TARGET ${packagName})
    
        # Test if CMakeFile exist for this library
        if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/${packagName}/CMakeLists.txt)

        
            # Include package
            add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/${packagName})
            
            # Set include dir
            set(${packagName}_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Dependencies/${packagName}/Sources" PARENT_SCOPE)
            
        else()
        
            # Find package
            find_package(${packagName})

        endif()  
        
    endif()

endfunction()
