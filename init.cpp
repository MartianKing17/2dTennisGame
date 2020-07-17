//
// Created by maxim on 16.07.2020.
//

#include "init.h"

using namespace std;
using namespace chrono;

void makeBlock(GLFWwindow * window, MatrixValue matrixValue, string picturePath, std::list<std::shared_ptr<Block>> &blocks)
{
    const glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);
    const glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    const glm::mat4 worldView = projection * camera;
    const std::string shaderVS = "path/shaderPlatform.vs", shaderFragment = "path/shaderFragPlatform.fragment";
    Shader shader = {shaderVS, shaderFragment};
    auto renderModel = new RenderModel(matrixValue, window, shader, worldView, picturePath);

    auto block = std::make_shared<Block>(window, renderModel);
    blocks.push_back(block);
}

std::list<Block> createBlocks(GLFWwindow *window)
{
    const glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);
    const glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    const glm::mat4 worldView = projection * camera;
    const size_t blockSize = 30;
    std::list<Block> blocks;
    Block block;
    RenderModel * renderModel;
    const std::string textureFileName = "texture/met_cube(crop).png";  // block texture
    const std::string shaderVS = "path/shaderPlatform.vs", shaderFragment = "path/shaderFragPlatform.fragment";
    Shader shader;
    MatrixValue matrixValue = {0., 0., 0.f, 0.1, 0.1, 0};

    for (float b = 0.9f; b > 0.4f ; b -= 0.2f)
    {
        for (float a = -0.9f; a < 1.f ; a += 0.2f)
        {
            matrixValue.a = a;
            matrixValue.b = b;
            shader = {shaderVS,shaderFragment};
            renderModel = new RenderModel(matrixValue, window, shader, worldView, textureFileName);
            block= {window, renderModel};
            blocks.push_back(block);
        }
    }

    return blocks;
}


std::unique_ptr<Ball> makeBall(GLFWwindow *window)
{
    const glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);
    const glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    const glm::mat4 worldView = projection * camera;
    MatrixValue matrixValue = {0., 0., 1., 0.03, 0.03, 0.};
    const std::string textureFileName = "texture/ball(crop).png";
    const std::string shaderVS = "path/shaderBall.vs", shaderFragment = "path/shaderFragBall.fragment";
    Shader shader = {shaderVS,shaderFragment};
    auto renderModel = new RenderModel(matrixValue, window, shader, worldView, textureFileName);
    // Remake function
    // Function must have a logic interactions with platform and blocks
    return std::make_unique<Ball>(window, renderModel, []()->bool{return true;});
}

std::unique_ptr<Platform> makePlatform(GLFWwindow *window, short *platformMotion)
{
    const glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);

    const glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    const glm::mat4 worldView = projection * camera;
    MatrixValue matrixValue = {0., -0.75, 1., 0.25, 0.25, 0.};
    const std::string textureFileName = "texture/platform_var1(crop).png";
    const std::string shaderVS = "path/shaderPlatform.vs", shaderFragment = "path/shaderFragPlatform.fragment";
    Shader shader = {shaderVS,shaderFragment};
    auto renderModel = new RenderModel(matrixValue, window, shader, worldView, textureFileName);
    return std::make_unique<Platform>(window, renderModel, platformMotion);
}

void update(std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks)
{
    ball->update();
    platform->update();

    for (auto iter = blocks.begin(); iter != blocks.end() ; iter++)
    {
        auto block = *iter;
        block->update();
    }
}

void render(std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks)
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    ball->render();
    platform->render();

    for (auto iter = blocks.begin(); iter != blocks.end() ; iter++)
    {
        auto block = *iter;
        block->render();
    }
}

int mainloop(std::unique_ptr<Ball> &ball, std::unique_ptr<Platform> &platform, std::list<std::shared_ptr<Block>> &blocks, GLFWwindow *window, bool &isSpaceActive)
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
        else if (blocks.empty())
        {
            return 1;
        }

        update(ball, platform, blocks);
        timer = system_clock::now();
        glfwSwapBuffers(window);
    }
}
