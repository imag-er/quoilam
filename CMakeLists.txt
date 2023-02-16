cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB SRC_FILE "src/*")

add_executable(quoilam ${SRC_FILE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
