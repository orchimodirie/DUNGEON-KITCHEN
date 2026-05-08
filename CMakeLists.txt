cmake_minimum_required(VERSION 4.2.1)

project(DungeonKitchen)

include_directories(include)

add_executable(DungeonKitchen src/main.cpp src/game.cpp src/displayUI.cpp
    src/Inventory.cpp)