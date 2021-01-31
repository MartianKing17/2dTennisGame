//
// Created by maxim on 17.07.2020.
//

#include <chrono>
#include "GemulingEngine/include/GLWindow.h"
#include "../include/mainloop.h"

using namespace std;
using namespace chrono;

bool handlerEvent(std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks)
{
    struct Coordinate
    {
        float leftX, rightX;
        float topY, bottomY;
    };

    // Function for ball-platform interactive event

    auto ballPlatInterEvent = [](std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform)
    {
        float cx, cy, radius; // Ball center x and center y and radius
        glm::mat4 matCoor{};
        Coordinate ballCoor{}, platformCoor{};
        matCoor = ball->getPosition();
        cx = ((-matCoor[0][0] + matCoor[3][0]) + matCoor[0][0] + matCoor[3][0])/2.f;
        cy = ((-matCoor[1][1] + matCoor[3][1]) + matCoor[1][1] + matCoor[3][1])/2.f;
        radius = matCoor[0][0];
        ballCoor.leftX = cx - radius;
        ballCoor.rightX = cx + radius;
        ballCoor.topY = cy + radius;
        ballCoor.bottomY = cy - radius;
        matCoor = platform->getPosition();
        cx = ((-matCoor[0][0] + matCoor[3][0]) + matCoor[0][0] + matCoor[3][0])/2.f;
        cy = ((-matCoor[1][1] + matCoor[3][1]) + matCoor[1][1] + matCoor[3][1])/2.f;
        radius = matCoor[0][0];
        platformCoor.leftX = cx - radius + 0.03f;
        platformCoor.rightX = cx + radius - 0.03f;
        platformCoor.topY = cy + radius - 0.18f;
        platformCoor.bottomY = cy - radius + 0.17f;

        const float ellipse = 0.000001;

        if (std::abs(platformCoor.topY - ballCoor.bottomY) < ellipse) {
            if (ballCoor.leftX > platformCoor.leftX && ballCoor.rightX < platformCoor.rightX) {
                ball->setSpeed(0, 0.01f);
            }
        }

        return true;
    };


    // Function for ball-block interactive event
    auto blockBallInterEvent = [](std::unique_ptr<Ball> &ball, std::list<std::shared_ptr<Block>> &blocks)
    {
        float cx{}, cy{}, radius{};
        glm::mat4 matCoor{};
        Coordinate ballCoor{}, blockCoor{};
        matCoor = ball->getPosition();
        cx = ((-matCoor[0][0] + matCoor[3][0]) + matCoor[0][0] + matCoor[3][0])/2.f;
        cy = ((-matCoor[1][1] + matCoor[3][1]) + matCoor[1][1] + matCoor[3][1])/2.f;
        radius = matCoor[0][0];
        ballCoor.leftX = cx - radius;
        ballCoor.rightX = cx + radius;
        ballCoor.topY = cy + radius;
        ballCoor.bottomY = cy - radius;

        for (auto it = blocks.begin(); it != blocks.end();++it) {
            matCoor = it->get()->getPosition();
            cx = ((-matCoor[0][0] + matCoor[3][0]) + matCoor[0][0] + matCoor[3][0])/2.f;
            cy = ((-matCoor[1][1] + matCoor[3][1]) + matCoor[1][1] + matCoor[3][1])/2.f;
            radius = matCoor[0][0];
            blockCoor.leftX = cx - 0.075;
            blockCoor.rightX = cx + 0.075;
            blockCoor.topY = cy + 0.05;
            blockCoor.bottomY = cy - 0.05;

            const float ellipse = 0.001;
            if (std::abs(ballCoor.topY - blockCoor.bottomY) < ellipse) {
                if (ballCoor.leftX > blockCoor.leftX && ballCoor.rightX < blockCoor.rightX) {
                    ball->setSpeed(0, -0.01f);
                    it = blocks.erase(it);
                }
            }
        }

    };


    // Checking if the ball is in the game zone

    auto checkBallGameZone = [](std::unique_ptr<Ball> &ball)->bool
    {
        float cx{}, cy{}, radius{};
        glm::mat4 matCoor{};
        Coordinate ballCoor{};
        matCoor = ball->getPosition();
        cx = ((-matCoor[0][0] + matCoor[3][0]) + matCoor[0][0] + matCoor[3][0])/2.f;
        cy = ((-matCoor[1][1] + matCoor[3][1]) + matCoor[1][1] + matCoor[3][1])/2.f;
        radius = matCoor[0][0];
        ballCoor.leftX = cx - radius;
        ballCoor.rightX = cx + radius;
        ballCoor.topY = cy + radius;
        ballCoor.bottomY = cy - radius;

        const float ellipse = 0.001;

        // If ball was fall out from game zone

        if (ballCoor.topY < -1.2f) {
            return false;
        } else if (std::abs(ballCoor.leftX + 1.f) < ellipse) {
            ball->setSpeed(0.01f, -0.01f);
        } else if (std::abs(ballCoor.rightX - 1.f) < ellipse) {
            ball->setSpeed(-0.01f, 0.01f);
        } else if (std::abs(ballCoor.topY - 1.f) < ellipse) {
            ball->setSpeed(-0.01f, -0.01f);
        }

        return true;
    };

    bool ballIsFall = checkBallGameZone(ball);
    ballPlatInterEvent(ball, platform);
    blockBallInterEvent(ball, blocks);
    return ballIsFall;
}

bool update(std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks)
{
    ball->update();
    platform->update();

    for(const auto &it : blocks) {
        it->update();
    }

    return handlerEvent(ball, platform, blocks);
}

void render(unique_ptr<Window> &window, std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform,
            std::list<std::shared_ptr<Block>> &blocks)
{
    window->clear();

    for (const auto &it : blocks) {
        it->render();
    }

    ball->render();
    platform->render();
}

int mainloop(std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks,
             unique_ptr<Window> &window, bool &isSpaceActive)
{
    GLWindow * glWindow = dynamic_cast<GLWindow*>(window.get());
    glm::mat4 model=glm::mat4(1.f);
    double delta_time{};
    system_clock::time_point timer = system_clock::now();

    while (!glfwWindowShouldClose(glWindow->get())) {
        glfwPollEvents();
        delta_time = duration_cast<milliseconds>(system_clock::now() - timer).count();

        if(delta_time < 16) {
            continue;
        }

        render(window, ball, platform, blocks);

        if(!isSpaceActive) {
            timer = system_clock::now();
            glfwSwapBuffers(glWindow->get());
            continue;
        } else if (blocks.empty()) {
            return 1;
        }

        if (!update(ball, platform, blocks)) {
            MatrixValue matrixValue{0., 0., 1., 0.03, 0.03, 0.};
            ball->setPosition(matrixValue);
            ball->setSpeed(0, -0.01f);
            matrixValue = {0., -0.75, 1., 0.2, 0.2, 0.};
            platform->setPosition(matrixValue);
            isSpaceActive = false;
        }

        timer = system_clock::now();
        glfwSwapBuffers(glWindow->get());
    }

    return 0;
}
