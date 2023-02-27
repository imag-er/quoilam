cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.1.0)

include(CTest)
enable_testing()

# add libs (aka.cpp)
foreach(lib_name server client singleton quoilamtest)
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
foreach(exec testexec)
    add_executable(${exec}
        src/${exec}.cpp
    )

    target_link_libraries(${exec}
        PRIVATE
        quoilamtest
        server
        client
    )
endforeach(exec)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
