cmake_minimum_required(VERSION 3.5)

project(LifeSimulation)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include/)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Charts  REQUIRED)

add_executable(LifeSimulation
    include/
    include/World.hpp
    include/Zebra.hpp
    include/Animal.hpp
    include/Geometry.hpp
    include/Grass.hpp
    include/Lion.hpp
    include/ObstaclesView.hpp
    include/GrassView.hpp
    include/AnimalView.hpp
    include/Chart.hpp
    include/View.hpp
    include/View.ui
    src/Animal.cpp
    src/Geometry.cpp
    src/Grass.cpp
    src/
    src/World.cpp
    src/main.cpp
    src/View.cpp
    src/Chart.cpp
    src/AnimalView.cpp
    src/GrassView.cpp
    src/ObstaclesView.cpp
)

target_link_libraries(LifeSimulation PRIVATE Qt5::Widgets Qt5::Charts)
