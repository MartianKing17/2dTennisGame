//
// Created by maxim on 05.08.2019.
//

#include "createGameLoop.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

BaseGameObject * createBall(GLFWwindow * window)
{
    vector<GLfloat> startPosition;
    string objectInfo[3];
    float val_mat_translate[3] = {0.,0.,1.};
    float val_mat_scale[3] = {0.03,0.03,0.};
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
    creater.set_matrix_translate(val_mat_translate[0], val_mat_translate[1], val_mat_translate[2]);
    creater.set_matrix_scale(val_mat_scale[0], val_mat_scale[1],val_mat_scale[2]);
    return new Ball(creater, window, shader, false);
}

BaseGameObject *createPlatform(GLFWwindow *window, bool *motionSet)
{
    vector<GLfloat> startPosition;
    string objectInfo[3];
    float val_mat_translate[3] = {0., -0.75, 1.};
    float val_mat_scale[3] = {0.25, 0.25, 0.};
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
    creater.set_matrix_translate(val_mat_translate[0], val_mat_translate[1], val_mat_translate[2]);
    creater.set_matrix_scale(val_mat_scale[0], val_mat_scale[1],val_mat_scale[2]);
    return new Platform(creater, window, shader, motionSet);
}


void update(BaseGameObject *ball, BaseGameObject *platform)
{
    ball->update();
    platform->update();
}

void render(BaseGameObject *ball, BaseGameObject *platform, glm::mat4 model)
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    ball->render();
    platform->render();
}

bool check_torch(BaseGameObject * ball,BaseGameObject * platform)
{
    auto pos_ball = ball->return_position();
    auto pos_platform = platform->return_position();

    /*
    if(pos_ball.second == pos_platform.second)
    {
        return true;
    }
     */

    return false;
}

void mainloop(BaseGameObject * ball,BaseGameObject * platform,GLFWwindow * window)
{
    glm::mat4 model=glm::mat4(1.f);
    double delta_time = 0.;
    system_clock::time_point timer = system_clock::now();
    int k = 0;


    while (!glfwWindowShouldClose(window))
    {

        delta_time = duration_cast<milliseconds>(system_clock::now() - timer).count();


        if(delta_time < 16 * 100)
        {
            continue;
        }


        glfwPollEvents();

        /*
        if(check_torch(ball, platform))
        {
            ball_forward = true;
        }
        else
        {
            ball_forward = false;
        }
         */


        update(ball, platform);
        render(ball, platform, model);

        //if(k <= 2) //fuc*ing code
        //{
            glfwSwapBuffers(window);
        //    k++;
        //}

        timer = system_clock::now();
    }
}