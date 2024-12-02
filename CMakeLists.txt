cmake_minimum_required(VERSION 3.27)
project(board_games)

set(CMAKE_CXX_STANDARD 23)

add_executable(board_games
        BoardGame_Classes.h
        main.cpp
        MinMaxPlayer.h)
