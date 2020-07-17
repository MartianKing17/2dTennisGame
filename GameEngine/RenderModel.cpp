//
// Created by maxim on 15.07.2020.
//

#include "RenderModel.h"


RenderModel::RenderModel(MatrixValue matValue, GLFWwindow *window, Shader shader, glm::mat4 worldView, std::string textureFileName)

{
    this->a = matValue.a;
    this->b = matValue.b;
    this->c = matValue.c;
    this->sx = matValue.sx;
    this->sy = matValue.sy;
    this->sz = matValue.sz;
    this->window = window;
    this->shader = shader;
    this->worldView = worldView;

    initializateVao();
    initializateVbo();
    initializateEbo();
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    createTexture(textureFileName.c_str());
    modelCoor = glGetUniformLocation(shader.getProgram(), "model");
}

RenderModel::RenderModel(const RenderModel & other)
{
    this->vao = other.vao;
    this->vbo = other.vbo;
    this->ebo = other.ebo;
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;
    this->texture = other.texture;
    this->shader = other.shader;
    this->window = other.window;
    this->worldView = other.worldView;
    this->modelCoor = other.modelCoor;
}
RenderModel::RenderModel(RenderModel && other)
{
    this->vao = other.vao;
    this->vbo = other.vbo;
    this->ebo = other.ebo;
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;
    this->texture = other.texture;
    this->shader = other.shader;
    this->window = other.window;
    this->worldView = other.worldView;
    this->modelCoor = other.modelCoor;

    other.vao = 0;
    other.vbo = 0;
    other.ebo = 0;
    other.a = 0.f;
    other.b = 0.f;
    other.c = 0.f;
    other.sx = 0.f;
    other.sy = 0.f;
    other.sz = 0.f;
    other.texture = 0;
    other.shader = {};
    other.window = nullptr;
    other.worldView = glm::mat4(1.f);
    other.modelCoor = 0;
}

RenderModel & RenderModel::operator =(const RenderModel & other)
{
    this->vao = other.vao;
    this->vbo = other.vbo;
    this->ebo = other.ebo;
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;
    this->texture = other.texture;
    this->shader = other.shader;
    this->window = other.window;
    this->worldView = other.worldView;
    this->modelCoor = other.modelCoor;

    return *this;
}

RenderModel & RenderModel::operator =(RenderModel && other) noexcept
{
    this->vao = other.vao;
    this->vbo = other.vbo;
    this->ebo = other.ebo;
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    this->sx = other.sx;
    this->sy = other.sy;
    this->sz = other.sz;
    this->texture = other.texture;
    this->shader = other.shader;
    this->window = other.window;
    this->worldView = other.worldView;
    this->modelCoor = other.modelCoor;

    other.vao = 0;
    other.vbo = 0;
    other.ebo = 0;
    other.a = 0.f;
    other.b = 0.f;
    other.c = 0.f;
    other.sx = 0.f;
    other.sy = 0.f;
    other.sz = 0.f;
    other.texture = 0;
    other.shader = {};
    other.window = nullptr;
    other.worldView = glm::mat4(1.f);
    other.modelCoor = 0;

    return *this;
}

void RenderModel::initializateVao()
{
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
}

void RenderModel::initializateVbo()
{
    const GLfloat vertices[32] =
            {
                    1.f, 1.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f,
                    1.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f,
                    -1.f, -1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
                    -1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f
            };

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void RenderModel::initializateEbo()
{
    const GLint indices[6] = {0, 1, 3, 1, 2, 3};
    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void RenderModel::createTexture(std::string data)
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    int width, height;
    unsigned char* image = SOIL_load_image(data.c_str(), &width, &height, 0, SOIL_LOAD_AUTO);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderModel::setValues(MatrixValue matrixValue)
{
    this->a = matrixValue.a;
    this->b = matrixValue.b;
    this->c = matrixValue.c;
    this->sx = matrixValue.sx;
    this->sy = matrixValue.sy;
    this->sz = matrixValue.sz;
}

MatrixValue RenderModel::getValues()
{
    return {this->a, this->b, this->c, this->sx, this->sy, this->sz};
};

void RenderModel::render(glm::mat4 model)
{
    const short elem = 6;
    shader.Use();
    glUniformMatrix4fv(this->modelCoor,1,GL_FALSE,glm::value_ptr(this->worldView * model));
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, elem, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D,0);
    glBindVertexArray(0);
    glDisable(GL_BLEND);
}

RenderModel::~RenderModel()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}