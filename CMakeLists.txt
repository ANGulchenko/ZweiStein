cmake_minimum_required(VERSION 3.5)

#set(CMAKE_CXX_COMPILER "g++")

project(ZweiStein
        VERSION 0.0.4
        LANGUAGES CXX
        HOMEPAGE_URL "https://github.com/ANGulchenko/ZweiStein"
        DESCRIPTION "ZweiStein is a remake of Einstein puzzle for a text-only terminal.")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
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

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
if (CURSES_FOUND)
    include_directories(${CURSES_INCLUDE_DIRS})
    target_link_libraries (MainProgram ${CURSES_LIBRARIES})
endif (CURSES_FOUND)
