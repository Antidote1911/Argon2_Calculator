cmake_minimum_required(VERSION 3.5)

project(argon2calculator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

option(WITH_ARGON2          "Enable Argon2 algorithms family" ON)
option(BUILD_STATIC         "Build static binary" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/argon2.cmake)
include_directories(src)
include_directories(src/3rdparty)


set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h

        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(argon2calculator WIN32
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(argon2calculator SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(argon2calculator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

if (WIN32)
    target_link_libraries(argon2calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets advapi32 user32 ws2_32 userenv ${ARGON2_LIBRARY})
endif (WIN32)

if (UNIX)
    target_link_libraries(argon2calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets dl ${ARGON2_LIBRARY})
endif (UNIX)


if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
endif()
if(LINUX)    # if(NOT LINUX) should work, too, if you need that
    message(STATUS ">>> Linux")
    # linux stuff here
else()
    message(STATUS ">>> Not Linux")
        # stuff that should happen not on Linux
endif()
