//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_BLOCK_H
#define ARKANOID_BLOCK_H

#include "BaseGameObject.h"

class Block : public BaseGameObject
{
public:
    explicit Block(std::unique_ptr<Render> &&renderModel);
    ~Block() override = default;
};

#endif //ARKANOID_BLOCK_H
