
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CXX_STANDARD 11)  #Seting c11 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

project(LearnOpengl)


find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)
find_package(ASSIMP REQUIRED)


file(GLOB src_dir src/*.cpp)
source_group("Source Files" FILES ${src_dir})

file(GLOB include_dir include/*.h)
source_group("Include Files" FILES ${include_dir})

include_directories("include")

add_executable(learn_opengl ${src_dir} ${include_dir})