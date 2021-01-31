//
// Created by maxim on 16.07.2020.
//

#include "../include/Game.h"
#include "GemulingEngine/include/Window.h"
#include "GemulingEngine/include/GLWindow.h"
#include "../include/init.h"
#include "../include/mainloop.h"
#include <memory>
#include <array>
#include <list>

short platformMotion = 0;
bool isSpaceButtonPress = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if(!isSpaceButtonPress) {
            isSpaceButtonPress = true;
        }
    }

    if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            platformMotion = -1;
        } else if (action == GLFW_RELEASE) {
            platformMotion = 0;
        }


    } else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            platformMotion = 1;
        } else if (action == GLFW_RELEASE) {
            platformMotion = 0;
        }
    }
}

void resize (GLFWwindow * window,int width, int height)
{
    glViewport(0, 0, width, height);
}

bool Game::startSinglePlay()
{
    int returnCode = 1;
    const std::string name = "Arkanoid";
    std::unique_ptr<Window> window;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Platform> platform;
    std::list<std::shared_ptr<Block>> blocks{};
    std::vector<std::string> fileData;

    try {
        fileData = getClearDataFromFile();
        window = fileData.at(0) == "full" ? std::make_unique<GLWindow>(name, true) : std::make_unique<GLWindow>(name);
        m_availableMaxLevel = std::stoi(fileData.at(1));
        ball = makeBall();
        platform = makePlatform(&platformMotion);
    } catch (const std::runtime_error& e) {
        window->terminate();
        throw e;
    }

    GLWindow * glWindow = dynamic_cast<GLWindow*>(window.get());
    glfwSetFramebufferSizeCallback(glWindow->get(), resize);
    glfwSetKeyCallback(glWindow->get(), key_callback);

    while (returnCode) {
        try {
            makeBlock("levels/level_" + std::to_string(m_availableMaxLevel) + ".dat", blocks);
            returnCode = mainloop(ball, platform, blocks, window, isSpaceButtonPress);
        } catch(const std::runtime_error &e) {
            window->terminate();
            throw e;
        }

        if (returnCode) {
            MatrixValue matrixValue{0., 0., 1., 0.03, 0.03, 0.};
            ball->setPosition(matrixValue);
            matrixValue = {0., -0.75, 1., 0.2, 0.2, 0.};
            platform->setPosition(matrixValue);
        }
    }

    return true;
}

std::vector<std::string> Game::getClearDataFromFile()
{
    std::vector<std::string> data{};
    std::ifstream read("path/setting.dat");
    std::string src{};

    if (!read.is_open()) {
        throw std::runtime_error("Cannot opened setting file");
    }

    read >> src;
    src = src.substr(src.find(':') + 1, src.size() - 1);
    data.push_back(src);
    src.clear();
    read.close();
    read.open("path/save.dat");

    if (!read.is_open()) {
        throw std::runtime_error("Cannot opened save file");
    }

    read >> src;
    src = src.substr(src.find(':') + 1, src.size() - 1);
    data.push_back(src);
    return data;
}

void Game::settingMenu()
{
    return;
}

Game::~Game(){}
