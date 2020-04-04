//
// Created by maxim on 05.08.2019.
//

#include "createGameLoop.h"

using namespace std;
using namespace chrono;

float *getBallPoint(const Ball *ball);
float *getBlockPoint(const Block &block);
bool *findDistance(const float *ballPoint, const float *blockPoint, const size_t len);
bool * getSegment(const float *ballPoint, const float *blockPoint, const size_t len);
int sigma(float x);

list<Block> * createBlocks(GLFWwindow *window)
{
    const size_t blockSize = 30;
    auto * blocks = new list<Block>();
    vector<GLfloat> startPosition;
    string objectInfo[3];
    const float val_mat_scale[3] = {0.1,0.1,0};        // data special for block

    objectInfo[0] = "texture/met_cube(crop).png";           // block texture
    objectInfo[1] = "path/shaderPlatform.vs";               // block vs
    objectInfo[2] = "path/shaderFragPlatform.fragment";     // block fragment shader

    Shader shader(objectInfo[1],objectInfo[2]);

    startPosition.insert(startPosition.begin(),   {1.f,1.f,0.f,   1.f,0.f,0.f,  1.f, 1.f});
    startPosition.insert(startPosition.begin()+8, {1.f,-1.f,0.f,  0.f,1.f,0.f,  1.f, 0.f});
    startPosition.insert(startPosition.begin()+16,{-1.f,-1.f,0.f, 0.f,0.f,1.f,  0.f,0.f});
    startPosition.insert(startPosition.begin()+24,{-1.f,1.f,0.f,  1.f,1.f,0.f,  0.f,1.f});


    ObjectCreater creater(startPosition,objectInfo[0]);
    creater.setMatrixScale(val_mat_scale[0], val_mat_scale[1], val_mat_scale[2]);
    Block * block;

    const float c = 0.f;

    for (float b = 0.9f; b > 0.4f ; b -= 0.2f)
    {
        for (float a = -0.9f; a < 1.f ; a += 0.2f)
        {
            creater.setMatrixTranslate(a, b, c);
            creater.initializate();
            block = new Block(creater, window, shader);
            blocks->push_back(*block);
        }
    }

    return blocks;
}


BaseGameObject *createBall(GLFWwindow *window)
{
    vector<GLfloat> startPosition;
    string objectInfo[3];
    const float val_mat_translate[3] = {0.,0.,1.};
    const float val_mat_scale[3] = {0.03,0.03,0.};
    objectInfo[0] = "texture/ball(crop).png";
    objectInfo[1] = "path/shaderPlatform.vs";
    objectInfo[2] = "path/shaderFragPlatform.fragment";

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
    objectInfo[0] = "texture/platform_var1(crop).png";
    objectInfo[1] = "path/shaderBall.vs";
    objectInfo[2] = "path/shaderFragBall.fragment";

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

void render(BaseGameObject *ball, BaseGameObject *platform, list<Block> *blocks)
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    ball->render();
    platform->render();

    for (auto iter = blocks->begin(); iter != blocks->end() ; iter++)
    {
        iter->render();
    }

}

