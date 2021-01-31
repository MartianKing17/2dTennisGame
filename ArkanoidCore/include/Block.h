//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_BLOCK_H
#define ARKANOID_BLOCK_H

#include "BaseGameObject.h"

class Block : public BaseGameObject
{
public:
    explicit Block(Render *renderModel);
    void update() override;
    ~Block() override = default;
};

#endif //ARKANOID_BLOCK_H
