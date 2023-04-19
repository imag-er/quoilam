project(Typedef)


include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(Typedef STATIC Typedef.cpp)

target_link_libraries(Typedef )

export(TARGETS Typedef NAMESPACE quoilam:: FILE quoilam-Typedef.cmake)
