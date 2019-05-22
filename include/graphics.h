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
#include <GLEW/include/GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

auto CreateMonitor();
GLFWwindow * initializate();
void key_callback(GLFWwindow * window,int key,int scancode,int action,int mode);



#endif //GAMEGRAPHICLIBRARY_GRAPHICS_H
