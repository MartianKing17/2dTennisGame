//
// Created by maxim on 05.08.2019.
//

#include "createGameLoop.h"

using namespace std;
using namespace chrono;

list<Block> * createBlocks(GLFWwindow *window)
{
    const size_t blockSize = 30;
    auto * blocks = new list<Block>();
    vector<GLfloat> startPosition;
    string objectInfo[3];
    float a, b, c;
    const float val_mat_scale[3] = {0.1,0.1,0};        // data special for block

    objectInfo[0]="texture/met_cube(crop).png";           // block texture
    objectInfo[1]="path/shaderPlatform.vs";               // block vs
    objectInfo[2]="path/shaderFragPlatform.fragment";     // block fragment shader

    Shader shader(objectInfo[1],objectInfo[2]);

    startPosition.insert(startPosition.begin(),   {1.f,1.f,0.f,   1.f,0.f,0.f,  1.f, 1.f});
    startPosition.insert(startPosition.begin()+8, {1.f,-1.f,0.f,  0.f,1.f,0.f,  1.f, 0.f});
    startPosition.insert(startPosition.begin()+16,{-1.f,-1.f,0.f, 0.f,0.f,1.f,  0.f,0.f});
    startPosition.insert(startPosition.begin()+24,{-1.f,1.f,0.f,  1.f,1.f,0.f,  0.f,1.f});


    ObjectCreater creater(startPosition,objectInfo[0]);
    creater.initializate();
    creater.setMatrixScale(val_mat_scale[0], val_mat_scale[1], val_mat_scale[2]);
    Block * block;

    a = -0.9;
    b = -0.9;
    c = 0.;

    for (size_t i = 0; i < blockSize; ++i)
    {
        if(a == 1.1)
        {
            b -=0.2;
            a = -0.9;
        }

        creater.setMatrixTranslate(a, b, c);
        block = new Block(creater, window, shader);
        blocks->push_back(*block);
        a += 0.2;
    }

    return blocks;
}


BaseGameObject *createBall(GLFWwindow *window)
{
    vector<GLfloat> startPosition;
    string objectInfo[3];
    bool ball_forward = false;
    const float val_mat_translate[3] = {0.,0.,1.};
    const float val_mat_scale[3] = {0.03,0.03,0.};
    objectInfo[0]="texture/platform_var1(crop).png";
    objectInfo[1]="path/shaderPlatform.vs";
    objectInfo[2]="path/shaderFragPlatform.fragment";

    Shader shader(objectInfo[1],objectInfo[2]);

    startPosition.insert(startPosition.begin(),   {1.f,1.f,0.f,   1.f,0.f,0.f,  1.f, 1.f});
    startPosition.insert(startPosition.begin()+8, {1.f,-1.f,0.f,  0.f,1.f,0.f,  1.f, 0.f});
    startPosition.insert(startPosition.begin()+16,{-1.f,-1.f,0.f, 0.f,0.f,1.f,  0.f,0.f});
    startPosition.insert(startPosition.begin()+24,{-1.f,1.f,0.f,  1.f,1.f,0.f,  0.f,1.f});


    ObjectCreater creater(startPosition,objectInfo[0]);
    creater.initializate();
    creater.setMatrixTranslate(val_mat_translate[0], val_mat_translate[1], val_mat_translate[2]);
    creater.setMatrixScale(val_mat_scale[0], val_mat_scale[1], val_mat_scale[2]);
    return new Ball(creater, window, shader);
}

BaseGameObject *createPlatform(GLFWwindow *window, bool *motionSet)
{
    vector<GLfloat> startPosition;
    string objectInfo[3];
    const float val_mat_translate[3] = {0., -0.75, 1.};
    const float val_mat_scale[3] = {0.25, 0.25, 0.};
    objectInfo[0]="texture/ball(crop).png";
    objectInfo[1]="path/shaderBall.vs";
    objectInfo[2]="path/shaderFragBall.fragment";

    Shader shader(objectInfo[1],objectInfo[2]);

    startPosition.insert(startPosition.begin(),   {1.f,1.f,0.f,    1.f,0.f,0.f,  1.f, 1.f});
    startPosition.insert(startPosition.begin()+8, {1.f,-1.f,0.f,   0.f,1.f,0.f,  1.f, 0.f});
    startPosition.insert(startPosition.begin()+16,{-1.f,-1.f,0.f,  0.f,0.f,1.f,  0.f,0.f});
    startPosition.insert(startPosition.begin()+24,{-1.f,1.f,0.f,   1.f,1.f,0.f,  0.f,1.f});

    ObjectCreater creater(startPosition,objectInfo[0]);
    creater.initializate();
    creater.setMatrixTranslate(val_mat_translate[0], val_mat_translate[1], val_mat_translate[2]);
    creater.setMatrixScale(val_mat_scale[0], val_mat_scale[1], val_mat_scale[2]);
    return new Platform(creater, window, shader, motionSet);
}


