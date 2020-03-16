cmake_minimum_required(VERSION 3.8)
project(2dTennisGame VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")


# Добавить в сборку исполняемый файл "MyProgram":
add_executable(2dTennisGame main.cpp)

# Требовать обработку файла "core/CMakeFiles.txt":
add_subdirectory(GameEngine)

# Скомпоновать исполняемый файл "MyProgram" со
# скомпилированной статической библиотекой "MyProgramCore":
target_link_libraries(2dTennisGame GameEngine)

# Установить исполняемый файл "MyProgram" в директорию "bin":
install(TARGETS 2dTennisGame DESTINATION bin)

