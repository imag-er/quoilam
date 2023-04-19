project(Database)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(Database STATIC Database.cpp)

target_link_libraries(Database SocketBase Typedef sqlite3)

export(TARGETS Database NAMESPACE quoilam:: FILE quoilam-Database.cmake)
