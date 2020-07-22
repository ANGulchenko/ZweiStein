cmake_minimum_required(VERSION 3.5)

#set(CMAKE_CXX_COMPILER "g++")

project(ZweiStein LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_LIBRARY(MainProgram
    game.cpp game.h
    cell.cpp cell.h
    field.cpp field.h
    interface.cpp interface.h
    command.cpp command.h
    hint.cpp hint.h
    hintvertical.cpp hintvertical.h
    hintajacent.cpp hintajacent.h
    hintleftright.cpp hintleftright.h
    hintthreeajacent.cpp hintthreeajacent.h
    hints.cpp hints.h
)

add_executable(ZweiStein main.cpp)
target_link_libraries(ZweiStein MainProgram)
target_link_libraries(MainProgram -ltinfo)
target_link_libraries(MainProgram -lncursesw)
