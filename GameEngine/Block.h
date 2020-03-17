//
// Created by maxim on 03.07.2019.
//

#ifndef INC_2DTENNISGAME_BLOCK_H
#define INC_2DTENNISGAME_BLOCK_H

#include "BaseGameObject.h"


class Block:public BaseGameObject
{

public:
    Block() = delete;
    Block(ObjectCreater object, GLFWwindow *mainwindow, Shader shader);
    Block(const Block & other);
    Block(Block && other);
    Block & operator =(const Block & other);
    Block & operator =(Block && other) noexcept;
    bool operator == (const Block& other) const;
    bool operator != (const Block& other) const;
    void update() override;
    virtual ~Block() = default;
};


#endif //INC_2DTENNISGAME_BLOCK_H
