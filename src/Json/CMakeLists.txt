project(Json)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(Json STATIC Json.cpp)

target_link_libraries(Json )

export(TARGETS Json NAMESPACE quoilam:: FILE quoilam-Json.cmake)