bool checkTouch(Ball *ball, Platform *platform, list<Block> *blocks)
{
    static float gorizontalSpeed, verticalSpeed;
    const float speed = 0.01f;
    const float ballBottomPoint = ball->getVerticalPlace() - ball->getRadius();


    if((ballBottomPoint - platform->getTop() <= 0.01) && (ball->getGorizontalPlace() >= platform->getLeft()) && (ball->getGorizontalPlace() <= platform->getRight()))
    {
        const float lenPlatform = abs(abs(platform->getRight()) + abs(platform->getLeft()));
        const float x = abs(abs(ball->getGorizontalPlace()) - abs(platform->getLeft()));
        float angle = x - 0.5f * lenPlatform;
        angle /= 0.5f * lenPlatform;
        angle = acos(angle);
        gorizontalSpeed = cos(angle) * speed;
        verticalSpeed   = sin(angle) * speed;

        /*
            The angle of the bounce of the ball from the platform, calculated as arccos((x - 0.5l) /0.5l)
            Where l is platform length and x is long from the left edge to the point where the ball falls
        */

        ball->setSpeed(gorizontalSpeed, verticalSpeed);
    }
    else if(abs(ball->getVerticalPlace() + ball->getRadius() - 1.) <= 0.01)
    {
        const float lenWall = 2.f;
        const float x = abs(ball->getGorizontalPlace());
        float angle = x - 0.5f * lenWall;
        angle /= 0.5f * lenWall;
        angle = acos(angle);
        gorizontalSpeed = cos(angle) * speed;
        verticalSpeed   = sin(angle) * speed - 0.01;

       /* if(abs(gorizontalSpeed) <= 0.001)
            gorizontalSpeed += 0.01 * sigma(gorizontalSpeed);

        if(abs(verticalSpeed) <= 0.001)
            verticalSpeed += 0.01 * sigma(verticalSpeed);*/

        //gorizontalSpeed = -0.01;
        //verticalSpeed   = -0.01;
        ball->setSpeed(gorizontalSpeed, verticalSpeed);
    }
    else if(abs(ball->getVerticalPlace() - ball->getRadius() - (-1)) <= 0.01)
    {
        ball->setSpeed(0, -0.01f);
        return false;
    }

    if(abs(ball->getGorizontalPlace() - ball->getRadius() - (-1)) <= 0.01)
    {
        const float lenWall = 2.f;
        const float x = abs(ball->getVerticalPlace());
        float angle = x - 0.5f * lenWall;
        angle /= 0.5f * lenWall;
        angle = acos(angle);
        gorizontalSpeed = abs(cos(angle) * speed);
        verticalSpeed   = sin(angle) * speed - 0.01;

        if(abs(gorizontalSpeed) <= 0.001)
            gorizontalSpeed += 0.01 * sigma(gorizontalSpeed);

        if(abs(verticalSpeed) <= 0.001)
            verticalSpeed += 0.01 * sigma(verticalSpeed);

        //gorizontalSpeed =  0.01;
        //verticalSpeed   = -0.01;
        ball->setSpeed(gorizontalSpeed, verticalSpeed);
    }
    else if(abs(ball->getGorizontalPlace() + ball->getRadius() - 1) <= 0.01)
    {
        const float lenWall = 2.f;
        const float x = abs(ball->getVerticalPlace());
        float angle = x - 0.5f * lenWall;
        angle /= 0.5f * lenWall;
        angle = acos(angle);
        gorizontalSpeed = cos(angle) * speed;
        verticalSpeed   = sin(angle) * speed - 0.01;

        if(abs(gorizontalSpeed) <= 0.001)
            gorizontalSpeed += 0.01 * sigma(gorizontalSpeed);

        if(abs(verticalSpeed) <= 0.001)
            verticalSpeed += 0.01 * sigma(verticalSpeed);

        //gorizontalSpeed = -0.01;
        //verticalSpeed   =  0.01;
        ball->setSpeed(gorizontalSpeed, verticalSpeed);
    }


    float * ballPoint = getBallPoint(ball);

    for (auto it = blocks->begin(); it != blocks->end(); it++)
    {
        const size_t len = 4;

        float * blockPoint = getBlockPoint(*it);

        bool * distance = findDistance(ballPoint, blockPoint, len);

        /*
            distance[0] = ball top point touch block bottom point
            distance[1] = ball bottom point touch block top point
            distance[2] = ball left point touch block right point
            distance[3] = ball right point touch block left point
        */

        if(distance[0])
        {
            verticalSpeed *= -1;
            it = blocks->erase(it);
            --it;
            ball->setSpeed(gorizontalSpeed, verticalSpeed);
        }
        else if(distance[1])
        {
            verticalSpeed *= -1;
            it = blocks->erase(it);
            --it;
            ball->setSpeed(gorizontalSpeed, verticalSpeed);
        }
        else if(distance[2])
        {
            gorizontalSpeed *= -1;
            it = blocks->erase(it);
            --it;
            ball->setSpeed(gorizontalSpeed, verticalSpeed);
        }
        else if(distance[3])
        {
            gorizontalSpeed *= -1;
            it = blocks->erase(it);
            --it;
            ball->setSpeed(gorizontalSpeed, verticalSpeed);
        }

        delete[] blockPoint;
        delete[] distance;
        blockPoint = nullptr;
        distance = nullptr;
    }

    delete[] ballPoint;
    ballPoint = nullptr;

    return true;
}

