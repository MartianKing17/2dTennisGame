//
// Created by maxim on 16.07.2020.
//

#include <string>
#include <utility>
#include <algorithm>
#include "../include/init.h"
#include "GemulingEngine/include/DirectRender.h"
#include "GemulingEngine/include/GLDirectRender.h"
#include "GemulingEngine/include/Shader.h"
#include "GemulingEngine/include/Render.h"
#include "GemulingEngine/include/GLRender.h"

using namespace std;

struct BlockCharact
{
    float x;
    float y;
    std::string path;
};

unsigned int modules(int value, int base)
{
    unsigned int res{};

    while (value > base) {
        value -= base;
        ++res;
    }

    return res;
}

std::pair<float, float> parseCoor(int value)
{
    float x{}, y{};
    const float yStep = 0.05;
    const float xStep = 0.154;
    const int sizeOfElemInX = 13;
    ++value;
    y = modules(value, sizeOfElemInX);
    x = value % 13;
    if (!x) x = 13;
    --x;
    --y;
    x = -1.0 + xStep * x + 0.075;
    y = 1.0 - yStep * y;
    return {x, y};
}

std::vector<std::string> readLevelFile(const std::string& lvlFilename)
{
    std::vector<std::string> data{};
    std::string str{};
    std::ifstream read(lvlFilename);

    if (!read.is_open()) {
        throw std::runtime_error("Cannot open level file script");
    }

    while (!read.eof()) {
        std::getline(read, str);
        data.push_back(str);
        str.clear();
    }

    read.close();
    data.pop_back();
    return data;
}

std::string remove(std::string src)
{
    size_t index{};
    for (auto it = src.begin(); it != src.end(); ++it) {
        if (std::isspace(*it)) ++index;
    }

    src.erase(src.begin(), src.begin() + index);
    return src;
}

std::vector<BlockCharact> convertToBlockData(std::vector<std::string> &data)
{
    std::vector<BlockCharact> vecBlocksCharact{};
    std::string value{};
    size_t pos{};
    std::pair<float, float> point{};

    for (std::string &src : data) {
        pos = src.find(',');
        value = src.substr(0, std::distance(src.begin(), src.begin() + pos));
        point = parseCoor(static_cast<int>(std::stod(value)));
        ++pos;
        src.erase(src.begin(), src.begin() + pos);
        src = remove(src);
        vecBlocksCharact.push_back({point.first, point.second, src});
    }

    return vecBlocksCharact;
}

void makeBlock(const std::string& lvlFilename, std::list<std::shared_ptr<Block>> &blocks)
{
    const std::string path = "texture/";
    const std::string shaderVS = "path/shaderPlatform.vs", shaderFragment = "path/shaderFragPlatform.fragment";
    unique_ptr<DirectRender> directRender{};
    unique_ptr<Render> render{};
    MatrixValue matrixValue{0., 0., 1., 0.075, 0.025, 1.};
    shared_ptr<Block> block;
    std::vector<BlockCharact> blocksCharact;
    std::vector<std::string> data{};
    const glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);
    const glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    glm::mat4 worldView{};

    try {
        data = readLevelFile(lvlFilename);
    } catch (const std::runtime_error& e) {
        throw e;
    }

    blocksCharact = convertToBlockData(data);

    for (const BlockCharact &blockCharact : blocksCharact) {
        try {
            directRender = make_unique<GLDirectRender>();
        } catch (const std::runtime_error& e) {
            throw e;
        }

        matrixValue.a = blockCharact.x;
        matrixValue.b = blockCharact.y;
        worldView = projection * camera;
        directRender->createTexture(path + blockCharact.path);
        directRender->makeShader(shaderVS, shaderFragment);
        directRender->setValues(matrixValue);
        render = make_unique<GLRender>(directRender.release(), worldView);
        block = std::make_shared<Block>(std::move(render));
        blocks.push_back(block);
    }
}

std::unique_ptr<Ball> makeBall()
{
    const glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);
    const glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    const glm::mat4 worldView = projection * camera;
    MatrixValue matrixValue = {0., 0., 1., 0.03, 0.03, 0.};
    const std::string textureFileName = "texture/ball.png";
    const std::string shaderVS = "path/shaderBall.vs", shaderFragment = "path/shaderFragBall.fragment";
    unique_ptr<DirectRender> directRender{};
    unique_ptr<Render> render{};

    try {
        directRender = make_unique<GLDirectRender>();
    } catch (const std::runtime_error& e) {
        throw e;
    }

    directRender->createTexture(textureFileName);
    directRender->makeShader(shaderVS, shaderFragment);
    directRender->setValues(matrixValue);
    render = make_unique<GLRender>(directRender.release(), worldView);
    return std::make_unique<Ball>(std::move(render));
}

std::unique_ptr<Platform> makePlatform(short *platformMotion)
{
    const glm::mat4 projection = glm::ortho(-1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f);
    const glm::mat4 camera = glm::lookAt(
            glm::vec3(+0.0f,+0.0f,+1.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f)
    );

    const glm::mat4 worldView = projection * camera;
    MatrixValue matrixValue = {0., -0.75, 1., 0.2, 0.2, 0.};
    const std::string textureFileName = "texture/platform.png";
    const std::string shaderVS = "path/shaderPlatform.vs", shaderFragment = "path/shaderFragPlatform.fragment";
    unique_ptr<DirectRender> directRender{};
    unique_ptr<Render> render{};

    try {
        directRender = make_unique<GLDirectRender>();
    } catch (const std::runtime_error& e) {
        throw e;
    }

    directRender->createTexture(textureFileName);
    directRender->makeShader(shaderVS, shaderFragment);
    directRender->setValues(matrixValue);
    render = make_unique<GLRender>(directRender.release(), worldView);
    return std::make_unique<Platform>(std::move(render), platformMotion);
}
