cmake_minimum_required(VERSION 3.9)

project(QCatGrayWidgets LANGUAGES CXX)

if (UNIX)
add_compile_options(-Wall -fPIC -Wno-stringop-overflow)
endif(UNIX)

message(STATUS "------------------------------------------------------------" )
message(STATUS "[QCatGrayWidgets] Configuration summary."                     )
message(STATUS "------------------------------------------------------------ ")
message(STATUS " System configuration:"                                       )
message(STATUS " .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS " .. CMake executable ............ = ${CMAKE_COMMAND}"         )
message(STATUS " .. CMake version ............... = ${CMAKE_VERSION}"         )
message(STATUS " .. System name ................. = ${CMAKE_SYSTEM}"          )
message(STATUS " .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"    )
message(STATUS " .. C compiler .................. = ${CMAKE_C_COMPILER}"      )
message(STATUS " .. size(void*) ................. = ${CMAKE_SIZEOF_VOID_P}"   )
message(STATUS " .. cmake current source ................. = ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS " .. cmake system name ................. = ${CMAKE_SYSTEM_NAME}")
message(STATUS "------------------------------------------------------------ ")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(QtConfig)

set(3RDPARTY
    libqrencode
)

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

set(EXAMPLES
    qrencodewidget
    qrencodeqml
    qcustomplotwidget
)

foreach(3rdparty_module ${3RDPARTY})
    if(${3rdparty_module} STREQUAL "libqrencode")
        set(WITH_TOOLS OFF)
    endif()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/${3rdparty_module})
endforeach(3rdparty_module ${3RDPARTY})

foreach(module ${MODULES})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/${module})
endforeach(module ${MODULES})

foreach(example ${EXAMPLES})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/${example})
endforeach(example ${EXAMPLES})

