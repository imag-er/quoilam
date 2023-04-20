project(ThreadPool)

find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(ThreadPool STATIC ThreadPool.cpp)

target_link_libraries(ThreadPool pthread StdLogger)

export(TARGETS ThreadPool NAMESPACE quoilam:: FILE quoilam-ThreadPool.cmake)
