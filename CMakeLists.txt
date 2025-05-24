cmake_minimum_required(VERSION 3.31)
project(DigitalJournal)

set(CMAKE_CXX_STANDARD 20)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC ON)            # <— key line
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_executable(DigitalJournal main.cpp
        RepositoryLayer/DataEntry.cpp
        RepositoryLayer/DataEntry.h)

target_link_libraries(DigitalJournal PRIVATE Qt6::Core Qt6::Widgets)