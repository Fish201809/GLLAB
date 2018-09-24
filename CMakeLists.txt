
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CXX_STANDARD 11)  #Seting c11 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

project(LearnOpengl)


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
file(GLOB GLAD_SRC_DIR ${GLAD_DIR}/src/*.c)
add_library(GLAD_libs STATIC ${GLAD_SRC_DIR})
endif(NOT GLAD_DIR)


file(GLOB src_dir src/*.cpp)
source_group("Source Files" FILES ${src_dir})

file(GLOB include_dir include/*.h)
source_group("Include Files" FILES ${include_dir})

include_directories("include")

add_executable(learn_opengl ${src_dir} ${include_dir})
target_link_libraries(learn_opengl GLAD_libs)
target_link_libraries(learn_opengl debug ${SDL2_debug_libs})
target_link_libraries(learn_opengl optimized ${SDL2_release_libs})
