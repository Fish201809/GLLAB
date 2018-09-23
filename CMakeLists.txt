
cmake_minimum_required(VERSION 2.8.11)


project(LearnOpengl)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:/QT/5.11.1/msvc2017_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)  #Seting c11 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)



#QT5 Seting
find_package(Qt5 COMPONENTS Core Quick REQUIRED)
include_directories(Qt5)

file(GLOB ui_qml_dir ui/*.qml)
source_group(ui FILES ${ui_qml_dir})



#OSG Seting
set(OSG_DIR "F:/3rdParty/osg36")
find_package(OpenSceneGraph  3.6.3 REQUIRED osgDB osgGA osgUtil osgText osgViewer osgWidget)



file(GLOB src_dir src/*.cpp)
source_group("Source Files" FILES ${src_dir})

file(GLOB include_dir include/*.h)
source_group("Include Files" FILES ${include_dir})

include_directories("include")



add_executable(learn_opengl ${src_dir} ${include_dir} ${ui_qml_dir} "ui/qml.qrc" )
target_link_libraries(learn_opengl Qt5::Quick Qt5::Core)