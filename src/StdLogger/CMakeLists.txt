project(StdLogger)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(StdLogger STATIC StdLogger.cpp)

target_link_libraries(StdLogger )

export(TARGETS StdLogger NAMESPACE quoilam:: FILE quoilam-StdLogger.cmake)
