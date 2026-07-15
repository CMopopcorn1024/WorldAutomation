cmake_minimum_required(VERSION 3.20)

project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(../Libraries/raylib raylib-build)
add_subdirectory(../Libraries/CPhysics CPhysics-build)

add_executable(Game
    main.cpp
    src/Player.cpp
    src/Harvestable.cpp
    src/BuildMap.cpp
    src/Wire.cpp
    src/ImageObject.cpp
    src/Electronic.cpp
    src/ElectronicPresets.cpp
)

target_include_directories(Game PRIVATE
    ../Libraries/raylib/src
)

target_link_libraries(Game PRIVATE
    CPhysics
    raylib
)