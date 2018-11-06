
cmake_minimum_required(VERSION 2.8.11)


project(LearnOpengl)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(VCPKG_DIR "G:/vcpkg")
set(DCMAKE_TOOLCHAIN_FILE ${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)


set(CMAKE_CXX_STANDARD 11)  #Seting c11 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS On)


include_directories(${CMAKE_BINARY_DIR}/configuration)
configure_file(tool/configuration/root_directory.h.in configuration/root_directory.h)


include_directories(${CMAKE_SOURCE_DIR}/tool/include)
find_package(gl3w CONFIG REQUIRED)
find_package(SDL2PP REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
include_directories(${SDL2_INCLUDE})
include_directories("${VCPKG_DIR}/installed/x64-windows/include/SDL2")

add_subdirectory("resource")
add_subdirectory("tool")

#添加例子
add_subdirectory("opengl_src")