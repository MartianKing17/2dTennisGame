//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_BASEGAMEOBJECT_H
#define ARKANOID_BASEGAMEOBJECT_H
#include "../GemulingEngine/glm/glm/glm.hpp"
#include "../GemulingEngine/glm/glm/gtc/matrix_transform.hpp"
#include "../GemulingEngine/glm/glm/gtc/type_ptr.hpp"
#include "../GemulingEngine/include/GLRender.h"
#include <utility>
#include <memory>

class BaseGameObject
{
public:
    BaseGameObject() = default;
    BaseGameObject(std::unique_ptr<Render> &&renderModel);
    void render(); //RenderModel position place and drawing paint
    void setPosition(MatrixValue matrixValue);
    glm::mat4 getPosition();
    virtual ~BaseGameObject() = default;
protected:
    std::unique_ptr<Render> m_renderModel;
    glm::mat4 m_model;
};

#endif //ARKANOID_BASEGAMEOBJECT_H
