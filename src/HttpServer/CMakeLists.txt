project(HttpServer)


include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(HttpServer STATIC HttpServer.cpp)

target_link_libraries(HttpServer Server)

export(TARGETS HttpServer NAMESPACE quoilam:: FILE quoilam-HttpServer.cmake)
