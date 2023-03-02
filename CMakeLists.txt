cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.1.0)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

find_package(Threads REQUIRED)

include_directories(src/include/)

set(quoilam_libs server client quoilamtest threadpool)
set(system_libs pthread)
set(example_executables testexec example_client example_server)

set(EXECUTABLE_OUTPUT_PATH build/executable/)
set(LIBRARY_OUTPUT_PATH build/library/)

# add libs (aka.cpp)
foreach(lib_name ${quoilam_libs})
    add_library(${lib_name}
        STATIC
        src/include/${lib_name}.h
        src/include/${lib_name}.cpp
    )
endforeach(lib_name)

link_libraries(${quoilam_libs} ${system_libs})

foreach(exec ${example_executables})
    add_executable(${exec}
        src/examples/${exec}.cpp
    )
endforeach(exec)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
