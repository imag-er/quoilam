project(Except)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(Except STATIC Except.cpp)

target_link_libraries(Except SocketBase Typedef sqlite3)

export(TARGETS Except NAMESPACE quoilam:: FILE quoilam-Database.cmake)