void update(BaseGameObject *ball, BaseGameObject *platform)
{
    ball->update();
    platform->update();
}

void render(BaseGameObject *ball, BaseGameObject *platform, list<Block> *blocks, glm::mat4 model)
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    ball->render();
    platform->render();

/*
    for (auto iter = blocks->begin(); iter != blocks->end() ; iter++)
    {
        iter->render();
    }
*/

}

bool checkTouch(Ball *ball, Platform *platform, list<Block> *blocks)
{
    float gorizontalSpeed, verticalSpeed;

    const float ballBottomPoint = ball->getVerticalPlace() - ball->getRadius();


    if((ballBottomPoint - platform->getTop() <= 0.01) && (ball->getGorizontalPlace() >= platform->getLeft()) && (ball->getGorizontalPlace() <= platform->getRight()))
    {
        gorizontalSpeed =  0.01;
        verticalSpeed   =  0.01;

        /*
            The angle of the bounce of the ball from the platform, calculated as arccos((x - 0.5l) /0.5l)
            Where l is platform length and x is long from the left edge to the point where the ball falls
        */

        ball->setSpeed(gorizontalSpeed, verticalSpeed);
    }
    else if(abs(ball->getVerticalPlace() + ball->getRadius() - 1.) <= 0.01)
    {
        gorizontalSpeed = -0.01;
        verticalSpeed   = -0.01;
        ball->setSpeed(gorizontalSpeed, verticalSpeed);
    }
    else if(abs(ball->getVerticalPlace() - ball->getRadius() - (-1)) <= 0.01)
    {
        ball->setSpeed(0, -0.01f);
        return false;
    }

    if(abs(ball->getGorizontalPlace() - ball->getRadius() - (-1)) <= 0.01)
    {
        gorizontalSpeed =  0.01;
        verticalSpeed   = -0.01;
        ball->setSpeed(gorizontalSpeed, verticalSpeed);
    }
    else if(abs(ball->getGorizontalPlace() + ball->getRadius() - 1) <= 0.01)
    {
        gorizontalSpeed = -0.01;
        verticalSpeed   =  0.01;
        ball->setSpeed(gorizontalSpeed, verticalSpeed);
    }


    /*for (auto iter = blocks->begin(); iter != blocks->end() ; iter++)
    {
        if((ball->getVerticalPlace() + ball->getRadius()) == (iter->getVerticalPlace() - iter->getRadius()))
        {
            blocks->erase(iter);
            ball->setSpeed(0, 0);
        }
    }*/

    return true;
}

void mainloop(BaseGameObject *ball, BaseGameObject *platform, list<Block> *blocks, GLFWwindow *window,
              bool &isSpaceActive)
{
    glm::mat4 model=glm::mat4(1.f);
    double delta_time = 0.;
    system_clock::time_point timer = system_clock::now();

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        delta_time = duration_cast<milliseconds>(system_clock::now() - timer).count();

        if(delta_time < 16)
        {
            continue;
        }

        render(ball, platform, blocks, model);

        if(!isSpaceActive)
        {
            timer = system_clock::now();
            glfwSwapBuffers(window);
            continue;
        }

        /*
        if(blocks->empty())
        {
            //do smth
        }
        */

        if(!checkTouch((Ball *) ball, (Platform *) platform, blocks))
        {
            const float val_mat_translate_ball[3] = {0.,0.,1.};
            const float val_mat_scale_ball[3] = {0.03,0.03,0.};

            const float val_mat_translate_platform[3] = {0., -0.75, 1.};
            const float val_mat_scale_platform[3] = {0.25, 0.25, 0.};

            ball->setMatrixTranslate(val_mat_translate_ball[0], val_mat_translate_ball[1], val_mat_translate_ball[2]);
            ball->setMatrixScale(val_mat_scale_ball[0], val_mat_scale_ball[1], val_mat_scale_ball[2]);

            platform->setMatrixTranslate(val_mat_translate_platform[0], val_mat_translate_platform[1],
                                         val_mat_translate_platform[2]);
            platform->setMatrixScale(val_mat_scale_platform[0], val_mat_scale_platform[1], val_mat_scale_platform[2]);

            isSpaceActive = false;
        }

        update(ball, platform);

        timer = system_clock::now();
        glfwSwapBuffers(window);
    }
}