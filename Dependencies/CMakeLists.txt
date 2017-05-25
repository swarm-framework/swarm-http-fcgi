if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/cxx-log/CMakeLists.txt)

    # Include cxx-log
    add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/cxx-log)

    # Include sources
    include_directories(${PROJECT_SOURCE_DIR}/Dependencies/cxx-log/Sources)

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons/CMakeLists.txt)

    # Include swarm-commons
    add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons)

    # Include sources
    include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons/Sources)

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api/CMakeLists.txt)

    # Include swarm-http-api
    add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api)

    # Include sources
    include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api/Sources)

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-server/CMakeLists.txt)

    # Include swarm-http-server
    add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-server)

    # Include sources
    include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-server/Sources)

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

