//
// Created by maxim on 16.07.2020.
//

#include "../include/Block.h"

Block::Block(std::unique_ptr<Render> &&renderModel)
        : BaseGameObject(std::move(renderModel))
{
    auto matValue = m_renderModel->getValue();
    setPosition(matValue);
}
