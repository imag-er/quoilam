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
    target_include_directories(${lib_name} PUBLIC 
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/include/>
        $<INSTALL_INTERFACE:include>
    )

endforeach()


# # 安装lib
# install(TARGETS ${quoilam_libs}
#     ARCHIVE DESTINATION lib
# )
# 安装header
install(FILES ${quoilam_headers}
    DESTINATION /usr/include/quoilam)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/quoilamConfig.cmake.in
    ${PROJECT_SOURCE_DIR}/cmake/quoilamConfig.cmake
    INSTALL_DESTINATION lib/quoilam
)

write_basic_package_version_file(
    ${PROJECT_SOURCE_DIR}/cmake/quoilamConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(TARGETS ${quoilam_libs}
    EXPORT quoilamTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT quoilamTargets
    FILE quoilamTargets.cmake
    NAMESPACE quoilam::
    DESTINATION lib/cmake/quoilam
)
install(FILES
    ${PROJECT_SOURCE_DIR}/cmake/quoilamConfig.cmake
    ${PROJECT_SOURCE_DIR}/cmake/quoilamConfigVersion.cmake
    DESTINATION lib/cmake/quoilam
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)


