
cmake_minimum_required(VERSION 2.8.11)


project(LearnOpengl)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(DCMAKE_TOOLCHAIN_FILE "G:/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)  #Seting c11 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#QT5 Seting
find_package(Qt5 COMPONENTS Core Quick REQUIRED)
include_directories(Qt5)


#OSG Seting
find_package(OpenSceneGraph REQUIRED osgDB osgGA osgUtil osgText osgViewer osgWidget)


file(GLOB src_dir src/*.cpp)
source_group("Source Files" FILES ${src_dir})

file(GLOB include_dir include/*.h)
source_group("Include Files" FILES ${include_dir})

file(GLOB qml_dir resources/ui/*.qml)
source_group("Ui Files" FILES ${qml_dir})

file(GLOB shader_dir resources/shaders/*.vert resources/shaders/*.frag)
source_group("Shader Files" FILES ${shader_dir})


include_directories("include")


add_executable(learn_opengl ${src_dir} ${include_dir} ${qml_dir} ${shader_dir} "resources/qml.qrc" )
target_link_libraries(learn_opengl Qt5::Quick Qt5::Core)