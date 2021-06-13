//
// Created by maxim on 17.07.2020.
//

#include <chrono>
#include "GemulingEngine/include/GLWindow.h"
#include "../include/mainloop.h"

glm::mat4 getMatrix(const std::shared_ptr<BaseGameObject> &object)
{
    float x{}, y{}, a{}, b{}, value = -1.f;
    glm::mat4 position = object->getPosition();
    x = position[0].x;
    y = position[0].y;
    a = position[3].x;
    b = position[3].y;

    for (size_t index = 0; index < 4; ++index) {
        position[index].x = x * value + a;
        value *= -1.f;
    }

    value = 1.f;

    for (size_t index = 0; index < 4; ++index) {
        position[index].y = y * value + b;

        if (!(index + 1 % 2)) {
            value *= -1.f;
        }
    }

    return position;
}

bool handlerEvent(const std::shared_ptr<Ball> &ball, const std::shared_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks)
{
    const float value = 0.0005;
    static float a{};
    float verticalSpeed = 0.015f;
    const float ellipse = 0.0525;
    ball->update();
    glm::mat4 ballPosition = getMatrix(std::static_pointer_cast<BaseGameObject>(ball));
    glm::mat4 platformPosition = getMatrix(std::static_pointer_cast<BaseGameObject>(platform));
    glm::mat4 blockPosition{};

    if (std::abs(ballPosition[2].y - platformPosition[0].y) < ellipse) {
        if (ballPosition[2].x >= platformPosition[0].x && ballPosition[3].x <= platformPosition[1].x) {
            a = -a + value;
            ball->setSpeed(a, verticalSpeed);
        }
    }

    if (std::abs(ballPosition[0].y + 1.2f) < ellipse) {
        return false;
    } else if (std::abs(ballPosition[0].x - 0.95f) < ellipse) {
        a = -a + value;
        verticalSpeed = std::abs(verticalSpeed);
        ball->setSpeed(a, verticalSpeed);
    } else if (std::abs(ballPosition[1].x + 0.95f) < ellipse) {
        a = -a + value;
        verticalSpeed = -std::abs(verticalSpeed);
        ball->setSpeed(a, verticalSpeed);
    } else if (std::abs(ballPosition[0].y - 0.98f) < ellipse) {
        a = -a + value;
        verticalSpeed = -std::abs(verticalSpeed);
        ball->setSpeed(a, verticalSpeed);
    }

    for (auto it = blocks.begin(); it != blocks.end();++it) {
        blockPosition = getMatrix(std::static_pointer_cast<BaseGameObject>(*it));

        if (std::abs(ballPosition[2].y - blockPosition[0].y) < ellipse) {
            if (ballPosition[2].x >= blockPosition[0].x && ballPosition[3].x <= blockPosition[1].x) {
                a = -a + value;
                verticalSpeed = -verticalSpeed;
                ball->setSpeed(a, verticalSpeed);
                it = blocks.erase(it);
            }
        } else if (std::abs(blockPosition[2].y - ballPosition[0].y) < ellipse) {
            if (blockPosition[2].x >= ballPosition[0].x && blockPosition[3].x <= ballPosition[1].x) {
                a = -a + value;
                verticalSpeed = -verticalSpeed;
                ball->setSpeed(a, verticalSpeed);
                it = blocks.erase(it);
            }
        } else if (blockPosition[1].y >= ballPosition[0].y && ballPosition[0].y >= blockPosition[3].y) {
            if (std::abs(blockPosition[1].x - ballPosition[0].x) < ellipse) {
                a = -a + value;
                verticalSpeed = -verticalSpeed;
                ball->setSpeed(a, verticalSpeed);
                it = blocks.erase(it);
            }
        } else if (blockPosition[1].y >= ballPosition[2].y && ballPosition[2].y >= blockPosition[3].y) {
            if (std::abs(blockPosition[1].x - ballPosition[2].x) < ellipse) {
                a = -a + value;
                verticalSpeed = -verticalSpeed;
                ball->setSpeed(a, verticalSpeed);
                it = blocks.erase(it);
            }
        } else if (blockPosition[0].y >= ballPosition[1].y && ballPosition[1].y >= blockPosition[2].y) {
            if (std::abs(blockPosition[0].x - ballPosition[1].x) < ellipse) {
                a = -a + value;
                verticalSpeed = -verticalSpeed;
                ball->setSpeed(a, verticalSpeed);
                it = blocks.erase(it);
            }
        } else if (blockPosition[0].y >= ballPosition[3].y && ballPosition[3].y >= blockPosition[2].y) {
            if (std::abs(blockPosition[0].x - ballPosition[3].x) < ellipse) {
                a = -a + value;
                verticalSpeed = -verticalSpeed;
                ball->setSpeed(a, verticalSpeed);
                it = blocks.erase(it);
            }
        }
    }

    return true;
}

void render(const std::unique_ptr<Window> &window, const std::shared_ptr<Ball> &ball, const std::shared_ptr<Platform> &platform,
            const std::list<std::shared_ptr<Block>> &blocks)
{
    window->clear();

    for (const auto &it : blocks) {
        it->render();
    }

    ball->render();
    platform->render();
}

int mainloop(std::shared_ptr<Ball> &ball, std::shared_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks,
             std::unique_ptr<Window> &window, bool &isSpaceActive, short *motion)
{
    GLWindow * glWindow = dynamic_cast<GLWindow*>(window.get());
    glm::mat4 model=glm::mat4(1.f);
    double delta_time{};
    std::chrono::system_clock::time_point timer = std::chrono::system_clock::now();

    while (!glfwWindowShouldClose(glWindow->get())) {
        glfwPollEvents();
        delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timer).count();

        if(delta_time < 16) {
            continue;
        }

        render(window, ball, platform, blocks);

        if(!isSpaceActive) {
            timer = std::chrono::system_clock::now();
            glfwSwapBuffers(glWindow->get());
            continue;
        } else if (blocks.empty()) {
            return 1;
        }

        if (*motion < 0) {
            platform->move(-0.02f);
        } else if (*motion > 0) {
            platform->move(0.02f);
        }

        if (!handlerEvent(ball, platform, blocks)) {
            MatrixValue matrixValue{0., 0., 1., 0.03, 0.03, 0.};
            ball->setPosition(matrixValue);
            ball->setSpeed(0, -0.01f);
            matrixValue = {0., -0.75, 1., 0.2, 0.2, 0.};
            platform->setPosition(matrixValue);
            isSpaceActive = false;
        }

        timer = std::chrono::system_clock::now();
        glfwSwapBuffers(glWindow->get());
    }

    return 0;
}
