cmake_minimum_required(VERSION 3.10)

project(QCatGrayTeachingTools LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions("-Wall -g")
#add_definitions(-std=c++17)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Svg)

set(QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/QCatGrayTeachingTools.qrc)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SvgWidgets)
qt_add_resources(QRC_FILES ${QRC_SOURCE_FILES})
else()
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})
endif()

file(GLOB SRC_LIST
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(${PROJECT_NAME}_a STATIC ${SRC_LIST}
                                  ${QRC_FILES})

add_library(${PROJECT_NAME} SHARED ${SRC_LIST}
                                   ${QRC_FILES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Svg)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    Qt${QT_VERSION_MAJOR}::SvgWidgets)
endif()

target_link_libraries(${PROJECT_NAME}_a 
    PRIVATE 
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Svg)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
target_link_libraries(${PROJECT_NAME}_a 
    PRIVATE 
    Qt${QT_VERSION_MAJOR}::SvgWidgets)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
