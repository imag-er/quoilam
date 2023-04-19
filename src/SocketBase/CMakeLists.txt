project(SocketBase)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(SocketBase STATIC SocketBase.cpp)

target_link_libraries(SocketBase StdLogger)

export(TARGETS SocketBase NAMESPACE quoilam:: FILE quoilam-SocketBase.cmake)
