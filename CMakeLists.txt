cmake_minimum_required(VERSION 3.8)
project(Arkanoid VERSION 1.0.0)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
find_package(Qt5 COMPONENTS Widgets Core Quick Qml LinguistTools REQUIRED)
set(TS_FILES GameGUI_en_US.ts)

add_executable(Arkanoid main.cpp BaseGameObject.cpp BaseGameObject.h Ball.cpp Ball.h Platform.cpp Platform.h Block.cpp Block.h init.cpp init.h levels.cpp levels.h Game.cpp Game.h)

add_subdirectory(GameEngine)

target_link_libraries(Arkanoid GameEngine Qt5::Widgets Qt5::Core Qt5::Quick Qt5::Qml)

#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

install(TARGETS Arkanoid DESTINATION bin)
