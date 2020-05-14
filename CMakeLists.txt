cmake_minimum_required(VERSION 3.5)

project(ZweiStein LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ZweiStein
    main.cpp
    game.cpp game.h
    cell.cpp cell.h
    field.cpp field.h
    interface.cpp interface.h
    command.cpp command.h
    hint.cpp hint.h
    hints.cpp hints.h
    )
