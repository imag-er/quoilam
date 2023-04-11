
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was quoilamConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/MyLibraryTargets.cmake")

# 暴露库的头文件目录
set(MyLibrary_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include")

# 暴露库的库文件
set(MyLibrary_LIBRARIES MyLibrary1 MyLibrary2)

# 暴露库的依赖项
set(MyLibrary_DEPENDENCIES)

# 安装路径
set(MyLibrary_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# 生成配置文件
configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/MyLibraryConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MyLibrary"
  PATH_VARS MyLibrary_INCLUDE_DIRS MyLibrary_INSTALL_PREFIX
  )

# 安装配置文件
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/MyLibraryConfig.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MyLibrary"
  )
