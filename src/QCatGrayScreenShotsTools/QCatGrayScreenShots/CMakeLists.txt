cmake_minimum_required(VERSION 3.10)

project(QCatGrayScreenShots LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

option(QT_PLATFORM "Build Qt Platform"  NO)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED Gui QUIET)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED Gui QUIET)


file(GLOB SRC_LIST
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

if(TARGET "Qt${QT_VERSION_MAJOR}::Gui")
    set(QT_PLATFORM ON)
else()
    set(QT_PLATFORM OFF)
endif()

if(NOT QT_PLATFORM)
    list(REMOVE_ITEM SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/QCatGrayScreenShot.h"
                                "${CMAKE_CURRENT_SOURCE_DIR}/QCatGrayScreenShot.cpp")
endif()

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

add_library(${PROJECT_NAME}_a STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        Qt${QT_VERSION_MAJOR}::Gui)


target_link_libraries(${PROJECT_NAME}_a 
    PRIVATE 
        Qt${QT_VERSION_MAJOR}::Gui)


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

## ==============================================================================
##
##  Configuration summary
##
## ==============================================================================
message(STATUS "------------------------------------------------------------" )
message(STATUS "[${PROJECT_NAME}] Configuration summary."                     )
message(STATUS "------------------------------------------------------------ ")
message(STATUS " System configuration:"                                       )
message(STATUS " .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS " .. CMake executable ............ = ${CMAKE_COMMAND}"         )
message(STATUS " .. CMake version ............... = ${CMAKE_VERSION}"         )
message(STATUS " .. System name ................. = ${CMAKE_SYSTEM}"          )
message(STATUS " .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"    )
message(STATUS " .. C compiler .................. = ${CMAKE_C_COMPILER}"      )
message(STATUS " .. size(void*) ................. = ${CMAKE_SIZEOF_VOID_P}"   )
message(STATUS " platform:"                                               )
message(STATUS " .. Build qt${QT_VERSION_MAJOR} platform  ........ = ${QT_PLATFORM}")
