cmake_minimum_required(VERSION 3.10.0)

# if we are using an IDE to work with the project
project(helloworld)

# Qt specific features
set(CMAKE_AUTOMOC ON)  # process headers of MOC files
set(CMAKE_AUTORCC ON)  # to process of Qt resources
set(CMAKE_AUTOUIC ON)  # for building the Qt designer UI files

# To look for headers in the current source directory and build director
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# To call the Qt5 version and the dependencies QWidgets and QtCore(not explecitely given as depend on QWidget)
find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets)

add_executable(helloworld
  mainwindow.ui
  mainwindow.cpp
  main.cpp
  object.cpp
  resources.qrc)

# To link the executable with the libraries
target_link_libraries(helloworld
  Qt5::Widgets)

# So fart no path for the executable was given!?
