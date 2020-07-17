//
// Created by maxim on 10.05.2019.
//

#ifndef GAMEGRAPHICLIBRARY_GRAPHICS_H
#define GAMEGRAPHICLIBRARY_GRAPHICS_H

#include <iostream>
#include <memory>
#include <fstream>
#include <utility>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
void construct();
GLFWwindow * createMonitor(const char * title);
GLFWwindow * createWindow(const char * title);


#endif //GAMEGRAPHICLIBRARY_GRAPHICS_H
