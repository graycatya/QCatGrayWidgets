cmake_minimum_required(VERSION 3.9)

project(QCatGrayWidgets LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -fPIC)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(QtConfig)

set(MODULES
    QCatGrayWidgetControls
    QCatGrayGraphicsDrawingBoard
    QCatGrayQcustomplot
    QCatGrayQrenCode
)

set(QCatGrayGraphicsDrawingBoard
    QCatGrayDrawingBoardTools
    QCatGrayTeachingTools
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS 
                                        Core Gui Widgets Svg OpenGL PrintSupport Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS 
                                            Core Gui Widgets Svg OpenGL PrintSupport Quick)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libqrencode libqrencode.out)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SvgWidgets)
endif()

add_module_sources(CURPATH_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src" ${MODULES})

#message("CURPATH_SRCS: ${CURPATH_SRCS}")

add_library(${PROJECT_NAME} SHARED ${CURPATH_SRCS})

add_library(${PROJECT_NAME}_a STATIC ${CURPATH_SRCS})

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Svg
        Qt${QT_VERSION_MAJOR}::OpenGL
        Qt${QT_VERSION_MAJOR}::PrintSupport
        Qt${QT_VERSION_MAJOR}::Quick
        qrencode)

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
        Qt${QT_VERSION_MAJOR}::Svg
        Qt${QT_VERSION_MAJOR}::OpenGL
        Qt${QT_VERSION_MAJOR}::PrintSupport
        Qt${QT_VERSION_MAJOR}::Quick
        qrencode)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
target_link_libraries(${PROJECT_NAME}_a 
    PRIVATE 
    Qt${QT_VERSION_MAJOR}::SvgWidgets)
endif()

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libqrencode)
target_include_directories(${PROJECT_NAME}_a 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libqrencode)
