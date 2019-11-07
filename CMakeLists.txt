cmake_minimum_required(VERSION 3.8)
project(2dTennisGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
include_directories(${CMAKE_SOURCE_DIR}/include)
set(SOIL_DIR "include/SOIL.h")
set(GLEW_DIR "include/glew.h")
set(GLFW_DIR "include/glfw3.h")
set(SOIL_LIBRARIES /home/maxim/Cpp-Frameworks/OpenGL/soil/lib/libSOIL.a)


if(${CMAKE_C_COMPILER} STREQUAL "/usr/bin/x86_64-w64-mingw32-gcc")
    set(OPENGL32_LIBRARIES ${CMAKE_SOURCE_DIR}/bin/win-bin/libopengl32.a)
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

    link_libraries(${OPENGL32_LIBRARIES}
            /home/maxim/Cpp-Frameworks/OpenGL/glfw/win-bin/lib-mingw-w64/glfw3.dll
            /home/maxim/Cpp-Frameworks/OpenGL/glew/win-bin/bin/Release/x64/glew32.dll
            ${SOIL_LIBRARIES}
            ${CMAKE_SOURCE_DIR}/bin/win-bin/libGameGraphic.dll)

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(OpenGL REQUIRED)
    link_libraries(${OPENGL_LIBRARIES} ${CMAKE_SOURCE_DIR}/bin/unix-bin/libGameGraphic.so
            /home/maxim/Cpp-Frameworks/OpenGL/glfw/unix-bin/src/libglfw.so
            /home/maxim/Cpp-Frameworks/OpenGL/glew/build/cmake/lib/libGLEW.so
            ${SOIL_LIBRARIES})
endif()

add_executable(2dTennisGame main.cpp Ball.h Ball.cpp Platform.h Platform.cpp Block.h Block.cpp BaseGameObject.h BaseGameObject.cpp ObjectCreater.h ObjectCreater.cpp
        filedata.h filedata.cpp createGameLoop.h createGameLoop.cpp
        include/SOIL.h include/SOIL.c include/image_DXT.h include/image_DXT.c include/image_helper.h
        include/image_helper.c include/stb_image_aug.h include/stb_image_aug.c include/stbi_DDS_aug.h include/stbi_DDS_aug_c.h)
