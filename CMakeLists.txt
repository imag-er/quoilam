cmake_minimum_required(VERSION 3.0.0)
project(quoilam VERSION 0.3.4)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX /usr/include/quoilam)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

include_directories(src/include/)

set(quoilam_libs
    Server
    Client
    ThreadPool
    StdLogger
    SocketBase
    HttpServer
    Database
    Typedef
    Json
)
file(GLOB quoilam_headers "${CMAKE_SOURCE_DIR}/src/include/*.h*")


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/library)

# add libs
foreach(lib_name ${quoilam_libs})
    add_library(${lib_name}
        STATIC
        ${PROJECT_SOURCE_DIR}/src/include/${lib_name}.h
        ${PROJECT_SOURCE_DIR}/src/include/${lib_name}.cpp
    )
endforeach()


# 安装lib
install(TARGETS ${quoilam_libs}
    ARCHIVE DESTINATION lib
)
# 安装header
install(FILES ${quoilam_headers}
    DESTINATION /usr/include/quoilam)

# 导入config生成助手
include(CMakePackageConfigHelpers)

# 通过cmake.in生成导出文件
configure_package_config_file( 
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/quoilamConfig.cmake.in 
    ${CMAKE_CURRENT_BINARY_DIR}/quoilamConfig.cmake
    INSTALL_DESTINATION lib/
)
write_basic_package_version_file( 
    ${CMAKE_CURRENT_BINARY_DIR}/quoilamConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion 
)

# 安装.cmake文件 代表静态库的配置文件
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/quoilamConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/quoilamConfigVersion.cmake
    DESTINATION lib/
)

# 导出target到配置文件
export(
    TARGETS 
    Server Client ThreadPool StdLogger SocketBase HttpServer Database Typedef Json 
    FILE ${CMAKE_CURRENT_BINARY_DIR}/quoilamTargets.cmake )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)


