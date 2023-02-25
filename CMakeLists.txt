cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB LIB_SOURCE "src/include/*.cpp")

# add libs (aka.cpp)
add_library(quoilam_libs STATIC ${LIB_SOURCE})

# add .h and .hpp to include_path
target_link_directories(quoilam_libs
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include)

# add_executable(quoilam ${SRC_FILE})
add_executable(testexec 
    src/testexec.cpp 
    )

target_link_libraries(testexec 
    PRIVATE 
    quoilam_libs
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
