
cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.3.4)

add_definitions("-Wall -std=c++17")

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

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
  Json
  Pipe
  Except
)

foreach(e ${quoilam_libs})
  add_subdirectory(${CMAKE_SOURCE_DIR}/src/${e})
endforeach(e ${quoilam_libs})

IF(CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Darwin")
  MESSAGE(STATUS "current platform: Unix-like (Linux OR Mac OS)")

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
  install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION /usr/local/include/quoilam)

ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Windows")

  MESSAGE(STATUS "current platform: Windows")

  install(
    TARGETS ${quoilam_libs}
    EXPORT quoilam-targets
    LIBRARY DESTINATION D:/System/Documents/libs/quoilam
    ARCHIVE DESTINATION D:/System/Documents/libs/quoilam)

  install(
    EXPORT quoilam-targets
    FILE quoilam-config.cmake
    NAMESPACE quoilam::
    DESTINATION D:/System/Documents/libs/quoilam/)
  install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION D:/System/Documents/include/quoilam)

ELSE()
  MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
