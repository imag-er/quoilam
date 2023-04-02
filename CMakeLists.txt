cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.3.4)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX /usr/include/quoilam)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

find_package(Threads REQUIRED)

include_directories(src/include/)

set(quoilam_libs
    Server
    Client
    ThreadPool
    StdLogger
    SocketBase
    HttpServer
    Database
    Typedef
    Json
)
file(GLOB quoilam_headers "${CMAKE_SOURCE_DIR}/src/include/*.h*")
set(example_executables
    test_client
    test_server
    test_threadpool
    test_multiclient
    test_stdlogger
    test_httpserver
    test_database
    test_json
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/executable)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/library)

# add libs
foreach(lib_name ${quoilam_libs})
    add_library(${lib_name}
        STATIC
        ${PROJECT_SOURCE_DIR}/src/include/${lib_name}.h
        ${PROJECT_SOURCE_DIR}/src/include/${lib_name}.cpp
    )
endforeach()

# link_libraries
target_link_libraries(ThreadPool
    pthread
    StdLogger
)
target_link_libraries(Client
    SocketBase
    StdLogger
)
target_link_libraries(Server
    SocketBase
    ThreadPool
    StdLogger
)
target_link_libraries(HttpServer
    Server
)
target_link_libraries(Database
    StdLogger
    sqlite3
    Typedef
)

# test_executables

# Client
add_executable(test_client
    ${PROJECT_SOURCE_DIR}/src/examples/test_client.cpp
)
target_link_libraries(test_client
    Client
)

# Server
add_executable(test_server
    ${PROJECT_SOURCE_DIR}/src/examples/test_server.cpp
)
target_link_libraries(test_server
    Server
)

# MultiClient
add_executable(test_multiclient
    ${PROJECT_SOURCE_DIR}/src/examples/test_multiclient.cpp
)
target_link_libraries(test_multiclient
    Client
    ThreadPool
)

# StdLogger
add_executable(test_stdlogger
    ${PROJECT_SOURCE_DIR}/src/examples/test_stdlogger.cpp
)
target_link_libraries(test_stdlogger
    StdLogger
)

# ThreadPool
add_executable(test_threadpool
    ${PROJECT_SOURCE_DIR}/src/examples/test_threadpool.cpp
)
target_link_libraries(test_threadpool
    ThreadPool
)

# HttpServer
add_executable(test_httpserver
    ${PROJECT_SOURCE_DIR}/src/examples/test_httpserver.cpp
)
target_link_libraries(test_httpserver
    HttpServer
)

add_executable(test_database
    ${PROJECT_SOURCE_DIR}/src/examples/test_database.cpp
)
target_link_libraries(test_database
    Database
)
add_executable(test_json
    ${PROJECT_SOURCE_DIR}/src/examples/test_json.cpp
)
target_link_libraries(test_json
    Json
)

install(TARGETS ${quoilam_libs}
    ARCHIVE DESTINATION lib
)

install(FILES ${quoilam_headers}
    DESTINATION /usr/include/quoilam)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
