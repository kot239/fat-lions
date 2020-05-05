cmake_minimum_required(VERSION 3.5)

project(View LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Charts)

if(ANDROID)
  add_library(View SHARED
    main.cpp
    view.cpp
    view.h
    chart.cpp
    chart.h
    animal_view.h
    animal_view.cpp
    grass_view.h
    grass_view.cpp
    view.ui
    ../include/Animal.hpp
    ../include/Geometry.hpp
    ../include/Grass.hpp
    ../include/Lion.hpp
    ../include/Obstacle.hpp
    ../include/
    ../include/World.hpp
    ../include/Zebra.hpp
    ../src/Animal.cpp
    ../src/Geometry.cpp
    ../src/Grass.cpp
    ../src/
    ../src/World.cpp
  )
else()
  add_executable(View
    main.cpp
    view.cpp
    view.h
    chart.cpp
    chart.h
    animal_view.h
    animal_view.cpp
    grass_view.h
    grass_view.cpp
    view.ui
    ../include/Animal.hpp
    ../include/Geometry.hpp
    ../include/Grass.hpp
    ../include/Lion.hpp
    ../include/Obstacle.hpp
    ../include/VectorLogic.hpp
    ../include/World.hpp
    ../include/Zebra.hpp
    ../src/Animal.cpp
    ../src/Geometry.cpp
    ../src/Grass.cpp
    ../src/VectorLogic.cpp
    ../src/World.cpp
  )
endif()

target_link_libraries(View PRIVATE Qt5::Widgets Qt5::Charts)
