//
// Created by maxim on 22.05.2019.
//

#include "GameEngine/filedata.h"
#include "GameEngine/createGameLoop.h"
#include <memory>
#include <list>

using namespace std;

bool state[3]={false};

void key_callback(GLFWwindow * window,int key,int scancode,int action,int mode)
{
    if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }


    if((key==GLFW_KEY_LEFT || key==GLFW_KEY_A) && (action == GLFW_PRESS)) // || action == GLFW_PRESS))
    {
        state[1] = false;
        state[0] = true;
    }
    else if((key==GLFW_KEY_RIGHT || key==GLFW_KEY_D) && (action == GLFW_PRESS)) // || action == GLFW_PRESS))
    {
        state[0] = false;
        state[1] = true;
    }
    else if(((key==GLFW_KEY_RIGHT || key==GLFW_KEY_D) || (key==GLFW_KEY_LEFT || key==GLFW_KEY_A)) && (action == GLFW_RELEASE))
    {
        state[0] = false;
        state[1] = false;
    }


    if((key==GLFW_KEY_SPACE) && action == GLFW_PRESS)
    {
        if(!state[2])
        {
            state[2] = true;
        }
    }
}

void resize (GLFWwindow * window,int width, int height)
{
    glViewport(0, 0, width, height);
}


//Check setting. If "full" make full screen window, null not full screen
GLFWwindow * createDisplay(vector<string> fileData)
{
    GLFWwindow * window;
    string name="test";

    if(fileData.at(0)=="full")
    {
        window=createMonitor(name.c_str());
    }

    else
    {
        window=createWindow(name.c_str());
    }

    return window;
}

/*
 TODO:
     * make the platform move smoothly +-
     * make the better physics
*/

int main()
{
    BaseGameObject * ball=nullptr,* platform=nullptr;
    list<Block> * blocks;
    vector<string> fileData=getClearDataFromFile();
    GLFWwindow * window=createDisplay(fileData);
    glfwSetFramebufferSizeCallback (window, resize);
    ball = createBall(window);
    platform = createPlatform(window, state);
    blocks = createBlocks(window);
    glfwSetKeyCallback(window, key_callback);
    mainloop(ball, platform, blocks, window, state[2]);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
