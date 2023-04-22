cmake_minimum_required(VERSION 3.0.0)
project(examples VERSION 0.3.4)

add_definitions("-g")

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

find_package(quoilam REQUIRED)

include_directories(/usr/local/include/quoilam/include/)

set(executables
    test_client
    test_server
    test_threadpool
    test_multiclient
    test_stdlogger
    test_httpserver
    test_database
    test_json
    test_pipe_read
    test_pipe_write

)

foreach(f ${executables})
    add_executable(${f} src/${f}.cpp)
endforeach(f ${executables})

target_link_libraries(test_json quoilam::Json)
target_link_libraries(test_httpserver quoilam::HttpServer)
target_link_libraries(test_client quoilam::Client)
target_link_libraries(test_multiclient quoilam::Client quoilam::ThreadPool)
target_link_libraries(test_server quoilam::Server)
target_link_libraries(test_stdlogger quoilam::StdLogger)
target_link_libraries(test_threadpool quoilam::ThreadPool)
target_link_libraries(test_json quoilam::Json)
target_link_libraries(test_database quoilam::Database)
target_link_libraries(test_pipe_read quoilam::Pipe)
target_link_libraries(test_pipe_write quoilam::Pipe)




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)


