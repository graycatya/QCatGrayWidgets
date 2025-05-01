cmake_minimum_required(VERSION 3.9)

project(QCatGrayTabbar LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

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
      Qt${QT_VERSION_MAJOR}::CorePrivate
      Qt${QT_VERSION_MAJOR}::GuiPrivate
      Qt${QT_VERSION_MAJOR}::WidgetsPrivate)

target_link_libraries(${PROJECT_NAME}_a 
  PRIVATE 
      Qt${QT_VERSION_MAJOR}::Core
      Qt${QT_VERSION_MAJOR}::Gui
      Qt${QT_VERSION_MAJOR}::Widgets
      Qt${QT_VERSION_MAJOR}::CorePrivate
      Qt${QT_VERSION_MAJOR}::GuiPrivate
      Qt${QT_VERSION_MAJOR}::WidgetsPrivate)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})