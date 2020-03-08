//
// Created by maxim on 02.08.2019.
//

#include "ObjectCreater.h"

ObjectCreater::ObjectCreater(std::vector<GLfloat> startObjectPosition, std::string texName):texName(texName),init(false)
{
    for (int i = 0; i < startObjectPosition.size(); i++)
    {
        this->vertices[i]=startObjectPosition.at(i);
    }

    indices[0]=0,indices[1]=1,indices[2]=3,
    indices[3]=1,indices[4]=2,indices[5]=3;
}

ObjectCreater::ObjectCreater(const ObjectCreater &other)
{
    this->vao=other.vao;
    this->vbo=other.vbo;
    this->ebo=other.ebo;
    this->texName=other.texName;
    this->texture=other.texture;
    int sizeVertices= sizeof(this->vertices)/ sizeof(GLuint),sizeIndex= sizeof(this->indices)/ sizeof(GLuint);

    for (int i = 0; i < sizeVertices; ++i)
    {
        this->vertices[i]=other.vertices[i];

        if(i < sizeIndex)
        {
            this->indices[i]=other.indices[i];
        }
    }
}

ObjectCreater::ObjectCreater(ObjectCreater &&other)noexcept
{
    this->vao=other.vao;
    this->vbo=other.vbo;
    this->ebo=other.ebo;
    this->texName=other.texName;
    this->texture=other.texture;
    int sizeVertices= sizeof(this->vertices)/ sizeof(GLuint),sizeIndex= sizeof(this->indices)/ sizeof(GLuint);

    for (int i = 0; i < sizeVertices; ++i)
    {
        this->vertices[i]=other.vertices[i];
        other.vertices[i]=0;

        if(i <sizeIndex)
        {
            this->indices[i]=other.indices[i];
            other.indices[i]=0;
        }
    }

    other.vao=0;
    other.vbo=0;
    other.ebo=0;
    other.texName.clear();
    other.texture=0;
}

ObjectCreater & ObjectCreater::operator=(const ObjectCreater &other)
{
    this->vao=other.vao;
    this->vbo=other.vbo;
    this->ebo=other.ebo;
    this->texName=other.texName;
    this->texture=other.texture;
    int sizeVertices= sizeof(this->vertices)/ sizeof(GLuint),sizeIndex= sizeof(this->indices)/ sizeof(GLuint);

    for (int i = 0; i < sizeVertices; ++i)
    {
        this->vertices[i]=other.vertices[i];

        if(i < sizeIndex)
        {
            this->indices[i]=other.indices[i];
        }
    }

    return *this;
}

ObjectCreater & ObjectCreater::operator=(ObjectCreater &&other)noexcept
{
    this->vao=other.vao;
    this->vbo=other.vbo;
    this->ebo=other.ebo;
    this->texName=other.texName;
    this->texture=other.texture;
    int sizeVertices= sizeof(this->vertices)/ sizeof(GLuint),sizeIndex= sizeof(this->indices)/ sizeof(GLuint);

    for (int i = 0; i < sizeVertices; ++i)
    {
        this->vertices[i]=other.vertices[i];
        other.vertices[i]=0;

        if(i <sizeIndex)
        {
            this->indices[i]=other.indices[i];
            other.indices[i]=0;
        }
    }

    other.vao=0;
    other.vbo=0;
    other.ebo=0;
    other.texName.clear();
    other.texture=0;
    return *this;
}

void ObjectCreater::initializateVao()
{
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
}

void ObjectCreater::initializateVbo()
{
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void ObjectCreater::initializateEbo()
{
    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void ObjectCreater::createTexture(std::string data)
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

void ObjectCreater::initializate()
{
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

    createTexture(texName.c_str());
    this->init=true;
}

bool ObjectCreater::isInitializate()
{
    return init;
}

void ObjectCreater::set_matrix_translate(float a, float b, float c)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

void ObjectCreater::set_matrix_scale(float sx, float sy, float sz)
{
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

float * ObjectCreater::get_matrix_translate()
{
    const size_t len = 3;
    float * mat_translate = new float[len];
    mat_translate[0] = a;
    mat_translate[1] = b;
    mat_translate[2] = c;
    return mat_translate;
}

float * ObjectCreater::get_matrix_scale()
{
    const size_t len = 3;
    float * mat_scale = new float[len];
    mat_scale[0] = sx;
    mat_scale[1] = sy;
    mat_scale[2] = sz;
    return mat_scale;
}

std::array<std::pair<double, double>, 3> * ObjectCreater::return_model_coor()
{
    const size_t len = 4;
    std::array<std::pair<double, double>, 3> * model_coordinate = new std::array<std::pair<double, double>, 3>();
    std::pair<double,double> point_coordinate;

    for (int i = 0, j = 0; j < len; i+=8, j++)
    {
            point_coordinate.first = vertices[i];
            point_coordinate.second = vertices[i+1];
            model_coordinate->at(j) = point_coordinate;
    }

    return model_coordinate;

}

std::array<GLuint,4> ObjectCreater::return_data()
{
    std::array<GLuint,4> data={vao,vbo,ebo,texture};
    return data;
}