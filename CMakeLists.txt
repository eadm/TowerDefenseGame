cmake_minimum_required(VERSION 3.0.2)
project(TowerDefenceGame)

include_directories(libs/SFML/include)

if (UNIX)
    if (APPLE)
        link_directories(libs/SFML/lib/dylib)
        message(STATUS ">>> Building for Mac")
    else (APPLE)
        link_directories(libs/SFML/lib/so)
        message(STATUS ">>> Building for Linux")
    endif(APPLE)
endif (UNIX)


link_libraries(sfml-graphics)
link_libraries(sfml-window)
link_libraries(sfml-system)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp include/constants/Sizes.h include/constants/Directions.h include/file/Reader.h src/file/Reader.cpp include/level/LevelColors.h src/level/LevelColors.cpp include/objects/TextureManager.h include/objects/GraphicObject.h src/objects/GraphicObject.cpp src/objects/TextureManager.cpp include/objects/Bullet.h include/objects/enemies/Enemy.h src/objects/enemies/Enemy.cpp src/objects/Bullet.cpp include/objects/Canon.h src/objects/Canon.cpp include/objects/enemies/Plane.h src/objects/enemies/Plane.cpp include/objects/enemies/Panzer.h src/objects/enemies/Panzer.cpp include/level/Level.h include/algo/Paths.h src/algo/Paths.cpp src/level/Level.cpp)
add_executable(TowerDefenceGame ${SOURCE_FILES})