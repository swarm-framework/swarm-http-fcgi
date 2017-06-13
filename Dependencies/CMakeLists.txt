if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/cxx-log/CMakeLists.txt)

    if(NOT TARGET cxx-log)
        # Include cxx-log
        add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/cxx-log)

        # Include sources
        include_directories(${PROJECT_SOURCE_DIR}/Dependencies/cxx-log/Sources)
    endif()

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons/CMakeLists.txt)

    if(NOT TARGET swarm-commons)
        # Include swarm-commons
        add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons)

        # Include sources
        include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons/Sources)
    endif()

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-mapping/CMakeLists.txt)

    if(NOT TARGET swarm-mapping)
        # Include swarm-mapping
        add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-mapping)

        # Include sources
        include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-mapping/Sources)
    endif()

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api/CMakeLists.txt)

    if(NOT TARGET swarm-http-api)
        # Include swarm-http-api
        add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api)

        # Include sources
        include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api/Sources)
    endif()

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-server/CMakeLists.txt)

    if(NOT TARGET swarm-http-server)
        # Include swarm-http-server
        add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-server)

        # Include sources
        include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-server/Sources)
    endif()

endif()

# --- Find Curl package ---

# Find Curl
find_package(CURL REQUIRED)

# --- FastCGI ---

# Find fastcgi
find_path(LibFCGI_Include fcgio.h)
find_library(LibFCGI NAMES fcgi)
find_library(LibFCGI++ NAMES fcgi++)

if (${LibFCGI++})
    message(--\ FCGI\ \ \ ${LibFCGI})
    message(--\ FCGI++\ ${LibFCGI++})
endif()
