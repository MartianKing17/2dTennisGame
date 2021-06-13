cmake_minimum_required(VERSION 3.8)
project(ArkanoidCore VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
add_subdirectory(GemulingEngine)
add_library(ArkanoidCore SHARED include/Ball.h include/BaseGameObject.h include/init.h
        include/Block.h include/mainloop.h include/Platform.h src/Ball.cpp src/BaseGameObject.cpp
        src/Block.cpp src/init.cpp src/mainloop.cpp src/Platform.cpp include/Game.h src/Game.cpp)
target_link_libraries(ArkanoidCore GemulingEngine)
install(TARGETS ArkanoidCore CONFIGURATIONS Debug LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS ArkanoidCore CONFIGURATIONS Release LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
