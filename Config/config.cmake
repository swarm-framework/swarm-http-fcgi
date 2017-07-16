# Enable testing capability
enable_testing()

# Set C++ compatibility
set(CMAKE_CXX_STANDARD 17)

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
