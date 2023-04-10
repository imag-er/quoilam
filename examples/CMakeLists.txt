cmake_minimum_required(VERSION 3.0.0)
project(examples VERSION 0.3.4)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(quoilam_DIR /usr/include/quoilam/lib/)
include(CTest)
enable_testing()

find_package(quoilam REQUIRED)

set(executables
    test_client
    test_server
    test_threadpool
    test_multiclient
    test_stdlogger
    test_httpserver
    test_database
    test_json
)

foreach(f ${executables})
    add_executable(f ${CMAKE_PROGRAM_PATH}/src/${f}.cpp)
endforeach(f ${executables})

target_link_libraries(test_threadpool quoilam::ThreadPool)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)


