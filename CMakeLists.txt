cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.3.4)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)

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
    Timer
)

set(example_executables
    test_client
    test_server
    test_threadpool
    test_multiclient
    test_stdlogger
    test_timer
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

# link_libraries(${quoilam_libs} ${system_libs})
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
target_link_libraries(Timer
    pthread
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

# ThreadPool
add_executable(test_timer
    ${PROJECT_SOURCE_DIR}/src/examples/test_timer.cpp
)
target_link_libraries(test_timer
    Timer
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
