//
// Created by maxim on 16.07.2020.
//

#include "../include/Game.h"
#include "GemulingEngine/include/GLWindow.h"
#include "../include/init.h"
#include "../include/mainloop.h"
#include <array>

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

Game::Game()
    : m_ball{}, m_platform{}, m_blocks{}, m_windowMode(""), m_level(1)
{
    getClearDataFromFile();
}

unsigned int Game::startSinglePlay()
{
    int returnCode = 1;
    const std::string name = "Arkanoid";
    std::unique_ptr<Window> window;

    try {
        window = m_windowMode == "full" ? std::make_unique<GLWindow>(name, true) : std::make_unique<GLWindow>(name);
        m_ball = makeBall();
        m_platform = makePlatform(&platformMotion);
    } catch (const std::runtime_error& e) {
        window->terminate();
        throw e;
    }

    GLWindow * glWindow = dynamic_cast<GLWindow*>(window.get());
    glfwSetFramebufferSizeCallback(glWindow->get(), resize);
    glfwSetKeyCallback(glWindow->get(), key_callback);

    while (returnCode) {
        try {
            makeBlock("levels/level_" + std::to_string(m_level) + ".dat", m_blocks);
            returnCode = mainloop(m_ball, m_platform, m_blocks, window, isSpaceButtonPress, &platformMotion);
        } catch(const std::runtime_error &e) {
            window->terminate();
            throw e;
        }

        if (m_blocks.empty()) {
            returnCode = 2;
            break;
        }
    }

    if (returnCode == 2 && m_maxLevel == m_level) {
        ++m_maxLevel;
    }

    m_ball.reset();
    m_platform.reset();
    m_blocks.clear();
    isSpaceButtonPress = false;
    return returnCode;
}

void Game::setLevel(unsigned int level)
{
    m_level = level;
}

unsigned int Game::getMaxLevel()
{
    return m_maxLevel;
}

void Game::getClearDataFromFile()
{
    std::ifstream read("path/setting.dat");
    std::string src{};

    if (!read.is_open()) {
        throw std::runtime_error("Cannot opened setting file");
    }

    read >> src;
    m_windowMode = src.substr(src.find(':') + 1, src.size() - 1);
    src.clear();
    read.close();
    read.open("path/save.dat");

    if (!read.is_open()) {
        throw std::runtime_error("Cannot opened save file");
    }

    read >> src;
    src = src.substr(src.find(':') + 1, src.size() - 1);
    m_maxLevel = std::stoi(src);
}

void Game::setWindowMode(std::string mode)
{
    m_windowMode = mode;
}

std::string Game::getWindowMode()
{
    return m_windowMode;
}

void Game::writeData()
{
    std::string filename = "path/setting.dat";
    std::ofstream write{};
    write.open(filename);

    if (!write.is_open()) {
        throw std::runtime_error("Cannot saved data to file");
    }

    write.clear();
    write << "monitor:" << m_windowMode << std::endl;
    write.close();

    filename = "path/save.dat";
    write.open(filename);

    if (!write.is_open()) {
        throw std::runtime_error("Cannot saved data to file");
    }

    write.clear();
    write << "score:" + std::to_string(m_maxLevel) << std::endl;
    write.close();
}
