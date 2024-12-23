cmake_minimum_required(VERSION 3.10)

project(Paint VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

file(GLOB_RECURSE PROJECT_SOURCES
        "paint/*.cpp"    "paint/.*hpp"
        "paint/shapes/*.cpp"    "paint/shapes/*.hpp"
        "paint/workspace_strategies/*.cpp"        "paint/workspace_strategies/*.hpp"
)

add_executable(Paint 
        main.cpp 
        ${PROJECT_SOURCES}
        resources.qrc
)

target_include_directories(Paint PRIVATE
        ${CMAKE_SOURCE_DIR}

)

target_link_libraries(Paint PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
