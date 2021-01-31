//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_BASEGAMEOBJECT_H
#define ARKANOID_BASEGAMEOBJECT_H
#include "GemulingEngine/glm/glm/glm.hpp"
#include "GemulingEngine/glm/glm/gtc/matrix_transform.hpp"
#include "GemulingEngine/glm/glm/gtc/type_ptr.hpp"
#include "GemulingEngine/include/GLRender.h"
#include <utility>

class BaseGameObject
{
public:
    BaseGameObject() = default;
    BaseGameObject(Render *renderModel);
    BaseGameObject(const BaseGameObject & other);
    BaseGameObject(BaseGameObject && other);
    BaseGameObject & operator =(const BaseGameObject & other);
    BaseGameObject & operator =(BaseGameObject && other) noexcept;
    void render(); //RenderModel position place and drawing paint
    virtual void update(); //Update position data
    void setPosition(MatrixValue matrixValue);
    glm::mat4 getPosition();
    float getVerticalPlace() const;
    float getGorizontalPlace()const;
    float getRadius() const;
    virtual ~BaseGameObject();
protected:
    float cx, cy, radius; //Central x, central,y and radius
    bool value;
    Render * renderModel;
    glm::mat4 model;
};

#endif //ARKANOID_BASEGAMEOBJECT_H
