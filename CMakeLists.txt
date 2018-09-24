
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CXX_STANDARD 11)  #设置c11标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS On) #为了更清晰的项目结构设置分类

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

project(LearnOpengl)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/..) #设置[安装/调试]目录路径


find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)
find_package(ASSIMP REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

#配置glad
if(NOT GLAD_DIR)
set(GLAD_DIR $ENV{GLAD_DIR} CACHE PATH "Choose SGLAD PATH" FORCE)
else(NOT GLAD_DIR)
include_directories(${GLAD_DIR}/include)
file(GLOB GLAD_INCLUDE_DIR ${GLAD_DIR}/include/*/*)
file(GLOB GLAD_SRC_DIR ${GLAD_DIR}/src/*.c)
source_group("Include Files" FILES ${GLAD_INCLUDE_DIR})
add_library(GLAD_libs STATIC ${GLAD_SRC_DIR}  ${GLAD_INCLUDE_DIR})
set_target_properties(GLAD_libs PROPERTIES FOLDER CommonLib)
endif(NOT GLAD_DIR)

#为安装dll
#install(FILES "README.md" DESTINATION Document)
file(GLOB 3RD_DLL ${CMAKE_SOURCE_DIR}/dll/*.dll)
install(FILES ${3RD_DLL} DESTINATION ${CMAKE_INSTALL_PREFIX}/BIN)

#添加例子
add_subdirectory("Example_1")


