cmake_minimum_required(VERSION 3.31)
project(DigitalJournal)
set(CMAKE_CXX_STANDARD 20)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia Network)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_executable(DigitalJournal
        main.cpp
        RepositoryLayer/DataEntry.cpp
        RepositoryLayer/DataEntry.h
        RepositoryLayer/Repository.h
        RepositoryLayer/CSVRepo.cpp
        RepositoryLayer/CSVRepo.h
        RepositoryLayer/JSONRepo.cpp
        RepositoryLayer/JSONRepo.h
        ControllerLayer/CommandPattern/Command.h
        ControllerLayer/CommandPattern/AddCommand.h
        ControllerLayer/CommandPattern/RemoveCommand.h
        ControllerLayer/CommandPattern/UpdateCommand.h
        ControllerLayer/FilterStrategy/FilterStrategy.h
        ControllerLayer/FilterStrategy/AndFilterStrategy.h
        ControllerLayer/FilterStrategy/OrFilterStrategy.h
        ControllerLayer/Controller.cpp
        ControllerLayer/Controller.h
        UILayer/MainWindow.cpp
        UILayer/MainWindow.h
        UILayer/EntryWidget.h
        resources.qrc
        UILayer/EntryDialog.h
        ControllerLayer/AIHelper.cpp
        ControllerLayer/AIHelper.h
        API_KEY.h
        TestClass.cpp
)
target_link_libraries(DigitalJournal PRIVATE Qt6::Core Qt6::Widgets Qt6::Multimedia Qt6::Network)