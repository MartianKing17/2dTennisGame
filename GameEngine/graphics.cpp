//
// Created by maxim on 10.05.2019.
//

#include "graphics.h"
#include "readfile.h"

using namespace std;

GLFWwindow * createMonitor(const char * title)
{
    if( !glfwInit() )
    {
        logic_error e("OpenGL don't initializiate");
        glfwTerminate();
        throw e;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

    GLFWmonitor * monitor;
    GLFWwindow * window;

    monitor=glfwGetPrimaryMonitor();

    const GLFWvidmode * mode= glfwGetVideoMode(monitor);

    window=glfwCreateWindow(mode->width,mode->height,title, monitor, nullptr);

    if(!window)
    {
      logic_error e("Window don't initiliziate");
      glfwTerminate();
      throw e;
    }

    glfwMakeContextCurrent(window);

    glewExperimental=GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        throw logic_error("Error");
    }

    glViewport(0,0,mode->width,mode->height);
    return window;
}

GLFWwindow * createWindow(const char * title)
{
    if( !glfwInit() )
    {
        logic_error e("OpenGL don't initializiate");
        glfwTerminate();
        throw e;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);

    GLFWmonitor * monitor;
    GLFWwindow * window;

    monitor=glfwGetPrimaryMonitor();

    const GLFWvidmode * mode= glfwGetVideoMode(monitor);

    int height,width;
    height=800;
    width=600;

    window=glfwCreateWindow(height,width,title, nullptr, nullptr);

    if(!window)
    {
        logic_error e("Window don't initiliziate");
        glfwTerminate();
        throw e;
    }

    glfwMakeContextCurrent(window);

    glewExperimental=GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        throw logic_error("Error");
    }

    glViewport(0,0,height,width);
    return window;
}
