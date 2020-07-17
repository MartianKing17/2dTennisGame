//
// Created by maxim on 16.07.2020.
//

#include "levels.h"
#include "init.h"

void lvl1(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{
    MatrixValue matrixValue = {0., 0., 0.f, 0.1, 0.1, 0};
    std::string fileTextureName = "texture/met_cube(crop).png";

    for (float b = 0.9f; b > 0.3f; b -= 0.2)
    {
        for (float a = -0.9f; a < 1.1f; a += 0.2)
        {
            matrixValue.a = a;
            matrixValue.b = b;
            makeBlock(window, matrixValue, fileTextureName, blocks);
        }
    }
}

void lvl2(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl3(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl4(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl5(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl6(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl7(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl8(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl9(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl10(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl11(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl12(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl13(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl14(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl15(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl16(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl17(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl18(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl19(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl20(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl21(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl22(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl23(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl24(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl25(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl26(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl27(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl28(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl29(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl30(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl31(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}

void lvl32(GLFWwindow *window, std::list<std::shared_ptr<Block>> &blocks)
{

}
