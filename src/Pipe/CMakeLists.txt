project(Pipe)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(Pipe STATIC Pipe.cpp)

target_link_libraries(Pipe StdLogger)

export(TARGETS Pipe NAMESPACE quoilam:: FILE quoilam-Pipe.cmake)
