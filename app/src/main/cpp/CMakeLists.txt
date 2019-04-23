#设定cmark需要的版本

cmake_minimum_required(VERSION 3.4.1)

#1.导入头文件
include_directories(${CMAKE_SOURCE_DIR}/inc)

#2.添加预编译的fmod库
add_library(
        fmod           #模块名称
        SHARED         #动态库
        IMPORTED)

add_library(
        fmodL
        SHARED
        IMPORTED)
   #3.设置详细的导入路径
set_target_properties(
        fmod
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../../../libs/${CMAKE_ANDROID_ARCH_ABI}/libfmod.so
)


set_target_properties(
        fmodL
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../../../libs/${CMAKE_ANDROID_ARCH_ABI}/libfmodL.so
)


#设置本地动态库，编译生成动态库
add_library(
        native-lib       #模块名称
        SHARED           #动态库
        native-lib.cpp)  #源文件

#查找系统库：日志库
find_library(
        log-lib
        log)

 #添加需要链接或者编译的库
target_link_libraries(
        native-lib
        fmod
        fmodL
        ${log-lib})
