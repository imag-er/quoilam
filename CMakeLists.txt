cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.1.0)
# Enable C++17
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

find_package(Threads REQUIRED)

# add libs (aka.cpp)
foreach(lib_name server client quoilamtest)
    add_library(${lib_name}
        STATIC
        src/include/${lib_name}.h
        src/include/${lib_name}.cpp
    )
    target_link_directories(${lib_name}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include)
endforeach(lib_name)

# add .h and .hpp to include_path

# add_executable(quoilam ${SRC_FILE})
foreach(exec testexec main_client main_server)
    add_executable(${exec}
        src/${exec}.cpp
    )

    target_link_libraries(${exec}
        PRIVATE
        quoilamtest
        server
        client
        pthread
    )

    
endforeach(exec)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
