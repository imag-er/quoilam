project(Client)


include_directories(${CMAKE_SOURCE_DIR}/include)


add_library(Client STATIC Client.cpp)

target_link_libraries(Client StdLogger SocketBase)

export(TARGETS Client NAMESPACE quoilam:: FILE quoilam-Client.cmake)
