//
// Created by maxim on 16.07.2020.
//

#include "Game.h"
#include "GameEngine/filedata.h"
#include "init.h"
#include "levels.h"
#include <memory>
#include <functional>
#include <array>
#include <exception>
#include <list>

short platformMotion = 0;
bool isSpaceButtonPress = false;

void key_callback(GLFWwindow * window,int key,int scancode,int action,int mode)
{
    if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }


    if((key==GLFW_KEY_LEFT || key==GLFW_KEY_A) && (action == GLFW_PRESS)) // || action == GLFW_PRESS))
    {
        platformMotion = -1;
    }
    else if((key==GLFW_KEY_RIGHT || key==GLFW_KEY_D) && (action == GLFW_PRESS)) // || action == GLFW_PRESS))
    {
        platformMotion = 1;
    }

    if((key==GLFW_KEY_SPACE) && action == GLFW_PRESS)
    {
        if(!isSpaceButtonPress)
        {
            isSpaceButtonPress = true;
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
    string name="Arkanoid";

    /*
    if(fileData.at(0)=="full")
    {
        window=createMonitor(name.c_str());
    }

    else
    {
        window=createWindow(name.c_str());
    }
    */

    window = createWindow(name.c_str());

    return window;

}

auto getLevels()
{
    std::array levels =
            {
                    lvl1, lvl2, lvl3, lvl4, lvl5, lvl6, lvl7, lvl8,
                    lvl9, lvl10, lvl11, lvl12, lvl13, lvl14, lvl15, lvl16,
                    lvl17, lvl18, lvl19, lvl20, lvl21, lvl22, lvl23, lvl24,
                    lvl25, lvl26, lvl27, lvl28, lvl29, lvl30, lvl31, lvl32,
            };

    return levels;
}

Game::Game(QObject * parent) : QObject(parent){};

void Game::setScreenSize(QRect screenSize)
{
this->screen = screenSize;
}

/*
 TODO:
     * make the platform move smoothly +-
     * make the better physics
*/

bool Game::startSinglePlay()
{
    int returnCode;
    list<shared_ptr<Block>> blocks;
    vector<string> fileData; //=getClearDataFromFile();
    GLFWwindow * window=createDisplay(fileData);
    glfwSetFramebufferSizeCallback (window, resize);
    auto levels = getLevels();
    auto ball = makeBall(window);
    auto platform = makePlatform(window, &platformMotion);
    glfwSetKeyCallback(window, key_callback);

    for (const auto &func:levels)
    {
        func(window, blocks);

        try
        {
            returnCode = mainloop(ball, platform, blocks, window, isSpaceButtonPress);
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            break;
        }

        if (returnCode == 1)
        {
            // ball->setPosition(params);
            // platform->setPosition(params);
            continue;
        }

    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return true;
}

bool Game::startMuiliPlay()
{
    return false;
}

void Game::achievementPage()
{
    return;
}

void Game::settingMenu()
{
    return;
}

int Game::getWidth()
{
    return screen.width();
}

int Game::getHeight()
{
    return screen.height();
}

Game::~Game(){};
