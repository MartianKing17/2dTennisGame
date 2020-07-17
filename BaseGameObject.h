//
// Created by maxim on 16.07.2020.
//

#ifndef ARKANOID_BASEGAMEOBJECT_H
#define ARKANOID_BASEGAMEOBJECT_H
#include "GameEngine/include/glm/glm.hpp"
#include "GameEngine/include/glm/gtc/matrix_transform.hpp"
#include "GameEngine/include/glm/gtc/type_ptr.hpp"
#include "GameEngine/RenderModel.h"
#include <utility>


class BaseGameObject
{
protected:
    float cx, cy, radius; //Central x, central,y and radius
    GLFWwindow * window;
    bool value;
    RenderModel * renderModel;
    glm::mat4 model;
public:
    BaseGameObject() = default;
    BaseGameObject(GLFWwindow *mainWindow, RenderModel *renderModel);
    BaseGameObject(const BaseGameObject & other);
    BaseGameObject(BaseGameObject && other);
    BaseGameObject & operator =(const BaseGameObject & other);
    BaseGameObject & operator =(BaseGameObject && other) noexcept;
    void render(); //RenderModel position place and drawing paint
    virtual void update(); //Update position data
    float getVerticalPlace() const;
    float getGorizontalPlace()const;
    float getRadius() const;
    virtual ~BaseGameObject();
};

#endif //ARKANOID_BASEGAMEOBJECT_H
