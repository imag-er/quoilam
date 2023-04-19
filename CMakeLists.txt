cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.3.4)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

set(quoilam_libs
    Server
    Client
    ThreadPool
    StdLogger
    SocketBase
    HttpServer
    Database
    Typedef
    Json)

foreach(e ${quoilam_libs})
  add_subdirectory(${CMAKE_SOURCE_DIR}/src/${e})


endforeach(e ${quoilam_libs})

install(
    TARGETS ${quoilam_libs}
    EXPORT quoilam-targets
    LIBRARY DESTINATION lib/quoilam
    ARCHIVE DESTINATION lib/quoilam)

install(
      EXPORT quoilam-targets
      FILE quoilam-config.cmake
      NAMESPACE quoilam::
      DESTINATION share/quoilam/)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include
        DESTINATION /usr/local/include/quoilam/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
