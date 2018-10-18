
cmake_minimum_required(VERSION 2.8.11)


project(LearnOpengl)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(DCMAKE_TOOLCHAIN_FILE "G:/vcpkg/scripts/buildsystems/vcpkg.cmake")


set(CMAKE_CXX_STANDARD 11)  #Seting c11 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS On) 

add_subdirectory("Resource")
add_subdirectory("Common")

#添加例子
add_subdirectory("Example_1")
add_subdirectory("Example_2")