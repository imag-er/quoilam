project(Server)


include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(Server STATIC Server.cpp)

target_link_libraries(Server SocketBase ThreadPool)

export(TARGETS Server NAMESPACE quoilam:: FILE quoilam-server.cmake)
