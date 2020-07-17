//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_BLOCK_H
#define ARKANOID_BLOCK_H

#include "BaseGameObject.h"


class Block:public BaseGameObject
{

public:
    Block() = default;
    Block(GLFWwindow *mainwindow, RenderModel *renderModel);
    Block(const Block & other);
    Block(Block && other);
    Block & operator =(const Block & other);
    Block & operator =(Block && other) noexcept;
    bool operator == (const Block& other) const;
    bool operator != (const Block& other) const;
    void update() override;
    virtual ~Block() = default;
};

#endif //ARKANOID_BLOCK_H