void mainloop(BaseGameObject *ball, BaseGameObject *platform, list<Block> *blocks, GLFWwindow *window, bool &isSpaceActive)
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

        render(ball, platform, blocks);

        if(!isSpaceActive)
        {
            timer = system_clock::now();
            glfwSwapBuffers(window);
            continue;
        }

        if(blocks->empty())
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

            delete blocks;
            blocks = createBlocks(window);
        }


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

float *getBallPoint(const Ball *ball)
{
    float * ballPoint = new float [4];

    /*
        ballPoint[0] - top point
        ballPoint[1] - bottom point
        ballPoint[2] - left point
        ballPoint[3] - right point
    */

    ballPoint[0] = ball->getVerticalPlace() + ball->getRadius();
    ballPoint[1] = ball->getVerticalPlace() - ball->getRadius();
    ballPoint[2] = ball->getGorizontalPlace() - ball->getRadius();
    ballPoint[3] = ball->getGorizontalPlace() + ball->getRadius();

    return ballPoint;
}

float *getBlockPoint(const Block &block)
{
    float * blockPoint = new float [4];

    /*
        blockPoint[0] - top point
        blockPoint[1] - bottom point
        blockPoint[2] - left point
        blockPoint[3] - right point
    */

    blockPoint[0] = block.getVerticalPlace() + block.getRadius();
    blockPoint[1] = block.getVerticalPlace() - block.getRadius();
    blockPoint[2] = block.getGorizontalPlace() - block.getRadius();
    blockPoint[3] = block.getGorizontalPlace() + block.getRadius();

    return blockPoint;
}

bool *findDistance(const float *ballPoint, const float *blockPoint, const size_t len)
{
    bool * distance = new bool[len];

    /*
         distanceBallPointAndBlockPoint[0] = d(ballTopPoint, blockBottomPoint)
         distanceBallPointAndBlockPoint[1] = d(ballBottomPoint, blockTopPoint)
         distanceBallPointAndBlockPoint[2] = d(ballLeftPoint, blockRightPoint)
         distanceBallPointAndBlockPoint[3] = d(ballRightPoint, blockLeftPoint)
     */

    bool boolDistanceBallPointAndBlockPoint[len];
    const float distanceBallPointAndBlockPoint[] = {abs(ballPoint[0] - blockPoint[1]), abs(ballPoint[1] - blockPoint[0]), abs(ballPoint[2] - blockPoint[3]), abs(ballPoint[3] - blockPoint[2])};

    for (size_t i = 0; i < len; ++i)
    {
        if(distanceBallPointAndBlockPoint[i] <= 0.01)
            boolDistanceBallPointAndBlockPoint[i] = true;
        else
            boolDistanceBallPointAndBlockPoint[i] = false;
    }

    bool * valueBelongsToTheSegment = getSegment(ballPoint, blockPoint, len);


    for (int i = 0; i < len; ++i)
    {
        if(boolDistanceBallPointAndBlockPoint[i] && valueBelongsToTheSegment[i])
        {
            distance[i] = true;
        }
        else
        {
            distance[i] = false;
        }
    }

    delete[] valueBelongsToTheSegment;
    valueBelongsToTheSegment = nullptr;

    return distance;
}

bool * getSegment(const float *ballPoint, const float *blockPoint, const size_t len)
{
    bool * isSegment = new bool[len];

    bool a, b, c;

    /*
      x = ballPoint[2] & ballPoint[3] & blockPoint[2] & blockPoint[3]
      y = ballPoint[0] & ballPoint[1] & blockPoint[0] & blockPoint[1]
    */

    a = blockPoint[2] <= ballPoint[2]; // block left point <= ball left point
    b = blockPoint[3] >= ballPoint[3]; // block right point >= ball right point
    c = a && b;

    isSegment[0] = c;
    isSegment[1] = c;

    a = blockPoint[0] >= ballPoint[1]; // block top point >= ball bottom point
    b = blockPoint[1] <= ballPoint[0]; // block bottom point <= ball top point
    c = a && b;

    isSegment[2] = c;
    isSegment[3] = c;

    return isSegment;
}

int sigma(float x)
{
    if(x > 0)
        return 1;
    else if(x < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}